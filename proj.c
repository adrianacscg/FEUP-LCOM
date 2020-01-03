// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you
#include <video_card_macros.h>
#include <macros_kbd.h>
#include <i8254.h>
#include <ps2_mouse_macros.h>
#include <video_card.h>
#include <mouse.h>
#include <timer.h>
#include <keyboard.h>
#include <macros_proj.h>
#include "main_functions.h"
#include "loading_xpms.h"
#include "rtc.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}
/*GLOBAL VARIABLES*/
extern uint8_t scancode[2];
extern bool two_byte_scan;
extern struct packet pack;
extern int byte_no;
int pos_x = 640, pos_y = 512;
extern int hook_id_mouse;

/*BOOLS - a mudar para enum*/
bool loading = true, choose = false, menu = false, eat = false, sleeping = false, mini_game = false, eating_action = false, lobby = false, ate = false, mg_enter = false, lost = false, start_again = false;

int(proj_main_loop)(int argc, char *argv[]) {
  
  int ipc_status;
  message msg;
  uint8_t bit_no_kbd, bit_no_timer, bit_no_mouse;
  uint32_t r;
  int irq_set_kbd = BIT(1), irq_set_timer = BIT(0), irq_set_mouse = BIT(12), irq_set_rtc = BIT(8);
  scancode[0] = 0;
  two_byte_scan = false;

  loading_xpms();
  
  set_graphics_mode(0x117);

  if (kbd_subscribe_int(&bit_no_kbd) != 0) {
    printf("Error subscribing");
    return 1;
  }
  if (mouse_subscribe_int(&bit_no_mouse) != 0) {
    printf("Error subscribing");
    return 1;
  }

  if (rtc_subscribe_int() != 0) {
    printf("Error subscribing");
    return 1;
  }

  rtc_enable_int();

  sys_irqdisable(&hook_id_mouse);

  mouse_enable_data_reporting();

  sys_irqenable(&hook_id_mouse);
  
  if (timer_subscribe_int(&bit_no_timer) != 0) {
    printf("Error subscribing");
    return 1;
  }

  while (scancode[0] != ESC_BREAK_CODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_mouse) {

            mouse_manager();
            
          }
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_manager();
            
          }
          if (msg.m_notify.interrupts & irq_set_kbd) {
            keyboard_manager();

          }
          if (msg.m_notify.interrupts & irq_set_rtc) {
            rtc_manager();
          }  
          break;
        default:
          break;
      }
    }
    else {
    }
  }


  if (kbd_unsubscribe_int() != 0) {
    printf("Error unsubscribing");
    return 1;
  }
  if (mouse_unsubscribe_int() != 0) {
    printf("Error unsubscribing");
    return 1;
  }
  if (timer_unsubscribe_int() != 0) {
    printf("Error unsubscribing");
    return 1;
  }
  
  mouse_disable_data_reporting();
  rtc_disable_int();
  vg_exit();

  return 0;
}
