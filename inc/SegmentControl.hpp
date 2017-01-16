/*
 * SegmentControl.hpp
 *
 *  Created on: 2017/01/16
 *      Author: MM07860
 */

#ifndef SEGMENTCONTROL_HPP_
#define SEGMENTCONTROL_HPP_


#include "BusOut.hpp"

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

class SegmentControl : public BusOut{
public:
	SegmentControl(GPIO_PORT_NAME_t bottomLeft, GPIO_PORT_NAME_t bottom, GPIO_PORT_NAME_t bottomRight, GPIO_PORT_NAME_t middle, GPIO_PORT_NAME_t topLeft, GPIO_PORT_NAME_t top, GPIO_PORT_NAME_t topRight);
	void write(uint8_t value);
	SegmentControl& operator=(uint8_t value);
private:
};


#endif /* SEGMENTCONTROL_HPP_ */
