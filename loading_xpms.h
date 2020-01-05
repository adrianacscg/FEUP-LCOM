#ifndef _LOADING_XPMS_H_
#define _LOADING_XPMS_H_

#include "types.h"
#include "rtc.h"


/** @defgroup Functions loading_xpms.c
 * @{
 *
 * Functions used to help working with the xpms
 */


/**
 * @brief Loads all the xpms
 * 
 * @return Return 0 upon success
 */
int loading_xpms();     

/**
 * @brief Decides in what position the rodolph should be in (used to change rudolph's eyes)
 * 
 * Depends on the mouse postion
 * 
 * @param pos_x position x of the mouse
 * @param pos_y position y of the mouse
 * 
 * @return the xpm_image_t of the correspondent rudolph position
 */
xpm_image_t decide_rudolph(uint16_t pos_x, uint16_t pos_y);

/**
 * @brief Decides in what position the sleep bar should be in
 * 
 * The sleep bar changes with time
 * Depends on time and if the character is sleeping or not
 * 
 * @param sb state of the current sleep bar
 * 
 * @return the xpm_image_t of the correspondent sleep bar
 */
xpm_image_t decide_sleep_bar(enum sleep_bar sb);


/**
 * @brief Decides in what position the fun bar should be in
 * 
 * The fun bar changes with time
 * Depends on time and if the character is playing
 * 
 * @param sb state of the current play bar
 * 
 * @return the xpm_image_t of the correspondent play bar
 */
xpm_image_t decide_play_bar(enum play_bar pb);

/**
 * @brief Decides in what position the eat bar should be in
 * 
 * The eat bar changes with time
 * Depends on time and if the character is eating
 * 
 * @param sb state of the current eat bar
 * 
 * @return the xpm_image_t of the correspondent eat bar
 */
xpm_image_t decide_food_bar(enum food_bar fb);

/**
 * @brief Decides the value of the counter of the minigame
 * 
 * The counter changes with time
 * Depends on time
 * 
 * @param c current time
 * 
 * @return the xpm_image_t of the correspondent counter value
 */
xpm_image_t decide_time(enum counter_bar c);

/**
 * @brief Decides the value of dozens number of the scores
 * 
 * This value changes when the character presses the correct key 10 times
 * 
 * @return enum value of the dozens number for the score
 */
enum score_bar_2 event_2();

/**
 * @brief Decides the value of unities number of the scores
 * 
 * This value changes when the character presses the correct key 1 time
 * 
 * @return enum value of the unities number for the score
 */
enum score_bar_1 event_1();

/**
 * @brief Decides the value of the counter of the minigame
 * 
 * The counter changes with time
 * Depends on time
 * 
 * @param c current time
 * 
 * @return the xpm_image_t of the correspondent counter value
 */
xpm_image_t decide_score_2_game();
xpm_image_t decide_score_2();
xpm_image_t decide_score_1_game();
xpm_image_t decide_score_1();
xpm_image_t decide_hours(rtc_time *time);
xpm_image_t decide_minutes(rtc_time *time);


#endif
