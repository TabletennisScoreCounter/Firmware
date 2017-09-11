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
public:
	FullcolorLEDDriver(GPIO_PORT_NAME_t redPort, GPIO_PORT_NAME_t greenPort, GPIO_PORT_NAME_t bluePort);
	void setColor(LED_COLOR_t color);
private:
	void setRedRate(uint8_t rate);
	void setGreenRate(uint8_t rate);
	void setBlueRate(uint8_t rate);

};


#endif /* FULLCOLORLEDDRIVER_HPP_ */
