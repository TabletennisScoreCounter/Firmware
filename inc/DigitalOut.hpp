/*
 * DigitalOut.hpp
 *
 *  Created on: 2017/01/16
 *      Author: MM07860
 */

#ifndef DIGITALOUT_HPP_
#define DIGITALOUT_HPP_

#include "gpio.h"

class DigitalOut {
public:
	DigitalOut(GPIO_PORT_NAME_t port);
	void write(bool status);
	DigitalOut& operator=(bool status);
private:
	GPIO_PORT_NAME_t PortName;
	GPIO_TypeDef* GPIOTypeDef;
	uint16_t GPIOPin;
};


#endif /* DIGITALOUT_HPP_ */
