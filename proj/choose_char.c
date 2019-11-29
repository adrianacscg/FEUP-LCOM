#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include <video_card.h>
#include <video_card_macros.h>
#include <keyboard.h>
#include <macros_kbd.h>


#include "xpms/choose_char_1.xpm"
#include "xpms/choose_char_2.xpm"

int EXIT;
extern uint8_t scancode[2];
extern bool two_byte_scan;

int choose_character()
{
  
  sleep(5);
  if(scancode[0] == ENTER_BREAK_CODE)
  {
    use_xpm(choose_char_1_xpm, 0, 0);
    sleep(5);
  }

  
  EXIT = 1;

  return 0;
}

