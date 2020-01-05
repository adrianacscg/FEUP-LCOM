
#ifndef _KDB_MACROS_H_
#define _KDB_MACROS_H_

/** @defgroup keyboard_macros
 * @{
 *
 * Keyboard macros
 */

#define OBF                     0x01    /**< @brief status register bit 0 */
#define PAR_ERR                 0x80    /**< @brief status register bit 7 */
#define TIMEOUT                 0x40    /**< @brief status register bit 6 */
#define AUX                     0x20    /**< @brief status register bit 5 */
#define INH                     0x10    /**< @brief status register bit 4 */
#define A2                      0x08    /**< @brief status register bit 3 */
#define SYS                     0x04    /**< @brief status register bit 2 */
#define IBF                     0x02    /**< @brief status register bit 1 */
#define KBD_IRQ                 1
#define OUT_BUF                 0x60    /**< @brief output buffer */
#define IN_BUF                  0x60    /**< @brief input buffer */
#define STAT_REG                0x64    /**< @brief Status register */
#define KBC_CMD_REG             0x64    /**< @brief kbc command register */
#define READ_CMD                0x20    /**< @brief read command byte */
#define WRITE_CMD               0x60    /**< @brief write command byte */

#define ENTER_BREAK_CODE        0x9c    /**< @brief enter break code */
#define ERASE_BREAK_CODE        0x8e    /**< @brief erase break code */
#define ESC_BREAK_CODE          0x81    /**< @brief Break code of the Esc key*/
#define TWO_BYTE_CODE           0xe0    /**< @brief To test when a code is two bytes long*/
#define DELAY_US                20000   /**< @brief delay used in the delay function*/

#define RIGHT_ARROW_BREAK_CODE  0xCDE0  /**< @brief right arrow break code */
#define LEFT_ARROW_BREAK_CODE   0xCBE0  /**< @brief left arrow break code */
#define A_BREAK_CODE            0x9E    /**< @brief a break code */
#define D_BREAK_CODE            0xA0    /**< @brief d break code */






#endif
