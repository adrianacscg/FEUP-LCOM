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
extern bool loading, choose, menu, eat, sleeping, mini_game, eating_action, lobby, ate, mg_enter, lost;
extern uint16_t xres, yres;
extern xpm_image_t load_bc, choose_character, cursor, border, not_implemented, day, night;
extern xpm_image_t rudolph_meio_baixo, rudolph_meio_cima, rudolph_esquerda_cima, rudolph_esquerda_baixo, rudolph_direita_cima, rudolph_direita_baixo;
extern xpm_image_t chicken_leg;
extern xpm_image_t minigame_sky, cloud, mg_menu, rudolph_cloud, minigame_score_menu;

extern enum sleep_bar sleep_barra;
extern enum food_bar food_barra;
extern enum play_bar play_barra;

extern enum counter_bar counter_barra;
static enum cloud_position nuvem = left;
enum cloud_position proxima_nuvem;
int jump_counter = 0;
int score_counter;


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
      counter = decide_time(counter_barra);
      character = decide_rudolph(pos_x, pos_y);
      sleep_bar = decide_sleep_bar(sleep_barra);
      food_bar = decide_food_bar(food_barra);
      play_bar = decide_play_bar(play_barra);
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
      use_xpm(&sleep_bar,X_BARS, Y_SLEEP_BAR);
      use_xpm(&food_bar,X_BARS, Y_FOOD_BAR);
      use_xpm(&play_bar,X_BARS, Y_PLAY_BAR);
    }  
    if(eat)
    {
      use_xpm(&day, 0, 0);
      use_xpm(&character, CHAR_X, CHAR_Y); 
      use_xpm(&chicken_leg, FOOD_POS_X, FOOD_POS_Y);
      use_xpm(&sleep_bar,X_BARS, Y_SLEEP_BAR);
      use_xpm(&food_bar,X_BARS, Y_FOOD_BAR);
      use_xpm(&play_bar,X_BARS, Y_PLAY_BAR);

      if(eating_action)
      {
        use_xpm(&chicken_leg, pos_x, pos_y);
      }
    }

    if(sleeping)
    {
      use_xpm(&night, 0, 0);
      use_xpm(&character, CHAR_X, CHAR_Y); 
      use_xpm(&sleep_bar,X_BARS, Y_SLEEP_BAR);
      use_xpm(&food_bar,X_BARS, Y_FOOD_BAR);
      use_xpm(&play_bar,X_BARS, Y_PLAY_BAR); 
    }    

    if(mini_game)
    {
      if(lost)
      {
        use_xpm(&minigame_score_menu, 0, 0);
      }
      else if(!mg_enter)
        use_xpm(&mg_menu, 0, 0);
      else if(mg_enter)
      {
        use_xpm(&minigame_sky, 0, 0);
        use_xpm(&counter, X_COUNTER, Y_COUNTER);
        
        if(counter_barra != C00)
        {
          draw_clouds(jump_counter);
          if(lost) 
          {
            use_xpm(&minigame_score_menu, 0, 0);
            counter_barra = C00;
            score_counter += jump_counter;
            //need to show the score_counter on the screen
          }
        }
      }
      
    }
       
    use_xpm(&cursor, pos_x, pos_y);
    DBtoVM();
  }
  return 0;
}


void draw_clouds(int jump_counter){

  switch(jump_counter){
    case 0:      
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_LEFT+78, CLOUD_BOTTOM-50); 
      nuvem = left;
      proxima_nuvem = center;

      break;

    case 1:      
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50); 
      nuvem = center;
      proxima_nuvem = right;
      break;

    case 2:
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_RIGHT+78, CLOUD_BOTTOM-50); 
      nuvem = right;
      proxima_nuvem = center;
      break;

    case 3:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = left;
      break;

    case 4:
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_LEFT+78, CLOUD_BOTTOM-50);
      nuvem = left;
      proxima_nuvem = center;
    
      break;

    case 5:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = left;
      break;

    case 6:
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_LEFT+78, CLOUD_BOTTOM-50);
      nuvem = left;
      proxima_nuvem = center;
      break;

    case 7:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = right;
      break;

    case 8:
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_RIGHT+78, CLOUD_BOTTOM-50);
      nuvem = right;
      proxima_nuvem = center;
      
      break;

    case 9:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = right;
      break;

    case 10:
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_RIGHT+78, CLOUD_BOTTOM-50);
      nuvem = right;
      proxima_nuvem = center;
      break;

    case 11:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = left;
      break;

    case 12:
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_LEFT+78, CLOUD_BOTTOM-50);
      nuvem = left;
      proxima_nuvem = center;
      
      break;

    case 13:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = right;
      break;

    case 14:
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_RIGHT+78, CLOUD_BOTTOM-50);
      nuvem = right;
      proxima_nuvem = center;
      break;

    case 15:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = left;
      break;

    case 16:
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_LEFT+78, CLOUD_BOTTOM-50);
      nuvem = left;
      proxima_nuvem = center;
      
      break;

    case 17:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = left;
      break;

    case 18:
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_LEFT+78, CLOUD_BOTTOM-50);
      nuvem = left;
      proxima_nuvem = center;
      break;

    case 19:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = right;
      break;

    case 20:
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_RIGHT+78, CLOUD_BOTTOM-50);
      nuvem = right;
      proxima_nuvem = center;
      break;

    case 21:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = right;
      break;

    case 22:
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_RIGHT+78, CLOUD_BOTTOM-50);
      nuvem = right;
      proxima_nuvem = center;
      break;

    case 23:
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_CENTER+78, CLOUD_BOTTOM-50);
      nuvem = center;
      proxima_nuvem = left;
      break;

    case 24:
      
      score_counter += jump_counter;  //adds the value of jumps to the score to keep track of it
      jump_counter = 0;               //resets the jumps to zero to start the cloud loop again
      break;    
  }

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
    lost = false;
    jump_counter = 0;
  }
  if(mini_game && scancode[0] == ENTER_BREAK_CODE)
  {
    mg_enter = true;
    lost = false;
  }

  if(mini_game && mg_enter)
  {
    if(nuvem == left && proxima_nuvem == center && scancode[0] == D_BREAK_CODE){
      jump_counter++;
      nuvem = center;
    }

    else if(nuvem == left && proxima_nuvem == center && scancode[0] == A_BREAK_CODE)
    {
      lost = true;
      mg_enter = false;
      counter_barra = C15;
      score_counter += jump_counter;
      jump_counter = 0;
    }     

    else if(nuvem == right && proxima_nuvem == center && scancode[0] == A_BREAK_CODE){
      jump_counter++;
      nuvem = center;
    }

    else if(nuvem == right && proxima_nuvem == center && scancode[0] == D_BREAK_CODE)
    {
      lost = true;
      mg_enter = false;
      counter_barra = C15;
      score_counter += jump_counter;
      jump_counter = 0;
    }    

    else if(nuvem == center && proxima_nuvem == left && scancode[0] == A_BREAK_CODE){
      jump_counter++;
      nuvem = left;
    }

    else if(nuvem == center && proxima_nuvem == left && scancode[0] == D_BREAK_CODE)
    {
      lost = true;
      mg_enter = false;
      counter_barra = C15;
      score_counter += jump_counter;
      jump_counter = 0;
    }    

    else if(nuvem == center && proxima_nuvem == right && scancode[0] == D_BREAK_CODE){
      jump_counter++;
      nuvem = right;
    }

    else if(nuvem == center && proxima_nuvem == right && scancode[0] == A_BREAK_CODE)
    {
      lost = true;
      mg_enter = false;
      counter_barra = C15;
      score_counter += jump_counter;
      jump_counter = 0;
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

    if(choose && pack.lb == 1 && (pos_x >= CHOOSE_RUDOLPH_MIN_X && pos_x <= CHOOSE_RUDOLPH_MAX_X) && (pos_y >= CHOOSE_RUDOLPH_MIN_Y && pos_y <= CHOOSE_RUDOLPH_MAX_Y))
    {
      lobby = true;
      choose = false;
      menu = true;
      sleep_barra = SLEEP_4;
      food_barra = FOOD_4;
      play_barra = PLAY_4;
      counter_barra = C15;
    }
    else if(pack.lb == 1 && (pos_x >= SLEEP_MIN_X && pos_x <= SLEEP_MAX_X) && (pos_y >= SLEEP_MIN_Y && pos_y <= SLEEP_MAX_Y))
    {
      sleeping = true;
      eat = false;
      mini_game = false;
      menu = false;
    }
    else if(pack.lb == 1 && (pos_x >= FOOD_MIN_X && pos_x <= FOOD_MAX_X) && (pos_y >= FOOD_MIN_Y && pos_y <= FOOD_MAX_Y))
    {
      eat = true;
      sleeping = false;
      mini_game = false;
      menu = false;
    }
    else if(pack.lb == 1 && (pos_x >= PLAY_MIN_X && pos_x <= PLAY_MAX_X) && (pos_y >= PLAY_MIN_Y && pos_y <= PLAY_MAX_Y))
    {
      mini_game = true;
      eat = false;
      sleeping = false;
      menu = false;
    }
    else if(eat && pack.lb == 1 && (pos_x >= FOOD_POS_X && pos_y >= FOOD_POS_Y && pos_x < (FOOD_POS_X+100) && pos_y < (FOOD_POS_Y+100)))
    {
      eating_action = true;
    }
    else if(eating_action && pack.lb == 0 && (pos_x >= CHAR_X && pos_y >= CHAR_Y && pos_x < (CHAR_X+320) && pos_y < (CHAR_Y+320)))
    {
      eating_action = false;
      ate = true;
    }
    else if(eating_action && pack.lb == 0 && !(pos_x >= CHAR_X && pos_y >= CHAR_Y && pos_x < (CHAR_X+320) && pos_y < (CHAR_Y+320)))
    {
      eating_action = false;
      ate = false;
    }
    byte_no = 0;
  }
  return 0;
}



