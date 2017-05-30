/*
 * SegmentControl.hpp
 *
 *  Created on: 2017/01/16
 *      Author: MM07860
 */

#ifndef SEGMENTCONTROL_HPP_
#define SEGMENTCONTROL_HPP_


#include "BusOut.hpp"



class SegmentControl : public BusOut{
public:
	SegmentControl(GPIO_PORT_NAME_t bottomLeft, GPIO_PORT_NAME_t bottom, GPIO_PORT_NAME_t bottomRight, GPIO_PORT_NAME_t middle, GPIO_PORT_NAME_t topLeft, GPIO_PORT_NAME_t top, GPIO_PORT_NAME_t topRight);
	void write(uint8_t value);
	SegmentControl& operator=(uint8_t value);
	enum SEGMENT : uint8_t{
		BOTTOM_LEFT = 0x01,
		BOTTOM = 0x02,
		BOTTOM_RIGHT = 0x04,
		MIDDLE = 0x08,
		TOP_LEFT = 0x10,
		TOP = 0x20,
		TOP_RIGHT = 0x40
	};
private:
	const uint8_t SEGMENT[10] = {
			BOTTOM_LEFT | BOTTOM | BOTTOM_RIGHT | TOP_LEFT | TOP | TOP_RIGHT, //0
			BOTTOM_RIGHT | TOP_RIGHT, //1
			BOTTOM_LEFT | BOTTOM | MIDDLE | TOP_RIGHT | TOP, //2
			BOTTOM | BOTTOM_RIGHT | MIDDLE | TOP_RIGHT | TOP, //3
			BOTTOM_RIGHT | MIDDLE | TOP_LEFT | TOP_RIGHT, //4
			BOTTOM | BOTTOM_RIGHT | MIDDLE | TOP_LEFT | TOP, //5
			BOTTOM_LEFT | BOTTOM | BOTTOM_RIGHT | MIDDLE | TOP_LEFT, //6
			BOTTOM_RIGHT | TOP_RIGHT | TOP, //7
			BOTTOM_LEFT | BOTTOM | BOTTOM_RIGHT | MIDDLE | TOP_LEFT | TOP_RIGHT | TOP, //8
			BOTTOM_RIGHT | MIDDLE | TOP_LEFT | TOP | TOP_RIGHT //9
	};
	const uint8_t SEGMENT_0 = 0x01 | 0x02 | 0x04 | 0x10 | 0x20 | 0x40;
	const uint8_t SEGMENT_1 = 0x04 | 0x40;
	const uint8_t SEGMENT_2 = 0x01 | 0x02 | 0x08 | 0x20 | 0x40;
	const uint8_t SEGMENT_3 = 0x02 | 0x04 | 0x08 | 0x20 | 0x40;
	const uint8_t SEGMENT_4 = 0x04 | 0x08 | 0x10 | 0x40;
	const uint8_t SEGMENT_5 = 0x02 | 0x04 | 0x08 | 0x10 | 0x20;
	const uint8_t SEGMENT_6 = 0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20;
	const uint8_t SEGMENT_7 = 0x04 | 0x20 | 0x40;
	const uint8_t SEGMENT_8 = 0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20 | 0x40;
	const uint8_t SEGMENT_9 = 0x04 | 0x08 | 0x10 | 0x20 | 0x40;
};


#endif /* SEGMENTCONTROL_HPP_ */
