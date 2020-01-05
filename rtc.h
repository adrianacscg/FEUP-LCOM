#ifndef _RTC_H_
#define _RTC_H_

/** @defgroup rtc
 * @{
 *
 * rtc variable and functions
 */

/**
 * @brief Struct that stores the information of the RTC hours, minutes and seconds
 * 
 * secs is the seconds of the RTC
 * mins is the minutes of the RTC
 * hours is the hours of the RTC
 */
typedef struct 
{
  uint8_t secs;
  uint8_t mins;
  uint8_t hours;
}rtc_time;

/**
 * @brief Function that subscribes RTC interruptions
 * 
 * @return Return 0 upon success
 */
int rtc_subscribe_int();

/**
 * @brief Function that unsubscribes RTC interruptions
 * 
 * @return Return 0 upon success
 */
int rtc_unsubscribe_int();

/**
 * @brief Function that disables RTC interruptions
 * 
 * @return Return 0 upon success
 */
void rtc_disable_int();

/**
 * @brief Function that enables RTC interruptions
 * 
 * @return Return 0 upon success
 */
void rtc_enable_int();

/**
 * @brief Function that converts the variable date from decimal to binary
 * 
 * @param date variable tha is converted (hours, minutes or seconds)
 * 
 * @return date after being converted
 */
uint8_t rtc_decimal_to_binary(uint8_t date);

/**
 * @brief Function that reads from the register and reads on the returned variable
 * 
 * @param port register wich you want to read from
 * 
 * @return data from the register
 */
uint8_t rtc_read_register(uint32_t port);

/**
 * @brief Function that writes data to a register
 * 
 * @param port register in which you want to write
 * @param data value that is gonna be written to the register
 */
void rtc_write_data(uint32_t port, uint32_t data);

/**
 * @brief Function that reads RTC's hours, minutes and seconds and saves it on the RTC time struct
 * 
 * @param time pointer to a variable of type struct rtc_time
 * 
 */
void rtc_read_time(rtc_time *time);

/**
 * @brief RTC's interrupt handler
 * 
 */
void rtc_ih();




#endif
