#ifndef _MACROS_PROJ_
#define _MACROS_PROJ_

#include <stdint.h>

/** @defgroup Project Macros + RTC Macros 
 * @{
 *
 * Constants used in the project (Positions) + Macros of the RTC
 */

#define CHAR_X                324 /**< @brief character position (x) */
#define CHAR_Y                313 /**< @brief character position (y) */

/* Screen Divisions */

#define MIN_ESQUERDA_X        0   /**< @brief minimum value of the left rectangle of the screen (x) */
#define MAX_ESQUERDA_X        341 /**< @brief minimum value of the left rectangle of the screen (x) */ */
#define MIN_MEIO_X            341 /**< @brief minimum value of the center rectangle of the screen (x)  */
#define MAX_MEIO_X            682 /**< @brief maximum value of the center rectangle of the screen (x)  */
#define MIN_DIREITA_X         682 /**< @brief minimum value of the right rectangle of the screen (x)  */
#define MAX_DIREITA_X         1024  /**< @brief maximum value of the right rectangle of the screen (x)  */
#define MIN_CIMA_Y            0   /**< @brief minimum value of the top rectangle of the screen (y) */
#define MAX_CIMA_Y            384 /**< @brief maximum value of the top rectangle of the screen (y) */
#define MIN_BAIXO_Y           384 /**< @brief minimum value of the bottom rectangle of the screen (y) */
#define MAX_BAIXO_Y           768 /**< @brief maximum value of the bottom rectangle of the screen (y) */

#define FOOD_POS_X            820 /**< @brief x food position */
#define FOOD_POS_Y            550 /**< @brief y food position */

#define CHOOSE_RUDOLPH_MIN_X  350 /**< @brief x minimum position to click on rudolph */
#define CHOOSE_RUDOLPH_MAX_X  675 /**< @brief x maximum position to click on rudolph */
#define CHOOSE_RUDOLPH_MIN_Y  235 /**< @brief y minimum position to click on rudolph */
#define CHOOSE_RUDOLPH_MAX_Y  535 /**< @brief y maximum position to click on rudolph */

#define SLEEP_MIN_X           259 /**< @brief x minimum position to click on sleep button */
#define SLEEP_MAX_X           331 /**< @brief x maximum position to click on sleep button */
#define SLEEP_MIN_Y           672 /**< @brief y minimum position to click on sleep button */
#define SLEEP_MAX_Y           742 /**< @brief y maximum position to click on sleep button */

#define FOOD_MIN_X            480 /**< @brief x minimum position to click on eat button */
#define FOOD_MAX_X            552 /**< @brief x maximum position to click on eat button */
#define FOOD_MIN_Y            672 /**< @brief y minimum position to click on eat button */
#define FOOD_MAX_Y            742 /**< @brief y maximum position to click on eat button */

#define PLAY_MIN_X            693 /**< @brief x minimum position to click on the minigame button */
#define PLAY_MAX_X            768 /**< @brief x maximum position to click on the minigame button */
#define PLAY_MIN_Y            672 /**< @brief y minimum position to click on the minigame button */
#define PLAY_MAX_Y            742 /**< @brief y maximum position to click on the minigame button */

#define X_BARS                650 /**< @brief x position of the life bars */
#define Y_SLEEP_BAR           115 /**< @brief y position of the sleep bar */
#define Y_FOOD_BAR            175 /**< @brief y position of the eat bars */
#define Y_PLAY_BAR            245 /**< @brief y position of the fun bars */

#define X_COUNTER             228 /**< @brief x position counter of the minigame */
#define Y_COUNTER             0   /**< @brief y position counter of the minigame */

#define CLOUD_LEFT            123 /**< @brief x position of the left cloud */
#define CLOUD_BOTTOM          499 /**< @brief y position of the bottom cloud */
#define CLOUD_CENTER          373 /**< @brief x position of the center cloud */
#define CLOUD_MIDDLE          364 /**< @brief y position of the middle cloud */
#define CLOUD_RIGHT           637 /**< @brief x position of the right cloud */
#define CLOUD_TOP             231 /**< @brief y position of the top cloud */

/*************RTC****************/

#define RTC_IRQ                  8 /**< @brief RTC IRQ */ 
//The RTC has only one IRQ line, which is connected to line IRQ0 of PIC2, i.e. IRQ8  
#define RTC_ADDR_REG            0x70 /**< @brief RTC address register*/ 
//must be loaded with the address of the RTC register to be accessed 
#define RTC_DATA_REG            0x71 /**< @brief RTC data register*/ 
//used to transfer the data to/from the RTC's register accessed 

#define REG_A                   0x0A
#define REG_B                   0x0B
#define REG_C                   0x0C
#define REG_D                   0x0D

#define RTC_HOURS               0x04
#define RTC_MINS                0x02
#define RTC_SECS                0x00

#define HOURS_ALARM_INTERRUPT         BIT(5)
#define MINUTES_ALARM_INTERRUPT       BIT(3)

#endif
