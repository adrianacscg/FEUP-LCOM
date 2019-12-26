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
#include "loading_xpms.h"
#include "macros_proj.h"
#include "types.h"

extern uint8_t scancode[2];
extern bool two_byte_scan;
extern struct packet pack;
extern int byte_no;
extern unsigned int timer_counter;
extern uint16_t pos_x, pos_y;
extern bool loading, choose, menu, eat, sleeping, mini_game, eating_action, lobby, ate, mg_enter;
extern uint16_t xres, yres;
extern xpm_image_t load_bc, choose_character, cursor, border, not_implemented, day, night;
extern xpm_image_t rudolph_meio_baixo, rudolph_meio_cima, rudolph_esquerda_cima, rudolph_esquerda_baixo, rudolph_direita_cima, rudolph_direita_baixo;
extern xpm_image_t chicken_leg;

extern enum sleep_bar sleep_barra;
extern enum food_bar food_barra;
extern enum play_bar play_barra;
extern enum counter counter_barra;

extern xpm_image_t minigame_sky, cloud, mg_menu;

int timer_manager()
{
  xpm_image_t character;
  xpm_image_t sleep_bar, food_bar, play_bar;
  xpm_image_t counter;

  timer_int_handler();

  if(timer_counter % 2 == 0) //a alterar; atual: 30 fps
  {
    if(lobby)
    {
      character = decide_rudolph(pos_x, pos_y);
      sleep_bar = decide_sleep_bar(sleep_barra);
      food_bar = decide_food_bar(food_barra);
      play_bar = decide_play_bar(play_barra);
      counter = decide_time(counter_barra);
    }

    clean_screen_and_draw();

    if(loading)
      use_xpm(&load_bc, 0, 0);

    if(choose)
      use_xpm(&choose_character, 0, 0);

    if(menu)
    {
      use_xpm(&day, 0, 0);
      use_xpm(&character, CHAR_X, CHAR_Y);
      use_xpm(&sleep_bar,850, 120);
      use_xpm(&food_bar,850, 200);
      use_xpm(&play_bar,850, 280);
    }  
    if(eat)
    {
      use_xpm(&day, 0, 0);
      use_xpm(&character, CHAR_X, CHAR_Y); 
      use_xpm(&chicken_leg, FOOD_POS_X, FOOD_POS_Y);
      use_xpm(&sleep_bar,850, 120);
      use_xpm(&food_bar,850, 200);
      use_xpm(&play_bar,850, 280);

      if(eating_action)
      {
        use_xpm(&chicken_leg, pos_x, pos_y);
      }
    }

    if(sleeping)
    {
      use_xpm(&night, 0, 0);
      use_xpm(&character, CHAR_X, CHAR_Y); 
      use_xpm(&sleep_bar,850, 120);
      use_xpm(&food_bar,850, 200);
      use_xpm(&play_bar,850, 280); 
    }    

    if(mini_game && ! mg_enter)
    {
      
      /*THINGS I ADDED - para ser mais facil encontrar/corrigir */
      use_xpm(&mg_menu, 0, 0);
      //use_xpm(&cloud, 138, 100);  //still testing the x and y values
    }
    if(mini_game && mg_enter)
    {
      use_xpm(&minigame_sky, 0, 0);
      use_xpm(&counter, 138, 216);
    }
       

    use_xpm(&cursor, pos_x, pos_y);
    DBtoVM();
  }
  return 0;
}

int keyboard_manager()
{
  kbc_ih();
  if(loading && scancode[0] == ENTER_BREAK_CODE)
  {
    loading = false;
    choose = true;
  }
  if((sleeping && scancode[0] == ERASE_BREAK_CODE) || (eat && scancode[0] == ERASE_BREAK_CODE) || (mini_game && scancode[0] == ERASE_BREAK_CODE))
  {
    menu = true;
    sleeping = false;
    eat = false;
    mini_game = false;
    mg_enter = false;
    counter_barra = C15;
  }
  if(mini_game && scancode[0] == ENTER_BREAK_CODE)
  {
    mg_enter = true;
  }
  return 0;
}

int mouse_manager()
{
  mouse_ih();
  if(byte_no == 3)
  {
    build_packet(&pack);

    pos_x = max(0, pos_x + pack.delta_x);
    pos_x = min(pos_x, xres -1);

    pos_y = max(0, pos_y - pack.delta_y);
    pos_y = min(pos_y, yres -1);   

    if(choose && pack.lb == 1 && (pos_x >= 428 && pos_x <= 852) && (pos_y >= 302 && pos_y <= 722))
    {
      lobby = true;
      choose = false;
      menu = true;
      sleep_barra = SLEEP_4;
      food_barra = FOOD_4;
      play_barra = PLAY_4;
      counter_barra = C15;
    }
    else if(menu && pack.lb == 1 && (pos_x >= 322 && pos_x <= 415) && (pos_y >= 900 && pos_y <= 1000))
    {
      sleeping = true;
      menu = false;
    }
    else if(menu && pack.lb == 1 && (pos_x >= 600 && pos_x <= 700) && (pos_y >= 900 && pos_y <= 1000))
    {
      eat = true;
      menu = false;
    }
    else if(menu && pack.lb == 1 && (pos_x >= 870 && pos_x <= 970) && (pos_y >= 900 && pos_y <= 1000))
    {
      mini_game = true;
      menu = false;
    }
    else if(eat && pack.lb == 1 && (pos_x >= FOOD_POS_X && pos_y >= FOOD_POS_Y && pos_x < (FOOD_POS_X+120) && pos_y < (FOOD_POS_Y+120)))
    {
      eating_action = true;
    }
    else if(eating_action && pack.lb == 0 && (pos_x >= CHAR_X && pos_y >= CHAR_Y && pos_x < (CHAR_X+472) && pos_y < (CHAR_Y+472)))
    {
      eating_action = false;
      ate = true;
    }
    else if(eating_action && pack.lb == 0 && !(pos_x >= CHAR_X && pos_y >= CHAR_Y && pos_x < (CHAR_X+472) && pos_y < (CHAR_Y+472)))
    {
      eating_action = false;
      ate = false;
    }
    byte_no = 0;
  }
  return 0;
}



