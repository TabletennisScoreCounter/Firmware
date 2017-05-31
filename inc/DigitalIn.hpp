/*
 * DigitalIn.hpp
 *
 *  Created on: 2017/05/31
 *      Author: MM07860
 */

#ifndef DIGITALIN_HPP_
#define DIGITALIN_HPP_


#include "DigitalPort.hpp"

class DigitalIn : public DigitalPort {
private:
	void* funcPtr[NUM_OF_PINS];
	static bool EXTI_UsedStatus[NUM_OF_PINS];
public:
	enum PullRes_t : uint32_t{
		PULLRES_PULLUP = GPIO_PULLUP,
		PULLRES_NONE = GPIO_NOPULL,
		PULLRES_PULLDOWN = GPIO_PULLDOWN
	};
	enum IRQMode_t : uint32_t{
		IRQ_RISING = GPIO_MODE_IT_RISING,
		IRQ_FALLING = GPIO_MODE_IT_FALLING,
		IRQ_RISING_AND_FALLING = GPIO_MODE_IT_RISING_FALLING
	};
	DigitalIn(GPIO_TypeDef* port, uint16_t pin);
	void setPullRegister(PullRes_t pullMode);
	void IRQAttach(IRQMode_t irqMode, void* funcPtr);
	void IRQDetach();
private:
	bool checkEXTI_Usable();
};


#endif /* DIGITALIN_HPP_ */
