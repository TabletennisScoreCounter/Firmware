/*
 * DigitalOut.hpp
 *
 *  Created on: 2017/01/08
 *      Author: user
 */

#ifndef DIGITALOUT_HPP_
#define DIGITALOUT_HPP_

#include "DigitalOutIn.hpp"

namespace DigitalOutIn{

class DigitalOut{
public:
	DigitalOut(PinName_t pinName);
	void write(bool value);
	bool read();
	DigitalOut& operator=(bool value);
	operator bool();
private:
	PinName_t pin;
};

}




#endif /* DIGITALOUT_HPP_ */
