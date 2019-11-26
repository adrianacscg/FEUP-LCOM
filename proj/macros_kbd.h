
#ifndef _KDB_MACROS_H_
#define _KDB_MACROS_H_

#define OBF                     0x01    //status register bit 0
#define PAR_ERR                 0x80    //status register bit 7
#define TIMEOUT                 0x40    //status register bit 6
#define AUX                     0x20    //status register bit 5
#define INH                     0x10    //status register bit 4
#define A2                      0x08    //status register bit 3
#define SYS                     0x04    //status register bit 2
#define IBF                     0x02    //status register bit 1
#define KBD_IRQ                 1
#define OUT_BUF                 0x60    //output buffer
#define IN_BUF                  0x60    //input buffer
#define STAT_REG                0x64    //Status register
#define KBC_CMD_REG             0x64
#define READ_CMD                0x20    //read command byte
#define WRITE_CMD               0x60    //write command byte 

#define ESC_BREAK_CODE          0x81    //Break code of the Esc key
#define TWO_BYTE_CODE           0xe0    //To test when a code is two bytes long
#define DELAY_US                20000   //delay used in the delay function


#endif
