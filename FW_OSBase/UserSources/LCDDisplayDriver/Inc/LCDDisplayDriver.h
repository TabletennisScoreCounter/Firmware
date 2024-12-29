/*
 * LCDDisplayDriver.h
 *
 *  Created on: 2018/02/10
 *      Author: Shuji
 */

#ifndef LCDDISPLAYDRIVER_INC_LCDDISPLAYDRIVER_H_
#define LCDDISPLAYDRIVER_INC_LCDDISPLAYDRIVER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
  LCDDISPLAY_OK = 0,
  LCDDISPLAY_ERROR
}LCDDisplayStatus_t;

LCDDisplayStatus_t Initialize_LCDDisplayDriver();
LCDDisplayStatus_t SetChar_LCDDisplayDriver(uint8_t* str, uint8_t length, uint8_t line);
LCDDisplayStatus_t ClearChar_LCDDisplayDriver();


#ifdef __cplusplus
}
#endif


#endif /* LCDDISPLAYDRIVER_INC_LCDDISPLAYDRIVER_H_ */
