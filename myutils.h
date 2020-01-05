#ifndef _MYUTILS_H_
#define _MYUTILS_H_

#include <stdint.h>

/** @defgroup myutils
 * @{
 *
 * some functions
 */

/**
 * @brief Function that gets the smallest of 2 numbers
 * 
 * @param a one of the numbers that is being compared
 * @param b the other number that is being compared
 * 
 * @return Return the smallest number
 */
int32_t min(int32_t a, int32_t b);

/**
 * @brief Function that gets the bigger of 2 numbers
 * 
 * @param a one of the numbers that is being compared
 * @param b the other number that is being compared
 * 
 * @return Return the bigger number
 */
int32_t max(int32_t a, int32_t b);

#endif
