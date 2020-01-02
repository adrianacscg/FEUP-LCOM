#ifndef _RTC_H_
#define _RTC_H_

typedef struct 
{
  uint8_t secs;
  uint8_t mins;
  uint8_t hours;
}rtc_time;

int rtc_subscribe_int();
int rtc_unsubscribe_int();
void rtc_disable_int();
void rtc_enable_int();
uint8_t rtc_decimal_to_binary(uint8_t date);
uint8_t rtc_read_register(uint32_t port);
void rtc_write_data(uint32_t port, uint32_t data);
void rtc_read_time(rtc_time *time);




#endif
