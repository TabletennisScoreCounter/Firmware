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
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

	HAL_GPIO_Init(getPort(), &GPIO_InitStruct);
}
void DigitalIn::setPullRegister(PullRes_t pullMode)
{
	GPIO_InitStruct.Pull = pullMode;

	HAL_GPIO_Init(getPort(), &GPIO_InitStruct);
}
void DigitalIn::IRQAttach(IRQMode_t irqMode, void* funcPtr)
{
	GPIO_InitStruct.Mode = irqMode;
}
void DigitalIn::IRQDetach()
{

}
bool DigitalIn::checkEXTI_Usable()
{

}
