// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you
#include <video_card_macros.h>
#include <video_card.h>
#include <macros_proj.h>
#include <macros_kbd.h>

#include "reindeer.xpm"

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

extern uint8_t scancode[2];
extern bool two_byte_scan;
static mmap_t mem_map;

int(proj_main_loop)(int argc, char *argv[]) {

 if (set_graphics_mode(BIT32) != 0) {
    vg_exit();
    printf("Failed to set graphic mode\n");
    return 1;
  }

  use_xpm(reindeer_xpm, 100, 100);

  sleep(5);
  vg_exit();
  lm_free(&mem_map);
  return 0;
}
