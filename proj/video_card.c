#include <lcom/lcf.h>

#include "video_card.h"
#include "video_card_macros.h"
#include "keyboard.h"
#include "macros_kbd.h"

static vbe_mode_info_t vmi_p;
static void *video_mem = NULL;         // frame-buffer VM addres (static global variable
static mmap_t mem;
extern bool two_byte_scan;
extern uint8_t scancode[2];
vg_vbe_contr_info_t info_p;

int set_graphics_mode(uint16_t mode)
{
  struct minix_mem_range mr;
  int r;	

 	lm_alloc(1<<20, &mem);

  memset(&vmi_p, 0, sizeof(vmi_p)); // clear

  //graphics mode VRAM is not directly accessible by a user probram. To make it accessible you need to map it in the process address space

  //begining of mapping the graphics VRAM in its address space
  //1st -> what's the VRAm's physical address
  if(vbe_get_mode_info(mode, &vmi_p)!=0) //to be implemented
  {
    printf("Failed to get vbe info\n");
    return 1;
  }

  unsigned int vram_address; // VRAM's physical addresss
  unsigned int vram_size; // VRAM's size, but you can use the frame-buffer size, instead

  //VRAM's physical address
  vram_address = vmi_p.PhysBasePtr; 

  //2nd -> horizontal and vertical resolution, as well as the number of bits per pixel = VRAM's size
  vram_size = vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel)/8);

  //We have the physical address, the horizontal and vertical resolution and the number of bits per pixel -> now memory mapping is allowed

  mr.mr_base = (phys_bytes) vram_address;
  mr.mr_limit = mr.mr_base + vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
   panic("sys_privctl (ADD_MEM) failed: %d\n", r);
 
  //Beginning of map memory

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
    panic("couldn't map video memory");

  //inicialize graphic mode
  
  struct reg86 r86;

  memset(&r86, 0, sizeof(r86));  //zero the structure;

  r86.intno = BIOS_VIDEO; //INT 10h
  r86.ah = CALL_VBE;  
  r86.al = VBE_SET_MODE;
  r86.bx = LINEAR_FRAME_FUFFER | /*CLEAR_DISPLAY_MEM | */mode;

  if( sys_int86(&r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }
  return 0;
}

int putPixel(uint16_t x, uint16_t y, uint32_t color)

{
  if(video_mem == NULL) printf("video_mem NULL\n");
  if(x > vmi_p.XResolution || y > vmi_p.YResolution)
  //if the x or the y is outside of the resolution of the frame_buffer
    return 0;
  uint32_t num_bytes_pixel = (vmi_p.BitsPerPixel)/8; //alterar -> pode ser 15
  uint32_t pos = (y * vmi_p.XResolution + x)*num_bytes_pixel;
  uint8_t *ptr = (uint8_t*) video_mem + pos;
  //matrix: go to the y (line) * xresolution + x(collumn)

  memcpy(ptr, &color, num_bytes_pixel);

  return 0;

}


int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color)
{
  for(int i = 0; i < len; i++)
  {
    putPixel(x+i,y,color);
  }

  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width,uint16_t height, uint32_t color)
{
  for (int i = 0; i < height; i++) {
    if (vg_draw_hline(x,y+i,width,color) != 0) {
      printf("Failed to draw rectangle");
      return 1;
    }
  }

  return 0;
}

int draw_pattern(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step)
{
  //The number of rectangles along each direction (i.e. both horizontal and vertical) is specified in the no_rectangles argument. If, e.g. its value is 3, then the pattern will be a matrix of 3 by 3 rectangles. All rectangles must have the same size. If the horizontal (vertical) resolution is not a multiple of the no_rectangles argument, then there will be a black stripe on the right (bottom) of the screen. The width of this black stripe must be minimum.
  uint16_t width = vmi_p.XResolution / no_rectangles;
  uint16_t height = vmi_p.YResolution / no_rectangles;
  uint32_t color;
  uint32_t R, G, B;

  for(size_t col = 0; col < no_rectangles; col++)
  {
    for(size_t row = 0; row < no_rectangles; row++)
    {
      if(mode == INDEXED_COLOR)
      {
        // If the color mode is indexed (or packed pixel, in VBE jargon), then the index of the color to fill the rectangle with coordinates (row, column) is given by the expression:
        color = (first + (row * no_rectangles + col) * step) % (1 << vmi_p.BitsPerPixel);

        vg_draw_rectangle(col * width, row * height, width, height, color);
      }
      else
      {
        // If the color mode is direct, then the RGB components of the color to fill the rectangle with coordinates (row, column) are given by the expressions: 
        R = (((first & ((0x1 << vmi_p.RedMaskSize) - 1) << vmi_p.RedFieldPosition) >> vmi_p.RedFieldPosition) + col * step) % (1 << vmi_p.RedMaskSize);
        G = (((first & ((0x1 << vmi_p.GreenMaskSize) - 1) << vmi_p.GreenFieldPosition) >> vmi_p.GreenFieldPosition) + row * step) % (1 << vmi_p.GreenMaskSize);
        B = (((first & ((0x1 << vmi_p.BlueMaskSize) - 1) << vmi_p.BlueFieldPosition) >> vmi_p.BlueFieldPosition) + (col + row) * step) % ( 1 << vmi_p.BlueMaskSize);

        color = (R << vmi_p.RedFieldPosition) | (G << vmi_p.GreenFieldPosition) | B; // color = RRGGBB

        vg_draw_rectangle(col * width, row * height, width, height, color);
      }
    }
  }
  return 0;
}

int use_xpm(xpm_map_t xpm, uint16_t x, uint16_t y)
{
  uint8_t* sprite;
  xpm_image_t img;
  sprite = xpm_load(xpm, XPM_5_6_5, &img);
  memset(video_mem, 0xff, vmi_p.XResolution*vmi_p.YResolution*2);
  int bcount = 0;
  for (int i = y; i < img.height + y; i++)
  {
    for(int j = x; j < img.width + x; j++)
    {
      if(((uint16_t*)(img.bytes))[bcount] != xpm_transparency_color(img.type))
      {
        putPixel(j, i, ((uint16_t*)(img.bytes))[bcount]);
      }
      else
      {
        putPixel(j, i, 0);
      }
      
      bcount++;
    }
  }
  return 0;
}

int clean_screen_and_draw(xpm_map_t xpm, uint16_t x, uint16_t y)
{
  vg_draw_rectangle(0,0, vmi_p.XResolution, vmi_p.YResolution, 0);
  use_xpm(xpm, x, y);
  return 0;
}

int controller(vg_vbe_contr_info_t *info_p)
{
  struct reg86 r86;
  mmap_t mapa;

  lm_alloc(sizeof(vg_vbe_contr_info_t), &mapa);

  VideoBlockInfo * ctrl_info = (VideoBlockInfo*) mapa.virt;

  ctrl_info->VBESignature[0] = 'V';
  ctrl_info->VBESignature[1] = 'B';
  ctrl_info->VBESignature[2] = 'E';
  ctrl_info->VBESignature[3] = '2';

  memset(&r86, 0, sizeof(r86));

  r86.intno = BIOS_VIDEO;
  r86.ah = CALL_VBE;
  r86.al = GET_CONTR_INFO;
  r86.es = PB2BASE(mapa.phys);
  r86.di = PB2OFF(mapa.phys);

  if( sys_int86(&r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

  info_p->VBESignature[0] = ctrl_info->VBESignature[0];
  info_p->VBESignature[1] = ctrl_info->VBESignature[1];
  info_p->VBESignature[2] = ctrl_info->VBESignature[2];
  info_p->VBESignature[3] = ctrl_info->VBESignature[3];
  info_p->VBEVersion[0] = ctrl_info->VBEVersion[0];
  info_p->VBEVersion[1] = ctrl_info->VBEVersion[1];
  info_p->TotalMemory = ctrl_info->TotalMemory * 64;


  /*



   INCOMPLETE



  */



  lm_free(&mapa);


	return 0;
}
