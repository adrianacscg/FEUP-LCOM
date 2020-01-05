#ifndef _MAIN_FUNCTIONS_H_
#define _MAIN_FUNCTIONS_H_

#include "types.h"

/** @defgroup main_functions
 * @{
 *
 * Main Functions of the Project
 */

/**
 * @brief Function that calls the timer interrupt handler and manages all the timer related variables and functions
 * 
 * @return Return 0 upon success
 */
int timer_manager();

/**
 * @brief Function that calls the keyboard interrupt handler and manages all the keyboard related variables and functions
 * 
 * @return Return 0 upon success
 */
int keyboard_manager();

/**
 * @brief Function that calls the mouse interrupt handler and manages all the mouse related variables and functions
 * 
 * @return Return 0 upon success
 */
int mouse_manager();

/**
 * @brief Function that calls the RTC interrupt handler and manages all the RTC related variables and functions
 * 
 * @return Return 0 upon success
 */
int rtc_manager();

/**
 * @brief Function that works with the logic of the minigame
 * 
 * The clouds of the minigame change when the jump_counter assumes different values
 * 
 * @param jump_counter variable used to help getting the score of the minigame and to use in the switch to decide wich cloud should be draw
 */
void draw_clouds(int jump_counter);

#endif
