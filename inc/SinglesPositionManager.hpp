/*
 * SinglesPositionManager.hpp
 *
 *  Created on: 2017/09/17
 *      Author: Shuji
 */

#ifndef SINGLESPOSITIONMANAGER_HPP_
#define SINGLESPOSITIONMANAGER_HPP_


class SinglesPositionManger{
public:
	enum SINGLES_POSITION_t{
		SERVER,
		RECEIVER,
	};
public:
	SinglesPositionManger(SINGLES_POSITION_t initialPosition);
	void rotatePosition();
	SINGLES_POSITION_t getCurrentPosition();
	void rotatePositionInverse();
private:
	SINGLES_POSITION_t currentPosition;
};


#endif /* SINGLESPOSITIONMANAGER_HPP_ */
