/*
 * BusOut.cpp
 *
 *  Created on: 2017/01/16
 *      Author: MM07860
 */

#include "BusOut.hpp"

/*
template <typename First, typename... Rest>BusOut::BusOut(const First& first, const Rest&... rest)
{
	portList.push_back(DigitalOut(first));

	BusOut(rest...);
}
*/
void BusOut::write(uint8_t data)
{
	for (uint16_t i = 0; i < portList.size(); i++) {
		portList[i] = (bool)(data & (0x01 << i));
	}
}
BusOut& BusOut::operator=(uint8_t data)
{
	write(data);
	return *this;
}
BusOut::BusOut()
{
	//Do Nothing
}
