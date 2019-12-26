#ifndef _VIDEO_CARD_H_
#define _VIDEO_CARD_H_

int set_graphics_mode(uint16_t mode);
int putPixel(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width,uint16_t height, uint32_t color);
int draw_pattern(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);
int use_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);
int clean_screen_and_draw(xpm_map_t xpm, uint16_t x, uint16_t y);
int controller(vg_vbe_contr_info_t *info_p);

typedef struct {
	char VBESignature[4];		
	BCD VBEVersion[2];			
	char *OEMString;			
	uint16_t *VideoModeList;	
	uint32_t TotalMemory;			
	char *OEMVendorNamePtr;		
	char *OEMProductNamePtr;	   
	char *OEMProductRevPtr;		 
} VideoBlockInfo;

#endif
