/*
 * SegmentControl.cpp
 *
 *  Created on: 2017/01/16
 *      Author: MM07860
 */


#include "../Inc/SegmentControl.hpp"


SegmentControl::SegmentControl(GPIO_PORT_NAME_t bottomLeft, GPIO_PORT_NAME_t bottom,
								GPIO_PORT_NAME_t bottomRight, GPIO_PORT_NAME_t middle,
								GPIO_PORT_NAME_t topLeft, GPIO_PORT_NAME_t top,
								GPIO_PORT_NAME_t topRight)
								: BusOut(bottomLeft, bottom, bottomRight, middle, topLeft, top, topRight)
{

}
void SegmentControl::write(uint8_t value)
{
	if(value < 10){
		BusOut::write(SEGMENT[value]);
	}
}
SegmentControl& SegmentControl::operator=(uint8_t value)
{
	write(value);
	return *this;
}



