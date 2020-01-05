#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "rtc.h"
#include "macros_proj.h"

int rtc_HookId = RTC_IRQ;
bool update_rtc_time;

int rtc_subscribe_int(){  

  sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &rtc_HookId);
  sys_irqenable(&rtc_HookId);

  return 0;

}

int rtc_unsubscribe_int(){
 return sys_irqrmpolicy(&rtc_HookId);
}

void rtc_disable_int(){
  uint8_t register_b = rtc_read_register(REG_B);
  register_b &= ~BIT(4);

  rtc_write_data(REG_B, register_b);
}

void rtc_enable_int(){
  uint8_t register_b = rtc_read_register(REG_B);
  register_b |= BIT(4);

  rtc_write_data(REG_B, register_b);
}

uint8_t rtc_decimal_to_binary(uint8_t date){
  date = (((date & 0xF0) >> 4) * 10 + (date & 0x0F));
  return date;
}

uint8_t rtc_read_register(uint32_t port){
  uint8_t data;

  sys_outb(RTC_ADDR_REG, port);
  util_sys_inb(RTC_DATA_REG, &data);

  return data;
}

void rtc_write_data(uint32_t port, uint32_t data){
  sys_outb(RTC_ADDR_REG, port);
  sys_outb(RTC_DATA_REG, data);
}

void rtc_read_time(rtc_time *time){     //Reads RTC's hours, minutes and seconds and saves it on the RTC time struct
  bool bcd = true;
  uint8_t register_b = rtc_read_register(REG_B);
  uint8_t var1 = register_b;

  if (register_b & BIT(2)) bcd = false;

  register_b |= BIT(7);
  rtc_write_data(REG_B, register_b);

  time->hours = rtc_read_register(RTC_HOURS);
  time->mins = rtc_read_register(RTC_MINS);
  time->secs = rtc_read_register(RTC_SECS);

  if (bcd){
    time->hours = rtc_decimal_to_binary(time->hours);
    time->mins = rtc_decimal_to_binary(time->mins);
    time->secs = rtc_decimal_to_binary(time->secs);
  }

  var1 &= ~BIT(7);
  rtc_write_data(REG_B, var1);
}

void rtc_ih(){

  uint8_t register_c = rtc_read_register(REG_C);

  if((register_c & HOURS_ALARM_INTERRUPT) || (register_c & MINUTES_ALARM_INTERRUPT) ){
    update_rtc_time = true;
  }

}
