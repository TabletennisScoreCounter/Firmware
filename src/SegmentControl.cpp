/*
 * SegmentControl.cpp
 *
 *  Created on: 2017/01/16
 *      Author: MM07860
 */


#include "SegmentControl.hpp"


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
	/*
	switch (value) {
		case 0:
			BusOut::write(SEGMENT_0);
			break;
		case 1:
			BusOut::write(SEGMENT_1);
			break;
		case 2:
			BusOut::write(SEGMENT_2);
			break;
		case 3:
			BusOut::write(SEGMENT_3);
			break;
		case 4:
			BusOut::write(SEGMENT_4);
			break;
		case 5:
			BusOut::write(SEGMENT_5);
			break;
		case 6:
			BusOut::write(SEGMENT_6);
			break;
		case 7:
			BusOut::write(SEGMENT_7);
			break;
		case 8:
			BusOut::write(SEGMENT_8);
			break;
		case 9:
			BusOut::write(SEGMENT_9);
			break;
		default:
			break;
	}
	*/
}
SegmentControl& SegmentControl::operator=(uint8_t value)
{
	write(value);
	return *this;
}



