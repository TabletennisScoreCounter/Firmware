/*
 * DigitalOutIn.hpp
 *
 *  Created on: 2017/01/08
 *      Author: user
 */

#ifndef DIGITALOUTIN_HPP_
#define DIGITALOUTIN_HPP_

namespace DigitalOutIn{

typedef enum{
	NC = -1,
	PA0 = 0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
	PB0 = 16,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
	PC0 = 32,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
}PinName_t;

typedef enum{
	RISING,
	FALLING
}InterruptTrigger;

typedef enum{
	NOPULL,
	PULLUP,
	PULLDOWN
}PullRegister;

}


#endif /* DIGITALOUTIN_HPP_ */
