/*
 * DigitalPort.hpp
 *
 *  Created on: 2017/05/31
 *      Author: MM07860
 */

#ifndef DIGITALPORT_HPP_
#define DIGITALPORT_HPP_

#include "gpio.h"

class DigitalPort {
public:
	static const uint16_t NUM_OF_PORTS = 4;
	static const uint16_t NUM_OF_PINS = 16;
private:
	GPIO_TypeDef* Port;
	uint16_t Pin;
	static bool PinUsedStatus[NUM_OF_PORTS][NUM_OF_PINS];
protected:
	uint32_t PullResister;
	uint32_t Mode;

public:
	DigitalPort(GPIO_TypeDef* port, uint16_t pin);
	~DigitalPort();
	bool read();
	operator bool();
protected:
	static bool checkPinUsable(GPIO_TypeDef* port, uint16_t pin);
	GPIO_TypeDef* getPort();
	uint16_t getPin();
private:
	static void updatePinOccupation(GPIO_TypeDef* port, uint16_t pin, bool add);
	static int getPortIndex(GPIO_TypeDef* port);
};



#endif /* DIGITALPORT_HPP_ */
