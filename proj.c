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

#include "xpms/loading.xpm"
#include <state_machine.h>

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

extern int EXIT;
extern uint8_t scancode[2];
extern bool two_byte_scan;
static mmap_t mem_map;

int(proj_main_loop)(int argc, char *argv[]) {
  int ipc_status;
  message msg;
  uint8_t bit_no;
  uint32_t r;
  int irq_timer = BIT(TIMER0_IRQ);
  int irq_kbd = BIT(KBD_IRQ);
  int irq_mouse = BIT(MOUSE_IRQ);
  
  EXIT = 0;

  mouse_enable_datarp();
  set_graphics_mode(0x11a);

  if (mouse_subscribe_int(&bit_no) != 0) {
    printf("Error subscribing");
    return 1;
  }

  if (timer_subscribe_int(&bit_no) != 0) {
    printf("Error subscribing");
    return 1;
  }

  if (kbd_subscribe_int(&bit_no) != 0) {
    printf("Error subscribing");
    return 1;
  }
  while (EXIT != 1) {
    // Get a request message.
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { // received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                               /*hardware interrupt notification*/
          if (msg.m_notify.interrupts & irq_timer) {
            timer_int_handler();

          }
          if (msg.m_notify.interrupts & irq_kbd) {
            kbc_ih();
            //enum == INIT
            // print xpm de loading
            //if INIT == choose character (after enter)
            //
            use_xpm(loading_xpm, 0, 0);
            
          }
          if (msg.m_notify.interrupts & irq_mouse) {
            mouse_ih();

          }
          break;
        default:
          break; /*no other notifications expected: do nothing*/
      }
    }
    else { // received a standard message, not a notification
           // no standard messages expected: do nothing
    }
  }

  if (mouse_unsubscribe_int() != 0) {
    printf("Error unsubscribing");
    return 1;
  }

  if (timer_unsubscribe_int() != 0) {
    printf("Error subscribing");
    return 1;
  }

  if (kbd_unsubscribe_int() != 0) {
    printf("Error unsubscribing");
    return 1;
  }


  

  mouse_disable_data_reporting();
  vg_exit();
  lm_free(&mem_map);
  return 0;
}
