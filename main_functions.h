#ifndef _MAIN_FUNCTIONS_H_
#define _MAIN_FUNCTIONS_H_

#include "types.h"

int timer_manager();
int keyboard_manager();
int mouse_manager();
struct cloud_event* draw_clouds(int jump_counter);

#endif
