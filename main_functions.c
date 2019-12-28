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
extern enum counter_bar counter_barra;

struct cloud_event nuvem;


extern xpm_image_t minigame_sky, cloud, mg_menu, rudolph_cloud;

int jump_counter = 0;
struct cloud_event proxima_nuvem;

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

    if(mini_game)
    {
      if(!mg_enter)
        use_xpm(&mg_menu, 0, 0);
      else
      {
        use_xpm(&minigame_sky, 0, 0);
        use_xpm(&counter, 138, 216);

        while(counter_barra != C00){
          
          proxima_nuvem.pos = draw_clouds(jump_counter)->pos;

          //jump_counter = decide_next_cloud(jump_counter, proxima_nuvem);

          if(jump_counter < 0) {
            use_xpm(&mg_menu, 0, 0); //if you die; need to change xpm to gameover pic
            //the value of jump_counter will be your score but negative, need to use abs to get the positive value and display it
            counter_barra = C00;
          }
        }
      }
      
    }
       
    use_xpm(&cursor, pos_x, pos_y);
    DBtoVM();
  }
  return 0;
}


struct cloud_event* draw_clouds(int jump_counter){

  switch(jump_counter){
    case 0:
      use_xpm(&rudolph_cloud, 250, 800); 
      use_xpm(&cloud, 640, 650);
      use_xpm(&cloud, 1030, 500);
      use_xpm(&cloud, 640, 350);
      use_xpm(&cloud, 250, 200);
      nuvem.pos = center;

      break;

    case 1:
      
      use_xpm(&rudolph_cloud, 250, 800); 
      use_xpm(&cloud, 640, 650);
      use_xpm(&cloud, 1030, 500);
      use_xpm(&cloud, 640, 350);
      use_xpm(&cloud, 250, 200);
      nuvem.pos = right;
      break;

    case 2:
      nuvem.pos = center;
    break;

    case 3:
    nuvem.pos = center;
    break;

    case 4:
    nuvem.pos = center;
    
    break;

    case 5:
    nuvem.pos = left;
    break;

    case 6:
    nuvem.pos = center;
    break;

    case 7:
    nuvem.pos = right;
    break;

    case 8:
    nuvem.pos = center;
    
    break;

    case 9:
    nuvem.pos = right;
    break;

    case 10:
    nuvem.pos = center;
    break;

    case 11:
    nuvem.pos = left;
    break;

    case 12:
    nuvem.pos = center;
    
    break;

    case 13:
    nuvem.pos = right;
    break;

    case 14:
    nuvem.pos = center;
    break;

    case 15:
    nuvem.pos = left;
    break;

    case 16:
    nuvem.pos = center;
    
    break;

    case 17:
    nuvem.pos = left;
    break;

    case 18:
    nuvem.pos = center;
    break;

    case 19:
    nuvem.pos = right;
    break;

    case 20:
    nuvem.pos = center;
    break;

    case 21:
    nuvem.pos = right;
    break;

    case 22:
    nuvem.pos = center;
    break;

    case 23:
    nuvem.pos = left;
    break;
  }

  return &nuvem;

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

  if(mini_game && mg_enter)
  {
    if(nuvem.pos == left && proxima_nuvem.pos == center && scancode[0] == RIGHT_ARROW_BREAK_CODE){
      jump_counter++;
      nuvem.pos = center;

    }

    if(nuvem.pos == right && proxima_nuvem.pos == center && scancode[0] == LEFT_ARROW_BREAK_CODE){
      jump_counter++;
      nuvem.pos = center;
    }

    if(nuvem.pos == center && proxima_nuvem.pos == left && scancode[0] == LEFT_ARROW_BREAK_CODE){
      jump_counter++;
      nuvem.pos = left;
    }

    if(nuvem.pos == center && proxima_nuvem.pos == right && scancode[0] == RIGHT_ARROW_BREAK_CODE){
      jump_counter++;
      nuvem.pos = right;
    }

    else
    {
      jump_counter--;
    }
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



