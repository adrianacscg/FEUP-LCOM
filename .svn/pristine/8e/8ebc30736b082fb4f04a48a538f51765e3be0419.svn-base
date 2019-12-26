#include <lcom/lcf.h>

#include "video_card.h"
#include "video_card_macros.h"
#include "keyboard.h"
#include "macros_kbd.h"
#include "myutils.h"

static vbe_mode_info_t vmi_p;
static void *video_mem = NULL;
static uint8_t *double_buffer;
extern bool two_byte_scan;
extern uint8_t scancode[2];
vg_vbe_contr_info_t info_p;
uint16_t xres, yres;

int set_graphics_mode(uint16_t mode)
{
  struct minix_mem_range mr;
  int r;	

  memset(&vmi_p, 0, sizeof(vmi_p));

  if(vbe_get_mode_info(mode, &vmi_p)!=0)
  {
    printf("Failed to get vbe info\n");
    return 1;
  }

  unsigned int vram_address;
  unsigned int vram_size;

  vram_address = vmi_p.PhysBasePtr; 

  vram_size = vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel+7)/8);
  xres = vmi_p.XResolution;
  yres = vmi_p.YResolution;

  mr.mr_base = (phys_bytes) vram_address;
  mr.mr_limit = mr.mr_base + vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
   panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
    panic("couldn't map video memory");

  double_buffer = malloc(vram_size);
  
  struct reg86 r86;

  memset(&r86, 0, sizeof(r86)); 

  r86.intno = BIOS_VIDEO; 
  r86.ah = CALL_VBE;  
  r86.al = VBE_SET_MODE;
  r86.bx = LINEAR_FRAME_FUFFER | /*CLEAR_DISPLAY_MEM | */mode;

  if( sys_int86(&r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }
  return 0;
}

int use_xpm(xpm_image_t *map, uint16_t x, uint16_t y)
{
  if(double_buffer == NULL) printf("double_buffer NULL\n");

  uint32_t num_bytes_pixel = (vmi_p.BitsPerPixel+7)/8;

  uint16_t x_max = min(x + map->width, vmi_p.XResolution);
  uint16_t y_max = min(y + map->height, vmi_p.YResolution);

  int bcount = 0;
  
  for (int i = y; i < y_max; i++)
  {
    for(int j = x; j < x_max; j++)
    {
      uint32_t color = ((uint16_t*)(map->bytes))[bcount];

      if((color != xpm_transparency_color(map->type)))
      {        
        uint32_t pos = (i * vmi_p.XResolution + j)*num_bytes_pixel;
        uint8_t *ptr = (uint8_t*) double_buffer + pos;

        memcpy(ptr, &color, num_bytes_pixel);
      }

      bcount++;
    }
  }

  return 0;
}

int clean_screen_and_draw()
{
  memset(double_buffer, 0, vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel+7)/8));
  return 0;
}

void DBtoVM()
{
  memcpy(video_mem, double_buffer, vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel+7)/8));
}

