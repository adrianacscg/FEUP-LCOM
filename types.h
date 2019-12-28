#ifndef _TYPES_H_
#define _TYPES_H_

enum sleep_bar{
  SLEEP_4,
  SLEEP_3,
  SLEEP_2,
  SLEEP_1
};

enum food_bar{
  FOOD_4,
  FOOD_3,
  FOOD_2,
  FOOD_1
};

enum play_bar{
  PLAY_4,
  PLAY_3,
  PLAY_2,
  PLAY_1
};

enum counter_bar{
  C00,
  C01,
  C02,
  C03,
  C04,
  C05,
  C06,
  C07,
  C08,
  C09,
  C10,
  C11,
  C12,
  C13,
  C14,
  C15
};

enum cloud_position{
  left,
  center,
  right
};

struct cloud_event{
  enum cloud_position pos;
};

#endif
