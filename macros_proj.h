#ifndef _MACROS_PROJ_
#define _MACROS_PROJ_

#include <stdint.h>

#define CHAR_X                324
#define CHAR_Y                313

#define MIN_ESQUERDA_X        0
#define MAX_ESQUERDA_X        341
#define MIN_MEIO_X            341 
#define MAX_MEIO_X            682
#define MIN_DIREITA_X         682
#define MAX_DIREITA_X         1024
#define MIN_CIMA_Y            0
#define MAX_CIMA_Y            384
#define MIN_BAIXO_Y           384
#define MAX_BAIXO_Y           768

#define FOOD_POS_X            820
#define FOOD_POS_Y            550

#define CHOOSE_RUDOLPH_MIN_X  350
#define CHOOSE_RUDOLPH_MAX_X  675
#define CHOOSE_RUDOLPH_MIN_Y  235
#define CHOOSE_RUDOLPH_MAX_Y  535

#define SLEEP_MIN_X           259
#define SLEEP_MAX_X           331
#define SLEEP_MIN_Y           672
#define SLEEP_MAX_Y           742

#define FOOD_MIN_X            480
#define FOOD_MAX_X            552
#define FOOD_MIN_Y            672
#define FOOD_MAX_Y            742

#define PLAY_MIN_X            693
#define PLAY_MAX_X            768
#define PLAY_MIN_Y            672
#define PLAY_MAX_Y            742

#define X_BARS                650
#define Y_SLEEP_BAR           115
#define Y_FOOD_BAR            175
#define Y_PLAY_BAR            245

#define X_COUNTER             228
#define Y_COUNTER             0

#define CLOUD_LEFT            123
#define CLOUD_BOTTOM          499
#define CLOUD_CENTER          373
#define CLOUD_MIDDLE          364
#define CLOUD_RIGHT           637
#define CLOUD_TOP             231

/*************RTC****************/

#define RTC_IRQ                  8 //The RTC has only one IRQ line, which is connected to line IRQ0 of PIC2, i.e. IRQ8
#define RTC_ADDR_REG            0x70 //must be loaded with the address of the RTC register to be accessed
#define RTC_DATA_REG            0x71 //used to transfer the data to/from the RTC's register accessed

#define REG_A                   0x0a
#define REG_B                   0x0b
#define REG_C                   0x0c
#define REG_D                   0x0d

#define RTC_HOURS               0x04
#define RTC_MINS                0x02
#define RTC_SECS                0x00

#define ALARM_INTERRUPT         BIT(5)

#endif
