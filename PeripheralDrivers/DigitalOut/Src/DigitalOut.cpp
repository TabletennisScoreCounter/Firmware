/*
 * DigitalOut.cpp
 *
 *  Created on: 2017/01/16
 *      Author: MM07860
 */


#include "DigitalOut.hpp"

DigitalOut::DigitalOut(GPIO_PORT_NAME_t port)
{
	PortName = port;

	GPIOTypeDef = getGPIO_TypeDef(port);
	GPIOPin = getGPIO_Pin(port);

	setGPIOOutput(port);

}
void DigitalOut::write(bool status)
{
	HAL_GPIO_WritePin(GPIOTypeDef, GPIOPin, GPIO_PinState(status));
}
DigitalOut& DigitalOut::operator =(bool status)
{
	write(status);
	return *this;
}


