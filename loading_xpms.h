#ifndef _LOADING_XPMS_H_
#define _LOADING_XPMS_H_

#include "types.h"

int loading_xpms();
xpm_image_t decide_rudolph(uint16_t pos_x, uint16_t pos_y);
xpm_image_t decide_sleep_bar(enum sleep_bar sb);
xpm_image_t decide_play_bar(enum play_bar pb);
xpm_image_t decide_food_bar(enum food_bar fb);
xpm_image_t decide_time(enum counter_bar c);


#endif
