#include <stdbool.h>
#include <stdint.h>

/** @defgroup keyboard
 * @{
 *
 * Main Functions of the Keyboard
 */

/**
 * @brief Function that subscribes keyboard interruptions
 * 
 * @return Return 0 upon success
 */
int (kbd_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Function that unsubscribes keyboard interruptions
 * 
 * @return Return 0 upon success
 */
int (kbd_unsubscribe_int)();

/**
 * @brief Function that decides if the code obtained is a break code or a make code
 * 
 * @return Return true if it's a make code. False otherwise
 */
bool (breakormake)(uint8_t scancode);

/**
 * @brief keyboard's interrupt handler
 * 
 */
void(kbc_ih)();
