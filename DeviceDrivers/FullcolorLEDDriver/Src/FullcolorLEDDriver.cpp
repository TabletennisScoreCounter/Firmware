/*
 * FullcolorLEDDriver.cpp
 *
 *  Created on: 2017/09/18
 *      Author: Shuji
 */

#include "../Inc/FullcolorLEDDriver.hpp"

FullcolorLEDDriver::FullcolorLEDDriver(LEDPWMPort_t redPort, LEDPWMPort_t greenPort, LEDPWMPort_t bluePort)
{
	Duty = 0;
	Red = 0;
	Green = 0;
	Blue = 0;

	this->PortName[RED_ELEMENT] = redPort.PortName;
	this->htim[RED_ELEMENT] = redPort.TimerHandle;
	this->TimerChannel[RED_ELEMENT] = redPort.TimerChannel;

	this->PortName[GREEN_ELEMENT] = greenPort.PortName;
	this->htim[GREEN_ELEMENT] = greenPort.TimerHandle;
	this->TimerChannel[GREEN_ELEMENT] = greenPort.TimerChannel;

	this->PortName[BLUE_ELEMENT] = bluePort.PortName;
	this->htim[BLUE_ELEMENT] = bluePort.TimerHandle;
	this->TimerChannel[BLUE_ELEMENT] = bluePort.TimerChannel;

	for(int i = 0; i < 3; i++){
		HAL_TIM_PWM_Start(htim[i], TimerChannel[i]);
	}
}
FullcolorLEDDriver::~FullcolorLEDDriver()
{
	for(int i = 0; i < 3; i++){
		HAL_TIM_PWM_Stop(htim[i], TimerChannel[i]);
	}
}
void FullcolorLEDDriver::setDuty(uint8_t dutyPercent)
{
	Duty = dutyPercent;
	setColorParam(Red, Green, Blue);
}
void FullcolorLEDDriver::setColor(LEDCOLOR_t color)
{
	switch(color){
	case RED: //(R,G,B) = (255,0,0)
		setColorParam(255,0,0);
		break;
	case GREEN: //(R,G,B) = (0,255,0)
		setColorParam(0,255,0);
		break;
	case BLUE: //(R,G,B) = (0,0,255)
		setColorParam(0,0,255);
		break;
	case PURPLE: //(R,G,B) = (122,0,122)
		setColorParam(122,0,122);
		break;
	case YELLOW: //(R,G,B) = (122,122,0)
		setColorParam(122,122,0);
		break;
	default:
		break;
	}
}
void FullcolorLEDDriver::setColorParam(uint8_t red, uint8_t green, uint8_t blue)
{
	setDutyTIM(htim[RED_ELEMENT], (uint8_t)((double)Duty / 100 * red), TimerChannel[RED_ELEMENT]);
	setDutyTIM(htim[GREEN_ELEMENT], (uint8_t)((double)Duty / 100 * green), TimerChannel[GREEN_ELEMENT]);
	setDutyTIM(htim[BLUE_ELEMENT], (uint8_t)((double)Duty / 100 * blue), TimerChannel[BLUE_ELEMENT]);

	Red = red;
	Green = green;
	Blue = blue;
}

