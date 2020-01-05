#ifndef _TYPES_H_
#define _TYPES_H_

/** @defgroup types
 * @{
 *
 * enums used in the project
 */

/**
 * @brief Different modes of the sleep bar
 * 
 * sleep bar has 4 stages, all with the same value. When the bar is complete, we can say that it has all the 4 stages. It loses stages with time
 */
enum sleep_bar{
  SLEEP_4,              /**< @brief Sleep bar with all the 4 stages (bar completed) */
  SLEEP_3,              /**< @brief Sleep bar with the 3 stages*/
  SLEEP_2,              /**< @brief Sleep bar with the 2 stages*/
  SLEEP_1               /**< @brief Sleep bar with 1 stage*/
};

/**
 * @brief Different modes of the food bar
 * 
 * food bar has 4 stages, all with the same value. When the bar is complete, we can say that it has all the 4 stages. It loses stages with time
 */
enum food_bar{
  FOOD_4,               /**< @brief Eat bar with all the 4 stages (bar completed) */
  FOOD_3,               /**< @brief Eat bar with the 3 stages*/
  FOOD_2,               /**< @brief Eat bar with the 2 stages*/
  FOOD_1                /**< @brief Eat bar with 1 stage*/
};

/**
 * @brief Different modes of the fun bar
 * 
 * fun bar has 4 stages, all with the same value. When the bar is complete, we can say that it has all the 4 stages. It loses stages with time
 */
enum play_bar{
  PLAY_4,               /**< @brief Fun bar with all the 4 stages (bar completed) */
  PLAY_3,               /**< @brief Fun bar with the 3 stages*/
  PLAY_2,               /**< @brief Fun bar with the 2 stages*/
  PLAY_1                /**< @brief Fun bar with 1 stage*/
};

/**
 * @brief Different values of the counter
 */
enum counter_bar{
  C00,                  /**< @brief Counter = 0 */
  C01,                  /**< @brief Counter = 1 */
  C02,                  /**< @brief Counter = 2 */
  C03,                  /**< @brief Counter = 3 */
  C04,                  /**< @brief Counter = 4 */
  C05,                  /**< @brief Counter = 5 */
  C06,                  /**< @brief Counter = 6 */
  C07,                  /**< @brief Counter = 7 */
  C08,                  /**< @brief Counter = 8 */
  C09,                  /**< @brief Counter = 9 */
  C10,                  /**< @brief Counter = 10 */
  C11,                  /**< @brief Counter = 11 */
  C12,                  /**< @brief Counter = 12 */
  C13,                  /**< @brief Counter = 13 */
  C14,                  /**< @brief Counter = 14 */
  C15                   /**< @brief Counter = 15 */
};

/**
 * @brief Different positions of the cloud
 */
enum cloud_position{
  left,                 /**< @brief cloud is in the left side of the screen */                 
  center,               /**< @brief cloud is in the center of the screen */ 
  right                 /**< @brief cloud is in the right side of the screen */ 
};

/**
 * @brief Different values of the units of the score
 */
enum score_bar_1{
  S01,                  /**< @brief units of the score = 1 */
  S02,                  /**< @brief units of the score = 2 */
  S03,                  /**< @brief units of the score = 3 */
  S04,                  /**< @brief units of the score = 4 */
  S05,                  /**< @brief units of the score = 5 */
  S06,                  /**< @brief units of the score = 6 */
  S07,                  /**< @brief units of the score = 7 */
  S08,                  /**< @brief units of the score = 8 */
  S09,                  /**< @brief units of the score = 9 */
  S00_1                 /**< @brief units of the score = 0 */
};

/**
 * @brief Different values of the dozens of the score
 */
enum score_bar_2{
  S10,                  /**< @brief dozens of the score = 1 */
  S20,                  /**< @brief dozens of the score = 2 */  
  S30,                  /**< @brief dozens of the score = 3 */
  S40,                  /**< @brief dozens of the score = 4 */
  S50,                  /**< @brief dozens of the score = 5 */
  S60,                  /**< @brief dozens of the score = 6 */
  S70,                  /**< @brief dozens of the score = 7 */
  S80,                  /**< @brief dozens of the score = 8 */
  S90,                  /**< @brief dozens of the score = 9 */
  S00_2                 /**< @brief dozens of the score = 0 */
};

#endif
