/*
 * PlayerPositionManager.hpp
 *
 *  Created on: 2018/01/03
 *      Author: Shuji
 */

#ifndef PLAYERPOSITIONMANAGER_HPP_
#define PLAYERPOSITIONMANAGER_HPP_

class PlayerPositionManager{
public:
	enum POSITION_t{
		SERVER,
		RECEIVER,
		SERVER_ASISTANT,
		RECEIVER_ASISTANT
	};
public:
	PlayerPositionManager(POSITION_t initialPosition);
	virtual ~PlayerPositionManager(){};
	virtual void rotatePosition() = 0;
	virtual void rotatePositionInverse() = 0;
	POSITION_t getCurrentPosition();
protected:
	POSITION_t CurrentPosition;
};



#endif /* PLAYERPOSITIONMANAGER_HPP_ */
