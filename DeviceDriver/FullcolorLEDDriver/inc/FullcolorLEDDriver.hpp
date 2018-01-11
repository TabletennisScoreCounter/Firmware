/*
 * FullcolorLEDDriver.hpp
 *
 *  Created on: 2017/09/18
 *      Author: Shuji
 */

#ifndef FULLCOLORLEDDRIVER_HPP_
#define FULLCOLORLEDDRIVER_HPP_

#include "tim.h"

struct LEDPWMPort_t{
	GPIO_PORT_NAME_t PortName;
	TIM_HandleTypeDef* TimerHandle;
	uint32_t TimerChannel;
};

class FullcolorLEDDriver{
public:
	enum LEDCOLOR_t{
		RED,
		GREEN,
		BLUE,
		YELLOW,
		PURPLE
	};
private:
	enum LED_ELEMENT_INDEX_t{
		RED_ELEMENT = 0,
		GREEN_ELEMENT = 1,
		BLUE_ELEMENT = 2
	};
public:
	FullcolorLEDDriver(LEDPWMPort_t redPort, LEDPWMPort_t greenPort, LEDPWMPort_t bluePort);
	~FullcolorLEDDriver();
	void setDuty(uint8_t dutyPercent);
	void setColor(LEDCOLOR_t color);
private:
	TIM_HandleTypeDef* htim[3];
	uint32_t TimerChannel[3];
	GPIO_PORT_NAME_t PortName[3];
	uint8_t Duty;
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
	void setColorParam(uint8_t red, uint8_t green, uint8_t blue);
};



#endif /* FULLCOLORLEDDRIVER_HPP_ */
