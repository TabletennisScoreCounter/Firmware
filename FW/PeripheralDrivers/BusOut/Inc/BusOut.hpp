/*
 * BusOut.hpp
 *
 *  Created on: 2017/01/16
 *      Author: MM07860
 */

#ifndef BUSOUT_HPP_
#define BUSOUT_HPP_


#include "DigitalOut.hpp"
#include <vector>

class BusOut {
public:
	template <typename First, typename... Rest>BusOut(const First& first, const Rest&... rest);
	BusOut();
	void write(uint8_t data);
	BusOut& operator=(uint8_t data);

private:
	std::vector<DigitalOut> portList;
	//int memberNum = 0;
	template <typename First, typename... Rest>void dummy(const First& first, const Rest&... rest);
	void dummy(){};
};
template <typename First, typename... Rest>BusOut::BusOut(const First& first, const Rest&... rest)
{
	dummy(first,rest...);
}
template <typename First, typename... Rest>void BusOut::dummy(const First& first, const Rest&... rest)
{
	/*DigitalOut member(first);*/
	portList.push_back(/*&member*/DigitalOut(first));
	//memberNum++;
	dummy(rest...);
}

#endif /* BUSOUT_HPP_ */
