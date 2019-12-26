#include <keyboard.h>
#include <lcom/lcf.h>
#include <macros_kbd.h>
#include <stdint.h>

/*global variables*/
uint8_t statusReg;
uint8_t scancode[2];
int hook_id_kbd;
bool two_byte_scan = false;
int counter;


/*interrupt handler*/
void(kbc_ih)() {
  uint8_t stat;
  uint8_t data;

  util_sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
/*loop while 8042 output buffer is empty*/
#ifdef LAB3
  counter++;
#endif
  if (stat & OBF) {
    if ((stat & (PAR_ERR | TIMEOUT | AUX)) == 0) {

      util_sys_inb(OUT_BUF, &data);
#ifdef LAB3
      counter++;
#endif
      if (two_byte_scan) {
        scancode[1] = data;
        two_byte_scan = false;
      }
      else {
        scancode[0] = data;
        if (data == TWO_BYTE_CODE) {
          two_byte_scan = true;
        }
      }
    }
  }
}

//define if it's a break or make code for the print function
bool(breakormake)(uint8_t scancode) {
  uint8_t scancode_bit = (uint8_t) scancode;
  if (scancode_bit & BIT(7)) {
    return false;
  }
  else {
    return true;
  }
}

int kbd_subscribe_int(uint8_t *bit_no) {
  hook_id_kbd = KBD_IRQ;
  *bit_no = hook_id_kbd;

  return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_kbd);
}

int kbd_unsubscribe_int() {
  return sys_irqrmpolicy(&hook_id_kbd);

  // used to unsubscribe a previous subscription of the interrupt notification associated with the specified hook_id (new value of hook_id)
}
