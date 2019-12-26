#ifndef _VIDEO_CARD_H_
#define _VIDEO_CARD_H_

int set_graphics_mode(uint16_t mode);
int use_xpm(xpm_image_t *map, uint16_t x, uint16_t y);
int clean_screen_and_draw();
void DBtoVM();

#endif