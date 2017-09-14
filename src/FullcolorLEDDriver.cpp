/*
 * FullcolorLEDDriver.cpp
 *
 *  Created on: 2017/09/09
 *      Author: Shuji
 */

#include "FullcolorLEDDriver.hpp"

uint8_t FullcolorLEDDriver::DutyCount[10][3]{{0}};
uint8_t FullcolorLEDDriver::ClassInsatanceCount = 0;
GPIO_PORT_NAME_t FullcolorLEDDriver::RedPort[10];
GPIO_PORT_NAME_t FullcolorLEDDriver::GreenPort[10];
GPIO_PORT_NAME_t FullcolorLEDDriver::BluePort[10];

FullcolorLEDDriver::FullcolorLEDDriver(GPIO_PORT_NAME_t redPort, GPIO_PORT_NAME_t greenPort, GPIO_PORT_NAME_t bluePort)
{
	Duty = 0;
	ClassInstanceIndex = 0;

	if(ClassInsatanceCount < 10){
		RedPort[ClassInsatanceCount] = redPort;
		GreenPort[ClassInsatanceCount] = greenPort;
		BluePort[ClassInsatanceCount] = bluePort;

		ClassInsatanceCount++;

		ClassInstanceIndex = ClassInsatanceCount - 1;
	}
}
void FullcolorLEDDriver::setColor(LED_COLOR_t color)
{

}
void FullcolorLEDDriver::setDuty(uint8_t duty)
{
	Duty = duty;
}

void FullcolorLEDDriver::setRedRate(uint8_t rate)
{
	DutyCount[ClassInstanceIndex][INDEX_RED] = (uint8_t)((double)rate / 100 * (double)Duty / 100 * 255);
}
void FullcolorLEDDriver::setGreenRate(uint8_t rate)
{
	DutyCount[ClassInstanceIndex][INDEX_GREEN] = (uint8_t)((double)rate / 100 * (double)Duty / 100 * 255);
}
void FullcolorLEDDriver::setBlueRate(uint8_t rate)
{
	DutyCount[ClassInstanceIndex][INDEX_BLUE] = (uint8_t)((double)rate / 100 * (double)Duty / 100 * 255);
}
void FullcolorLEDDriver::callBack()
{
	static uint8_t count = 0;

	count++;

	if(count >= 255){
		count = 0;
	}
/*
	for(int i = 0; i < ClassInsatanceCount; i++){
		if(count < DutyCount[i][INDEX_RED]){
			HAL_GPIO_WritePin(getGPIO_TypeDef(RedPort), getGPIO_Pin(RedPort), GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(getGPIO_TypeDef(RedPort), getGPIO_Pin(RedPort), GPIO_PIN_SET);
		}
		if(count < DutyCount[i][INDEX_GREEN]){
			HAL_GPIO_WritePin(getGPIO_TypeDef(GreenPort), getGPIO_Pin(GreenPort), GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(getGPIO_TypeDef(GreenPort), getGPIO_Pin(GreenPort), GPIO_PIN_SET);
		}
		if(count < DutyCount[i][INDEX_BLUE]){
			HAL_GPIO_WritePin(getGPIO_TypeDef(BluePort), getGPIO_Pin(BluePort), GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(getGPIO_TypeDef(BluePort), getGPIO_Pin(BluePort), GPIO_PIN_SET);
		}
	}
	*/
}
