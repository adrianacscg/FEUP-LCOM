#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int hook_id;
unsigned int timer_counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  if (freq < 19 || freq > TIMER_FREQ) return EXIT_FAILURE;
  if(timer == 0 || timer == 1 || timer == 2){ 
    uint16_t n_inicial_counter;
    uint8_t status_byte, control_word, n_lsb, n_msb;
    uint8_t lsb_st;
    timer_get_conf(timer, &status_byte);
    lsb_st = status_byte & 0x0F;                                          //keep 4 least significant bits of status_byte (mode, BCD)
    switch (timer)
    {
      case 0:
        control_word = TIMER_SEL0 | TIMER_LSB_MSB | lsb_st;
        break;
      case 1:
        control_word = TIMER_SEL1 | TIMER_LSB_MSB | lsb_st;
        break;
      case 2:
        control_word = TIMER_SEL2 | TIMER_LSB_MSB | lsb_st;
        break;
      default:
        return 1;
    }
    // control word: D7-D6: select counter (0,1,2); D5-D4: Read/write least significant byte first, then most significant byte; D3-D0: mode, BCD
    sys_outb(TIMER_CTRL, control_word);                                   // For each counter, the control word must be written before the initial count is written

    n_inicial_counter = TIMER_FREQ / freq;                                //freq: 1193182 / n inicial counter

    util_get_LSB(n_inicial_counter, &n_lsb);
    util_get_MSB(n_inicial_counter, &n_msb);
    // sys_outb only accepts 8 bits arguments and the n has 16 bits, so the utils functions get the lsb and the msb
    switch (timer)
    {
      case 0:
        sys_outb(TIMER_0, n_lsb);
        sys_outb(TIMER_0, n_msb);
        break;
      case 1:
        sys_outb(TIMER_1, n_lsb);
        sys_outb(TIMER_1, n_msb);
        break;
      case 2:
        sys_outb(TIMER_2, n_lsb);
        sys_outb(TIMER_2, n_msb);
        break;
      default:
        return 1;
    }
    return 0;
    //lsb->msb ------> n initial counter
  }
  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {

  *bit_no = hook_id;
  return sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id);
  // used to subscribe a notification on every interrup in the input TIMER0_IRQ
}

int (timer_unsubscribe_int)() {
  
  return sys_irqrmpolicy(&hook_id);
  // used to unsubscribe a previous subscription of the interrupt notification associated with the specified hook_id (new value of hook_id)
}

void (timer_int_handler)() {

  timer_counter ++;
  //increments counter
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  
  if(timer == 0 || timer == 1 || timer == 2){
    uint32_t read_back;

    read_back = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);      // 11000000 | 00100000 | 00001000 ou 00000100 ou 00000010
    if(!sys_outb(TIMER_CTRL, read_back)){                                  //read_back |   count  | timer 0  ou timer 1  ou timer 2

      
      if(timer == 0) util_sys_inb(TIMER_0, st);                            //read status of the selected timer and store the value in st
      if(timer == 1) util_sys_inb(TIMER_1, st);
      if(timer == 2) util_sys_inb(TIMER_2, st);
                                      
      return 0;
    }   
  }
  return 1;

}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  
  union timer_status_field_val status_field_val;            //declares a variable of type union time_status_field_val

  //useful variables
  uint8_t var_bits123 = (BIT(1) | BIT(2) | BIT(3));         //creates a variable with the binary 00001110
  uint8_t counting_mode = (var_bits123 & st);               //counting_mode takes the value of the bits 1, 2 and 3 from st
  counting_mode>>= 1;

  uint8_t var_bits45 = (BIT(5) | BIT(4));                   //creates a variable with the binary 00110000
  uint8_t initialization_mode = (var_bits45 & st);          //initialization_mode takes the value of the bits 4 and 5 from st
  initialization_mode>>= 4;

  switch (field)
  {
    case tsf_all:                                           //prints all bits in hexadecimal

      status_field_val.byte = st;                           //value of st attributed to the union attribute byte
      break;
  
    case tsf_initial:                                       //only prints timer initialization mode

      switch (initialization_mode)
      {
      case 0:                                               // 00 -> INVAL_val
        status_field_val.in_mode = INVAL_val;               //value of INVAL_val attributed to the union attribute in_mode
        break;
      
      case 1:                                               // 01 -> LSB_only
        status_field_val.in_mode = LSB_only;                //value of LSB_only attributed to the union attribute in_mode
        break;

      case 2:                                               // 10 -> MSB_only
        status_field_val.in_mode = MSB_only;                //value of MSB_only attributed to the union attribute in_mode
        break;

      case 3:                                               // 11 -> MSB_after_LSB
        status_field_val.in_mode = MSB_after_LSB;           //value of MSB_after_LSB attributed to the union attribute in_mode
        break;
      }
      break;
    case tsf_mode:                                          //only prints timer counting mode

      if(counting_mode == 6) 
        status_field_val.count_mode = 2;

      else if (counting_mode == 7)
        status_field_val.count_mode = 3;
      
      else
        status_field_val.count_mode = counting_mode;        //value of counting_mode attributed to the union attribute count_mode
            
      break;

    case tsf_base:                                          //only prints timer counting base

      if(BIT(0)==(st & BIT(0))){                            //if the first bit of st is 1, then the counting base is BCD

        bool counting_base = true;                          //counting_base is true if BCD
        status_field_val.bcd = counting_base;
      }
      else                                                  //if the first bit of st is 0, then the counting base is binary
      {
        bool counting_base = false;                         //counting_base is false if binary
        status_field_val.bcd = counting_base;
      }
      break;

  
  }
  timer_print_config(timer, field, status_field_val);

  return 1;
}
