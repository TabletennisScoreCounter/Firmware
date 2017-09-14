/*
 * FullcolorLEDDriver.hpp
 *
 *  Created on: 2017/09/09
 *      Author: Shuji
 */

#ifndef FULLCOLORLEDDRIVER_HPP_
#define FULLCOLORLEDDRIVER_HPP_

#include "gpio.h"

#include "BusOut.hpp"

class FullcolorLEDDriver{
public:
	enum LED_COLOR_t{
		RED,
		GREEN,
		BLUE,
		YELLOW,
		PURPLE
	};
private:
	enum LED_INDEX_t{
		INDEX_RED = 0,
		INDEX_GREEN = 1,
		INDEX_BLUE = 2
	};
private:
	static uint8_t DutyCount[10][3];
	static uint8_t ClassInsatanceCount;
	static GPIO_PORT_NAME_t RedPort[10];
	static GPIO_PORT_NAME_t GreenPort[10];
	static GPIO_PORT_NAME_t BluePort[10];
	uint8_t ClassInstanceIndex;
	uint8_t Duty;
	uint8_t RedRate;
	uint8_t GreenRate;
	uint8_t BlueRate;
public:
	FullcolorLEDDriver(GPIO_PORT_NAME_t redPort, GPIO_PORT_NAME_t greenPort, GPIO_PORT_NAME_t bluePort);
	void setColor(LED_COLOR_t color);
	void setDuty(uint8_t duty);
private:
	void setRedRate(uint8_t rate);
	void setGreenRate(uint8_t rate);
	void setBlueRate(uint8_t rate);
	static void callBack();

};


#endif /* FULLCOLORLEDDRIVER_HPP_ */
