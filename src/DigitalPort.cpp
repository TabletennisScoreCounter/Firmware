/*
 * DigitalPort.cpp
 *
 *  Created on: 2017/05/31
 *      Author: MM07860
 */


#include "DigitalPort.hpp"

bool DigitalPort::PinUsedStatus[DigitalPort::NUM_OF_PORTS][DigitalPort::NUM_OF_PINS]{0};

bool DigitalPort::checkPinUsable(GPIO_TypeDef* port, uint16_t pin)
{
	int index = getPortIndex(port);

	return PinUsedStatus[index][pin];
}
void DigitalPort::updatePinOccupation(GPIO_TypeDef* port, uint16_t pin, bool add)
{
	int index = getPortIndex(port);

	PinUsedStatus[index][pin] = add;
}

DigitalPort::DigitalPort(GPIO_TypeDef* port, uint16_t pin)
{
	//�|�[�g�����g�p���ǂ����`�F�b�N
	assert_param(checkPinUsable(port, pin)==true);

	Port = port;
	//Pin = pin;
	//Mode = GPIO_MODE_ANALOG;
	//PullResister = GPIO_NOPULL;
	peripheralClockEnable(port);

	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	updatePinOccupation(port, pin, true);
}
DigitalPort::~DigitalPort()
{
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(Port,&GPIO_InitStruct);

	updatePinOccupation(Port, GPIO_InitStruct.Pin, false);
}
bool DigitalPort::read()
{
	return HAL_GPIO_ReadPin(Port, GPIO_InitStruct.Pin);
}
DigitalPort::operator bool()
{
	return read();
}
GPIO_TypeDef* DigitalPort::getPort()
{
	return Port;
}
uint16_t DigitalPort::getPin()
{
	return GPIO_InitStruct.Pin;
}
int DigitalPort::getPortIndex(GPIO_TypeDef* port)
{
	int index{0};
/*
	switch ((uint32_t)port) {
		case (uint32_t)GPIOA:
			index = 0;
			break;
		case (uint32_t)GPIOB:
			index = 1;
			break;
		case (uint32_t)GPIOC:
			index = 2;
			break;
		case (uint32_t)GPIOD:
			index = 3;
			break;
		default:
			break;
	}
*/
	return index;
}
void DigitalPort::peripheralClockEnable(GPIO_TypeDef* port)
{
	/*
	switch ((uint32_t)port) {
		case (uint32_t)GPIOA:
			__HAL_RCC_GPIOA_CLK_ENABLE();
			break;
		case (uint32_t)GPIOB:
			__HAL_RCC_GPIOB_CLK_ENABLE();
			break;
		case (uint32_t)GPIOC:
			__HAL_RCC_GPIOC_CLK_ENABLE();
			break;
		case (uint32_t)GPIOD:
			__HAL_RCC_GPIOD_CLK_ENABLE();
			break;
		default:
			break;
	}
	*/
}
void DigitalPort::peripheralClockDisable(GPIO_TypeDef* port)
{
	/*
	switch ((uint32_t)port) {
		case (uint32_t)GPIOA:
			__HAL_RCC_GPIOA_CLK_DISABLE();
			break;
		case (uint32_t)GPIOB:
			__HAL_RCC_GPIOB_CLK_DISABLE();
			break;
		case (uint32_t)GPIOC:
			__HAL_RCC_GPIOC_CLK_DISABLE();
			break;
		case (uint32_t)GPIOD:
			__HAL_RCC_GPIOD_CLK_DISABLE();
			break;
		default:
			break;
	}
	*/
}
