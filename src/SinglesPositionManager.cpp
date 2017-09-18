/*
 * SinglesPositionManager.cpp
 *
 *  Created on: 2017/09/17
 *      Author: Shuji
 */



#include "SinglesPositionManager.hpp"

SinglesPositionManger::SinglesPositionManger(SINGLES_POSITION_t initialPosition)
{
	currentPosition = initialPosition;
}
void SinglesPositionManger::rotatePosition()
{
	switch(currentPosition){
	case SERVER:
		currentPosition = RECEIVER;
		break;
	case RECEIVER:
		currentPosition = SERVER;
		break;
	default:
		break;
	}
}
SinglesPositionManger::SINGLES_POSITION_t SinglesPositionManger::getCurrentPosition()
{
	return currentPosition;
}
