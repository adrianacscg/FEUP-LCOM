#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  
  *lsb = val & 0x00FF;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  
  *msb = val >> 8;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {     //wrapper to sys_inb()
  
  
  uint32_t var1;
 
  if(!sys_inb(port, &var1)){
    
    *value = (uint8_t) var1;
    return 0;

  }

  return 1;
}

