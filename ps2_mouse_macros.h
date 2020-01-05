#ifndef PS2_MOUSE_MACROS
#define PS2_MOUSE_MACROS

/** @defgroup mouse_macros
 * @{
 *
 * macros of the mouse
 */

#define OBF                     0x01    /**< @brief status register bit 0 */
#define PAR_ERR                 0x80    /**< @brief status register bit 7*/
#define TIMEOUT                 0x40    /**< @brief status register bit 6*/
#define AUX                     0x20    /**< @brief status register bit 5*/
#define INH                     0x10    /**< @brief status register bit 4*/
#define A2                      0x08    /**< @brief status register bit 3*/
#define SYS                     0x04    /**< @brief status register bit 2*/
#define IBF                     0x02    /**< @brief status register bit 1*/

#define MOUSE_IRQ               12      /**< @brief Mouse IRQ */

#define ACK                     0xFA    /**< @brief acknowledgement byte that everything is OK*/
#define NACK                    0xFE    /**< @brief invalid byte*/
#define ERROR                   0xFC    /**< @brief second consecutive invalid byte*/
#define DISABLE_DATA_REPORTING  0xF5    /**< @brief disable data reporting (in stream mode, should be sent                                              before any other command)*/
#define ENABLE_DATA_REPORTING   0xF4    /**< @brief enable data reporting*/
#define WRITE_MOUSE             0xD4    /**< @brief write byte to mouse*/
#define SET_DEFAULT             0xF6    /**< @brief set default values*/
#define READ_DATA               0xEB    /**< @brief read data*/

#define OUT_BUF                 0x60    /**< @brief output buffer*/
#define IN_BUF                  0x60    /**< @brief input buffer*/
#define STAT_REG                0x64    /**< @brief Status register*/
#define KBC_CMD_REG             0x64    /**< @brief KBC command register*/
#define READ_CMD                0x20    /**< @brief read command byte*/
#define WRITE_CMD               0x60    /**< @brief write command byte */
#define DIS_MOUSE               0xA7    /**< @brief disable mouse*/
#define EN_MOUSE                0xA8    /**< @brief enable mouse*/
#define CHECK_MOUSE             0xA9    /**< @brief check mouse interface*/


#define RESET                   0xFF    /**< @brief mouse reset*/

#define ESC_BREAK_CODE          0x81    /**< @brief Break code of the Esc key*/
#define TWO_BYTE_CODE           0xe0    /**< @brief To test when a code is two bytes long*/
#define DELAY_US                20000   /**< @brief delay used in the delay function*/


#endif
