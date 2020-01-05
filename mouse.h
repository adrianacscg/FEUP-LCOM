#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>

/** @defgroup mouse
 * @{
 *
 * mouse main functions
 */

/**
 * @brief Function that reverts the cpl2 value of the byte[1] (xDelta) of the mouse packet
 * 
 * @param byte byte[1] of the mouse packet
 * 
 * @return Returns the new value of the byte
 */
uint16_t cpl2_revert_x(uint8_t byte);

/**
 * @brief Function that reverts the cpl2 value of the byte[2] (YDelta) of the mouse packet
 * 
 * @param byte byte[2] of the mouse packet
 * 
 * @return Returns the new value of the byte
 */
uint16_t cpl2_revert_y(uint8_t byte);

/**
 * @brief Function that builds a mouse packet
 * 
 * @param pack pointer to a struct packet of the mouse packet that is gonna be built
 */
void build_packet(struct packet * pack);

/**
 * @brief Function that subscribes mouse interruptions
 * 
 * @return Return 0 upon success
 */
int mouse_subscribe_int(uint8_t *bit_no);

/**
 * @brief Function that unsubscribes mouse interruptions
 * 
 * @return Return 0 upon success
 */
int mouse_unsubscribe_int();

/**
 * @brief Mouse interrupt handler
 * 
 */
void(mouse_ih)();

/**
 * @brief Function that disables the mouse data reporting
 * 
 * @return Returns 0 upon success
 */
int (mouse_disable_data_reporting)();

/**
 * @brief Function that enables the mouse data reporting
 * 
 * @return Returns 0 upon success
 */
int (mouse_enable_datarp)();

/**
 * @brief Function that saves a command in the keyboard command register
 * 
 * @param command command that is gonna be saved
 * 
 * @return Returns 0 upon success
 */
int (send_command)(uint8_t command);

/**
 * @brief Function that writes an argument in the output buffer
 * 
 * @param argument command that is gonna be written
 * 
 * @return Returns 0 upon success
 */
int (write_argument)(uint8_t argument);

/**
 * @brief Function that sets the stream mode
 * 
 * @return Returns 0 upon success
 */
int (set_stream_mode)();

/**
 * @brief Function that sends a command to read data from the mouse
 * 
 * @return Returns 0 upon success
 */
int (read_data)();

