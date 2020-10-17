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

#include "i2c.h"

void initialize_LCDDisplayDriver();
void setChar_LCDDisplayDriver(uint8_t* str, uint8_t length, uint8_t line);
void clearChar_LCDDisplayDriver();


#ifdef __cplusplus
}
#endif


#endif /* LCDDISPLAYDRIVER_INC_LCDDISPLAYDRIVER_H_ */
