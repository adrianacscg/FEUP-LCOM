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
#include "rtc.h"

extern uint8_t scancode[2];
extern bool two_byte_scan;
extern struct packet pack;
extern int byte_no;
extern unsigned int timer_counter;
extern uint16_t pos_x, pos_y;
extern bool loading, choose, menu, eat, sleeping, mini_game, eating_action, lobby, ate, mg_enter, lost, start_again;
extern uint16_t xres, yres;
extern xpm_image_t load_bc, choose_character, cursor, border, not_implemented, day, night;
extern xpm_image_t rudolph_meio_baixo, rudolph_meio_cima, rudolph_esquerda_cima, rudolph_esquerda_baixo, rudolph_direita_cima, rudolph_direita_baixo;
extern xpm_image_t chicken_leg;
extern xpm_image_t minigame_sky, cloud, mg_menu, rudolph_cloud, score, score_ingame;
extern xpm_image_t n1, n2, n3, n4, n5, n6, n7, n8, n9, n0;
extern xpm_image_t n1g, n2g, n3g, n4g, n5g, n6g, n7g, n8g, n9g, n0g;
extern xpm_image_t time_00, time_01, time_02, time_03, time_04, time_05, time_06, time_07, time_08, time_09, time_10, time_11, time_12, time_13, time_14, time_15, time_16, time_17, time_18, time_19, time_20, time_21, time_22, time_23, time_24, time_25, time_26, time_27, time_28, time_29, time_30, time_31, time_32, time_33, time_34, time_35, time_36, time_37, time_38, time_39, time_40, time_41, time_42, time_43, time_44, time_45, time_46, time_47, time_48, time_49, time_50, time_51, time_52, time_53, time_54, time_55, time_56, time_57, time_58, time_59;

extern enum sleep_bar sleep_barra;
extern enum food_bar food_barra;
extern enum play_bar play_barra;
extern enum counter_bar counter_barra;
static enum cloud_position nuvem = left;
enum cloud_position proxima_nuvem;
int jump_counter = 0;
int score_counter = 0;

rtc_time real_time;

extern bool update_rtc_time;   //bool que vem do interrupt handler do rtc
bool update_rtc;    //bool para ser usado na timer_manager e ser feito update na rtc_manager


int timer_manager()
{
  xpm_image_t character;
  xpm_image_t sleep_bar, food_bar, play_bar;
  xpm_image_t counter;
  xpm_image_t sg1;
  xpm_image_t s1;
  xpm_image_t sg2;
  xpm_image_t s2;
  xpm_image_t rtc_horas, rtc_minutos;

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

      
      rtc_horas = decide_hours(&real_time);
      rtc_minutos = decide_minutes(&real_time);
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
      
      if(true){   //this is if(true) because i'm testing stuff, it should be if(update_rtc)
        rtc_horas = decide_hours(&real_time);
        rtc_minutos = decide_minutes(&real_time);
        use_xpm(&rtc_horas,X_COUNTER ,150);   
        use_xpm(&rtc_minutos,X_COUNTER + 150 ,150);   
      }
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

      sg1 = decide_score_1_game();
      sg2 = decide_score_2_game();
      s1 = decide_score_1();
      s2 = decide_score_2();

      if(lost)
      {
        use_xpm(&minigame_sky, 0, 0);
        use_xpm(&score, 117, 260);
        use_xpm(&s1, 646, 330);
        use_xpm(&s2, 571, 330);
      }
      else if(!mg_enter)
        use_xpm(&mg_menu, 0, 0);
      else if(mg_enter)
      {
        use_xpm(&minigame_sky, 0, 0);
        use_xpm(&counter, X_COUNTER, Y_COUNTER);
        use_xpm(&score_ingame, 70, 140);
        use_xpm(&sg2, 215, 135);
        use_xpm(&sg1, 240, 135);
        
        if(counter_barra != C00)
        {
          draw_clouds(jump_counter);
          if(lost) 
          {
            use_xpm(&minigame_sky, 0, 0);
            use_xpm(&score, 117, 260);
            use_xpm(&s1, 646, 309);
            use_xpm(&s2, 571, 309);
            counter_barra = C00;
            score_counter += jump_counter;
          }
        }
        else if (counter_barra == C00)
        {
          lost = true;
          start_again = true;
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
      use_xpm(&cloud, CLOUD_LEFT, CLOUD_BOTTOM);
      use_xpm(&cloud, CLOUD_CENTER, CLOUD_MIDDLE);
      use_xpm(&cloud, CLOUD_RIGHT, CLOUD_TOP);
      use_xpm(&rudolph_cloud, CLOUD_LEFT+78, CLOUD_BOTTOM-50);
      nuvem = left;
      proxima_nuvem = center;
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
    score_counter = 0;
  }


  if(mini_game && mg_enter)
  {
    if(start_again && scancode[0] == ENTER_BREAK_CODE)
    {
      mg_enter = false;
      lost = false;
      start_again = false;
    }

    if(nuvem == left && proxima_nuvem == center && scancode[0] == D_BREAK_CODE){
      jump_counter++;
      score_counter++;
      nuvem = center;
    }

    else if(nuvem == left && proxima_nuvem == center && scancode[0] == A_BREAK_CODE)
    {
      lost = true;
      start_again = true;
      counter_barra = C15;
      jump_counter = 0;
    }     

    else if(nuvem == right && proxima_nuvem == center && scancode[0] == A_BREAK_CODE){
      jump_counter++;
      score_counter++;
      nuvem = center;
    }

    else if(nuvem == right && proxima_nuvem == center && scancode[0] == D_BREAK_CODE)
    {
      lost = true;
      start_again = true;
      counter_barra = C15;
      jump_counter = 0;
    }    

    else if(nuvem == center && proxima_nuvem == left && scancode[0] == A_BREAK_CODE){
      jump_counter++;
      score_counter++;
      nuvem = left;
    }

    else if(nuvem == center && proxima_nuvem == left && scancode[0] == D_BREAK_CODE)
    {
      lost = true;
      start_again = true;
      counter_barra = C15;
      jump_counter = 0;
    }    

    else if(nuvem == center && proxima_nuvem == right && scancode[0] == D_BREAK_CODE){
      jump_counter++;
      score_counter++;
      nuvem = right;
    }

    else if(nuvem == center && proxima_nuvem == right && scancode[0] == A_BREAK_CODE)
    {
      lost = true;
      start_again = true;
      counter_barra = C15;
      jump_counter = 0;
    }
    if(jump_counter == 25 && scancode[0] == D_BREAK_CODE)
    {
      jump_counter= 1;
      score_counter++;
      nuvem = center;
    }
    if(jump_counter == 25 && scancode[0] == A_BREAK_CODE)
    {
      lost = true;
      start_again = true;
      counter_barra = C15;
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


int rtc_manager(){
  rtc_read_time(&real_time);
  rtc_ih();
  
  if(update_rtc_time == true){
    rtc_read_time(&real_time);
    update_rtc = true;
  }
  else{
    update_rtc = false;
  }

  return 0;

}

