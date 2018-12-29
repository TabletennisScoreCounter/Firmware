/*
 * SinglesPositionManager.cpp
 *
 *  Created on: 2017/09/17
 *      Author: Shuji
 */



#include "SinglesPositionManager.hpp"

void SinglesPositionManger::rotatePosition()
{
	switch(CurrentPosition){
	case SERVER:
		CurrentPosition = RECEIVER;
		break;
	case RECEIVER:
		CurrentPosition = SERVER;
		break;
	default:
		break;
	}
}
void SinglesPositionManger::rotatePositionInverse()
{//シングルスでは動きは同じ
	rotatePosition();
}
