#include <stdbool.h>
#include <stdint.h>


int (kbd_subscribe_int)(uint8_t *bit_no);
int (kbd_unsubscribe_int)();
bool (breakormake)(uint8_t scancode);
void (kbc_ih)();
