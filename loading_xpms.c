#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

/*FICHEIROS*/
#include "main_functions.h"
#include "video_card.h"
#include "keyboard.h"
#include "macros_kbd.h"
#include "mouse.h"
#include "ps2_mouse_macros.h"
#include "myutils.h"
#include "macros_proj.h"
#include "timer.h"
#include "types.h"

/*XPMS*/
#include "xpms/choose_char.xpm"
#include "xpms/cursor.xpm"
#include "xpms/loading.xpm"
#include "xpms/border.xpm"
#include "xpms/not_implemented.xpm"
#include "xpms/day.xpm"
#include "xpms/night.xpm"
#include "xpms/rudolph.xpm"
#include "xpms/rudolph_baixo_direita.xpm"
#include "xpms/rudolph_baixo_esquerda.xpm"
#include "xpms/rudolph_cima_direita.xpm"
#include "xpms/rudolph_cima_esquerda.xpm"
#include "xpms/rudolph_cima_meio.xpm"
#include "xpms/rudolph_sleep.xpm"
#include "xpms/chicken_leg.xpm"
#include "xpms/sleep_1.xpm"
#include "xpms/sleep_2.xpm"
#include "xpms/sleep_3.xpm"
#include "xpms/sleep_4.xpm"
#include "xpms/food_1.xpm"
#include "xpms/food_2.xpm"
#include "xpms/food_3.xpm"
#include "xpms/food_4.xpm"
#include "xpms/play_1.xpm"
#include "xpms/play_2.xpm"
#include "xpms/play_3.xpm"
#include "xpms/play_4.xpm"
#include "xpms/counter_00.xpm"
#include "xpms/counter_01.xpm"
#include "xpms/counter_02.xpm"
#include "xpms/counter_03.xpm"
#include "xpms/counter_04.xpm"
#include "xpms/counter_05.xpm"
#include "xpms/counter_06.xpm"
#include "xpms/counter_07.xpm"
#include "xpms/counter_08.xpm"
#include "xpms/counter_09.xpm"
#include "xpms/counter_10.xpm"
#include "xpms/counter_11.xpm"
#include "xpms/counter_12.xpm"
#include "xpms/counter_13.xpm"
#include "xpms/counter_14.xpm"
#include "xpms/counter_15.xpm"
#include "xpms/bg_enter.xpm"
#include "xpms/bg_mg.xpm"
#include "xpms/MINIGAME_CLOUD.xpm"
#include "xpms/rudolph_minigame.xpm"


//GLOBAL VARIABLES
xpm_image_t load_bc, choose_character, cursor, border, not_implemented, day, night;
xpm_image_t rudolph_meio_baixo, rudolph_meio_cima, rudolph_esquerda_cima, rudolph_esquerda_baixo, rudolph_direita_cima, rudolph_direita_baixo, rudolph_sleep;
xpm_image_t chicken_leg;
xpm_image_t sleep_4, sleep_3, sleep_2, sleep_1, food_4, food_3, food_2, food_1, play_4, play_3, play_2, play_1;
xpm_image_t counter_00, counter_01, counter_02, counter_03, counter_04, counter_05, counter_06, counter_07, counter_08, counter_09, counter_10, counter_11, counter_12, counter_13, counter_14, counter_15;
xpm_image_t minigame_sky, cloud, mg_menu, rudolph_cloud;
extern int timer_counter;
int timer_counter_sleep = 0, timer_counter_food = 0, timer_counter_play = 0;

enum sleep_bar sleep_barra;
enum play_bar play_barra;
enum food_bar food_barra;
enum counter_bar counter_barra;

extern bool sleeping, ate, mini_game, mg_enter;
extern uint8_t scancode[2];


int loading_xpms()
{
  uint8_t *load_back, *choose_char, *cursor_map, *border_map, *not_map, *day_map, *night_map;
  uint8_t *rudolph_meio_baixo_map, *rudolph_meio_cima_map, *rudolph_esquerda_cima_map, *rudolph_esquerda_baixo_map, *rudolph_direita_cima_map, *rudolph_direita_baixo_map, *rudolph_sleep_map;
  uint8_t *chicken_leg_map;
  uint8_t *sleep_4_map, *sleep_3_map, *sleep_2_map, *sleep_1_map, *food_4_map, *food_3_map, *food_2_map, *food_1_map, *play_4_map, *play_3_map, *play_2_map, *play_1_map;
  uint8_t *counter_00_map, *counter_01_map, *counter_02_map, *counter_03_map, *counter_04_map, *counter_05_map, *counter_06_map, *counter_07_map, *counter_08_map, *counter_09_map, *counter_10_map, *counter_11_map, *counter_12_map, *counter_13_map, *counter_14_map, *counter_15_map;
  uint8_t *minigame_sky_map, *cloud_map, *minigame_menu_map, *rudolph_on_cloud_map;

  load_back = xpm_load(loading_xpm, XPM_5_6_5, &load_bc);
  choose_char = xpm_load(choose_char_2_xpm, XPM_5_6_5, &choose_character);
  cursor_map = xpm_load(cursor_xpm, XPM_5_6_5, &cursor);
  border_map = xpm_load(border_xpm, XPM_5_6_5, &border);
  not_map = xpm_load(not_implemented_xpm, XPM_5_6_5, &not_implemented);
  day_map = xpm_load(day_xpm, XPM_5_6_5, &day);
  night_map = xpm_load(night_xpm, XPM_5_6_5, &night);

  rudolph_meio_baixo_map = xpm_load(rudolph_xpm, XPM_5_6_5, &rudolph_meio_baixo);
  rudolph_meio_cima_map = xpm_load(rudolph_cima_meio_xpm, XPM_5_6_5, &rudolph_meio_cima);
  rudolph_direita_baixo_map = xpm_load(rudolph_baixo_direita_xpm, XPM_5_6_5, &rudolph_direita_baixo);
  rudolph_direita_cima_map = xpm_load(rudolph_cima_direita_xpm, XPM_5_6_5, &rudolph_direita_cima);
  rudolph_esquerda_baixo_map = xpm_load(rudolph_baixo_esquerda_xpm, XPM_5_6_5, &rudolph_esquerda_baixo);
  rudolph_esquerda_cima_map = xpm_load(rudolph_cima_esquerda_xpm, XPM_5_6_5, &rudolph_esquerda_cima);
  rudolph_sleep_map = xpm_load(rudolph_sleep_xpm, XPM_5_6_5, &rudolph_sleep);  
  
  chicken_leg_map = xpm_load(chicken_leg_xpm, XPM_5_6_5, &chicken_leg);

  sleep_1_map = xpm_load(sleep_1_xpm, XPM_5_6_5, &sleep_1);
  sleep_2_map = xpm_load(sleep_2_xpm, XPM_5_6_5, &sleep_2);
  sleep_3_map = xpm_load(sleep_3_xpm, XPM_5_6_5, &sleep_3);
  sleep_4_map = xpm_load(sleep_4_xpm, XPM_5_6_5, &sleep_4);

  food_1_map = xpm_load(food_1_xpm, XPM_5_6_5, &food_1);
  food_2_map = xpm_load(food_2_xpm, XPM_5_6_5, &food_2);
  food_3_map = xpm_load(food_3_xpm, XPM_5_6_5, &food_3);
  food_4_map = xpm_load(food_4_xpm, XPM_5_6_5, &food_4);

  play_1_map = xpm_load(play_1_xpm, XPM_5_6_5, &play_1);
  play_2_map = xpm_load(play_2_xpm, XPM_5_6_5, &play_2);
  play_3_map = xpm_load(play_3_xpm, XPM_5_6_5, &play_3);
  play_4_map = xpm_load(play_4_xpm, XPM_5_6_5, &play_4);

  counter_00_map = xpm_load(counter_00_xpm, XPM_5_6_5, &counter_00);
  counter_01_map = xpm_load(counter_01_xpm, XPM_5_6_5, &counter_01);
  counter_02_map = xpm_load(counter_02_xpm, XPM_5_6_5, &counter_02);
  counter_03_map = xpm_load(counter_03_xpm, XPM_5_6_5, &counter_03);
  counter_04_map = xpm_load(counter_04_xpm, XPM_5_6_5, &counter_04);
  counter_05_map = xpm_load(counter_05_xpm, XPM_5_6_5, &counter_05);
  counter_06_map = xpm_load(counter_06_xpm, XPM_5_6_5, &counter_06);
  counter_07_map = xpm_load(counter_07_xpm, XPM_5_6_5, &counter_07);
  counter_08_map = xpm_load(counter_08_xpm, XPM_5_6_5, &counter_08);
  counter_09_map = xpm_load(counter_09_xpm, XPM_5_6_5, &counter_09);
  counter_10_map = xpm_load(counter_10_xpm, XPM_5_6_5, &counter_10);
  counter_11_map = xpm_load(counter_11_xpm, XPM_5_6_5, &counter_11);
  counter_12_map = xpm_load(counter_12_xpm, XPM_5_6_5, &counter_12);
  counter_13_map = xpm_load(counter_13_xpm, XPM_5_6_5, &counter_13);
  counter_14_map = xpm_load(counter_14_xpm, XPM_5_6_5, &counter_14);
  counter_15_map = xpm_load(counter_15_xpm, XPM_5_6_5, &counter_15);

  /*THINGS I ADDED - para ser mais facil encontrar/corrigir */
  minigame_sky_map = xpm_load(bg_mg_xpm, XPM_5_6_5, &minigame_sky);
  cloud_map = xpm_load(MINIGAME_CLOUD_xpm, XPM_5_6_5, &cloud);
  minigame_menu_map = xpm_load(bg_enter_xpm, XPM_5_6_5, &mg_menu);
  rudolph_on_cloud_map = xpm_load(rudolph_minigame_xpm, XPM_5_6_5, &rudolph_cloud);
  


  return 0;
}

xpm_image_t decide_rudolph(uint16_t pos_x, uint16_t pos_y)
{
  xpm_image_t character;
  if(sleeping)
  {
    character = rudolph_sleep;
    return character;
  }
    
  if(pos_y >= MIN_CIMA_Y && pos_y < MAX_CIMA_Y)
  {
    if(pos_x >= MIN_ESQUERDA_X && pos_x < MAX_ESQUERDA_X)
      character = rudolph_esquerda_cima;
    else if(pos_x >= MIN_MEIO_X && pos_x < MAX_MEIO_X)
      character = rudolph_meio_cima;
    else if(pos_x >= MIN_DIREITA_X && pos_x < MAX_DIREITA_X)
      character = rudolph_direita_cima;
  }
  else if(pos_y >= MIN_BAIXO_Y && pos_y < MAX_BAIXO_Y)
  {
    if(pos_x >= MIN_ESQUERDA_X && pos_x < MAX_ESQUERDA_X)
      character = rudolph_esquerda_baixo;
    else if(pos_x >= MIN_MEIO_X && pos_x < MAX_MEIO_X)
      character = rudolph_meio_baixo;
    else if(pos_x >= MIN_DIREITA_X && pos_x < MAX_DIREITA_X)
      character = rudolph_direita_baixo;
  }
  return character;
}

xpm_image_t decide_sleep_bar(enum sleep_bar sb)
{
  if(timer_counter % sys_hz() == 0)
  {
    timer_counter_sleep++;
  }

  if(sleeping)
  {
    if(timer_counter_sleep == 5)
    {
      timer_counter_sleep = 0;

      switch(sb)
      {
        case SLEEP_4:
          sleep_barra = SLEEP_4;
          return sleep_4;

        case SLEEP_3:
          sleep_barra = SLEEP_4;
          return sleep_4;

        case SLEEP_2:
          sleep_barra = SLEEP_3;
          return sleep_3;

        case SLEEP_1:
          sleep_barra = SLEEP_2;
          return sleep_2;

        default:
          break;
      }
    }
  }


  if(timer_counter_sleep == 15)
  {
    timer_counter_sleep = 0;

    switch(sb)
    {
      case SLEEP_4:
        sleep_barra = SLEEP_3;
        return sleep_3;

      case SLEEP_3:
        sleep_barra = SLEEP_2;
        return sleep_2;

      case SLEEP_2:
        sleep_barra = SLEEP_1;
        return sleep_1;

      case SLEEP_1:
        sleep_barra = SLEEP_1;
        return sleep_1;

      default:
        break;
    }
  }

  switch(sb)
    {
      case SLEEP_4:
        return sleep_4;

      case SLEEP_3:
        return sleep_3;

      case SLEEP_2:
        return sleep_2;

      case SLEEP_1:
        return sleep_1;

      default:
        break;
    }

  

  return sleep_1;
}

xpm_image_t decide_play_bar(enum play_bar pb)
{
  if(timer_counter % sys_hz() == 0)
  {
    timer_counter_play++;
  }

  if(mg_enter)
  {
    if(timer_counter_play == 15)
    {
      timer_counter_play = 0;

      switch(pb)
      {
        case PLAY_4:
          play_barra = PLAY_4;
          return play_4;

        case PLAY_3:
          play_barra = PLAY_4;
          return play_4;

        case PLAY_2:
          play_barra = PLAY_3;
          return play_3;

        case PLAY_1:
          play_barra = PLAY_2;
          return play_2;

        default:
          break;
      }
    }
  }

  if(timer_counter_play == 10)
  {
    timer_counter_play = 0;

    switch(pb)
    {
      case PLAY_4:
        play_barra = PLAY_3;
        return play_3;

      case PLAY_3:
        play_barra = PLAY_2;
        return play_2;

      case PLAY_2:
        play_barra = PLAY_1;
        return play_1;

      case PLAY_1:
        play_barra = PLAY_1;
        return play_1;

      default:
        break;
    }
  }

  switch(pb)
    {
      case PLAY_4:
        return play_4;

      case PLAY_3:
        return play_3;

      case PLAY_2:
        return play_2;

      case PLAY_1:
        return play_1;

      default:
        break;
    }

  return play_1;
}

xpm_image_t decide_food_bar(enum food_bar fb)
{
  if(timer_counter % sys_hz() == 0)
    timer_counter_food++;
  

  if(ate)
  {
    ate = false;
    switch(fb)
    {
      case FOOD_4:
        food_barra = FOOD_4;
        return food_4;

      case FOOD_3:
        food_barra = FOOD_4;
        return food_4;

      case FOOD_2:
        food_barra = FOOD_3;
        return food_3;

      case FOOD_1:
        food_barra = FOOD_2;
        return food_2;

      default:
        break;
    }
  }

  if(timer_counter_food == 7)
  {
    timer_counter_food = 0;

    switch(fb)
    {
      case FOOD_4:
        food_barra = FOOD_3;
        return food_3;

      case FOOD_3:
        food_barra = FOOD_2;
        return food_2;

      case FOOD_2:
        food_barra = FOOD_1;
        return food_1;

      case FOOD_1:
        food_barra = FOOD_1;
        return food_1;

      default:
        break;
    }
  }

  switch(fb)
    {
      case FOOD_4:
        return food_4;

      case FOOD_3:
        return food_3;

      case FOOD_2:
        return food_2;

      case FOOD_1:
        return food_1;

      default:
        break;
    }

  return food_1;
}

xpm_image_t decide_time(enum counter_bar c)
{
  if(mini_game)
  {
    if(timer_counter % sys_hz() == 0)
    {
      switch(c)
      {
        case C15:
          counter_barra = C14;
          return counter_14;
        
        case C14:
          counter_barra = C13;
          return counter_13;
        
        case C13:
          counter_barra = C12;
          return counter_12;
        
        case C12:
          counter_barra = C11;
          return counter_11;

        case C11:
          counter_barra = C10;
          return counter_10; 

        case C10:
          counter_barra = C09;
          return counter_09;  

        case C09:
          counter_barra = C08;
          return counter_08;

        case C08:
          counter_barra = C07;
          return counter_07;
        
        case C07:
          counter_barra = C06;
          return counter_06;

        case C06:
          counter_barra = C05;
          return counter_05;  

        case C05:
          counter_barra = C04;
          return counter_04;

        case C04:
          counter_barra = C03;
          return counter_03;

        case C03:
          counter_barra = C02;
          return counter_02;

        case C02:
          counter_barra = C01;
          return counter_01;

        case C01:
          counter_barra = C00;
          return counter_00;

        case C00:
          counter_barra = C00;
          return counter_00;
        
        default:
          break;
 
      }
    }

    switch(c)
      {
        case C15:
          counter_barra = C15;
          return counter_15;
        
        case C14:
          counter_barra = C14;
          return counter_14;
        
        case C13:
          counter_barra = C13;
          return counter_13;
        
        case C12:
          counter_barra = C12;
          return counter_12;

        case C11:
          counter_barra = C11;
          return counter_11; 

        case C10:
          counter_barra = C10;
          return counter_10;  

        case C09:
          counter_barra = C09;
          return counter_09;

        case C08:
          counter_barra = C08;
          return counter_08;
        
        case C07:
          counter_barra = C07;
          return counter_07;

        case C06:
          counter_barra = C06;
          return counter_06;  

        case C05:
          counter_barra = C05;
          return counter_05;

        case C04:
          counter_barra = C04;
          return counter_04;

        case C03:
          counter_barra = C03;
          return counter_03;

        case C02:
          counter_barra = C02;
          return counter_02;

        case C01:
          counter_barra = C01;
          return counter_01;

        case C00:
          counter_barra = C00;
          return counter_00;
        
        default:
          break;
 
      }

  }
  
  return counter_15; 
  
}


