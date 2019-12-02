#ifndef PS2_MOUSE_MACROS
#define PS2_MOUSE_MACROS

#define OBF                     0x01    //status register bit 0
#define PAR_ERR                 0x80    //status register bit 7
#define TIMEOUT                 0x40    //status register bit 6
#define AUX                     0x20    //status register bit 5
#define INH                     0x10    //status register bit 4
#define A2                      0x08    //status register bit 3
#define SYS                     0x04    //status register bit 2
#define IBF                     0x02    //status register bit 1

#define MOUSE_IRQ               12

#define ACK                     0xFA    //acknowledgement byte that everything is OK
#define NACK                    0xFE    //invalid byte
#define ERROR                   0xFC    //second consecutive invalid byte
#define DISABLE_DATA_REPORTING  0xF5    //disable data reporting (in stream mode, should be sent                                              before any other command)
#define ENABLE_DATA_REPORTING   0xF4    //enable data reporting
#define WRITE_MOUSE             0xD4    //write byte to mouse
#define SET_DEFAULT             0xF6    //set default values
#define READ_DATA               0xEB    //read data

#define OUT_BUF                 0x60    //output buffer
#define IN_BUF                  0x60    //input buffer
#define STAT_REG                0x64    //Status register
#define KBC_CMD_REG             0x64
#define READ_CMD                0x20    //read command byte
#define WRITE_CMD               0x60    //write command byte 
#define DIS_MOUSE               0xA7    //disable mouse
#define EN_MOUSE                0xA8    //enable mouse
#define CHECK_MOUSE             0xA9    //check mouse interface


#define RESET                   0xFF    //mouse reset

#define ESC_BREAK_CODE          0x81    //Break code of the Esc key
#define TWO_BYTE_CODE           0xe0    //To test when a code is two bytes long
#define DELAY_US                20000   //delay used in the delay function


#endif
