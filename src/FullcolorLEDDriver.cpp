/*
 * FullcolorLEDDriver.cpp
 *
 *  Created on: 2017/09/09
 *      Author: Shuji
 */

#include "FullcolorLEDDriver.hpp"
#include "tim.h"

uint8_t FullcolorLEDDriver::DutyCount[10][3]{{0}};
uint8_t FullcolorLEDDriver::ClassInsatanceCount = 0;
GPIO_PORT_NAME_t FullcolorLEDDriver::RedPort[10];
GPIO_PORT_NAME_t FullcolorLEDDriver::GreenPort[10];
GPIO_PORT_NAME_t FullcolorLEDDriver::BluePort[10];

FullcolorLEDDriver::FullcolorLEDDriver(GPIO_PORT_NAME_t redPort, GPIO_PORT_NAME_t greenPort, GPIO_PORT_NAME_t bluePort)
{
	Duty = 0;
	ClassInstanceIndex = 0;
	RedRate = 0;
	GreenRate = 0;
	BlueRate = 0;

	if(ClassInsatanceCount == 0){
		IRQAttachTIM15(callBack);

		startTIM15();
	}

	if(ClassInsatanceCount < 10){
		RedPort[ClassInsatanceCount] = redPort;
		GreenPort[ClassInsatanceCount] = greenPort;
		BluePort[ClassInsatanceCount] = bluePort;

		ClassInsatanceCount++;

		ClassInstanceIndex = ClassInsatanceCount - 1;
	}
}
FullcolorLEDDriver::~FullcolorLEDDriver()
{

}
void FullcolorLEDDriver::setColor(LED_COLOR_t color)
{
	switch(color){
	case RED:
		setRedRate(100);
		setGreenRate(0);
		setBlueRate(0);
		break;
	case GREEN:
		setRedRate(0);
		setGreenRate(100);
		setBlueRate(0);
		break;
	case BLUE:
		setRedRate(0);
		setGreenRate(0);
		setBlueRate(100);
		break;
	case YELLOW:
		setRedRate(50);
		setGreenRate(50);
		setBlueRate(0);
		break;
	case PURPLE:
		setRedRate(50);
		setGreenRate(0);
		setBlueRate(50);
		break;
	default:
		break;
	}
}
void FullcolorLEDDriver::setDuty(uint8_t duty)
{
	Duty = duty;
	DutyCount[ClassInstanceIndex][INDEX_RED] = (uint8_t)((double)RedRate / 100 * (double)Duty / 100 * 255);
	DutyCount[ClassInstanceIndex][INDEX_RED] = (uint8_t)((double)GreenRate / 100 * (double)Duty / 100 * 255);
	DutyCount[ClassInstanceIndex][INDEX_RED] = (uint8_t)((double)BlueRate / 100 * (double)Duty / 100 * 255);
}

void FullcolorLEDDriver::setRedRate(uint8_t rate)
{
	RedRate = rate;
	DutyCount[ClassInstanceIndex][INDEX_RED] = (uint8_t)((double)rate / 100 * (double)Duty / 100 * 255);
}
void FullcolorLEDDriver::setGreenRate(uint8_t rate)
{
	GreenRate = rate;
	DutyCount[ClassInstanceIndex][INDEX_GREEN] = (uint8_t)((double)rate / 100 * (double)Duty / 100 * 255);
}
void FullcolorLEDDriver::setBlueRate(uint8_t rate)
{
	BlueRate = rate;
	DutyCount[ClassInstanceIndex][INDEX_BLUE] = (uint8_t)((double)rate / 100 * (double)Duty / 100 * 255);
}
void FullcolorLEDDriver::callBack()
{
	static uint8_t count = 0;

	count++;

	if(count >= 255){
		count = 0;
	}

	for(int i = 0; i < ClassInsatanceCount; i++){
		if(count < DutyCount[i][INDEX_RED]){
			HAL_GPIO_WritePin(getGPIO_TypeDef(RedPort[i]), getGPIO_Pin(RedPort[i]), GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(getGPIO_TypeDef(RedPort[i]), getGPIO_Pin(RedPort[i]), GPIO_PIN_RESET);
		}
		if(count < DutyCount[i][INDEX_GREEN]){
			HAL_GPIO_WritePin(getGPIO_TypeDef(GreenPort[i]), getGPIO_Pin(GreenPort[i]), GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(getGPIO_TypeDef(GreenPort[i]), getGPIO_Pin(GreenPort[i]), GPIO_PIN_RESET);
		}
		if(count < DutyCount[i][INDEX_BLUE]){
			HAL_GPIO_WritePin(getGPIO_TypeDef(BluePort[i]), getGPIO_Pin(BluePort[i]), GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(getGPIO_TypeDef(BluePort[i]), getGPIO_Pin(BluePort[i]), GPIO_PIN_RESET);
		}
	}

}
