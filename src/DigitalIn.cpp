/*
 * DigitalIn.cpp
 *
 *  Created on: 2017/05/31
 *      Author: MM07860
 */


#include "DigitalIn.hpp"

bool DigitalIn::EXTI_UsedStatus[NUM_OF_PINS]{false};

DigitalIn::DigitalIn(GPIO_TypeDef* port, uint16_t pin) : DigitalPort(port, pin)
{

}
void DigitalIn::setPullRegister(PullRes_t pullMode)
{

}
void DigitalIn::IRQAttach(IRQMode_t irqMode, void* funcPtr)
{

}
void DigitalIn::IRQDetach()
{

}
bool DigitalIn::checkEXTI_Usable()
{

}
