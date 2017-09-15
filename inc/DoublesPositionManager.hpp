/*
 * PositionManager.hpp
 *
 *  Created on: 2017/09/16
 *      Author: Shuji
 */

#ifndef DOUBLESPOSITIONMANAGER_HPP_
#define DOUBLESPOSITIONMANAGER_HPP_


class DoublesPositionManger{
public:
	enum DOUBLES_POSITION_t{
		SERVER,
		RECEIVER,
		SERVER_ASISTANT,
		RECEIVER_ASISTANT
	};
public:
	DoublesPositionManger(DOUBLES_POSITION_t initialPosition);
	void rotatePosition();
	DOUBLES_POSITION_t getCurrentPosition();
private:
	DOUBLES_POSITION_t currentPosition;
};


#endif /* DOUBLESPOSITIONMANAGER_HPP_ */
