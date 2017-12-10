/*
 * PositionManager.cpp
 *
 *  Created on: 2017/09/16
 *      Author: Shuji
 */


#include "DoublesPositionManager.hpp"

DoublesPositionManger::DoublesPositionManger(DOUBLES_POSITION_t initialPosition)
{
	currentPosition = initialPosition;
}
void DoublesPositionManger::rotatePosition()
{
	switch(currentPosition){
	case SERVER:
		currentPosition = RECEIVER_ASISTANT;
		break;
	case RECEIVER_ASISTANT:
		currentPosition = SERVER_ASISTANT;
		break;
	case SERVER_ASISTANT:
		currentPosition = RECEIVER;
		break;
	case RECEIVER:
		currentPosition = SERVER;
		break;
	default:
		break;
	}
}
void DoublesPositionManger::rotatePositionInverse()
{
	switch(currentPosition){
	case SERVER:
		//currentPosition = RECEIVER_ASISTANT;
		currentPosition = RECEIVER;
		break;
	case RECEIVER_ASISTANT:
		//currentPosition = SERVER_ASISTANT;
		currentPosition = SERVER;
		break;
	case SERVER_ASISTANT:
		//currentPosition = RECEIVER;
		currentPosition = RECEIVER_ASISTANT;
		break;
	case RECEIVER:
		//currentPosition = SERVER;
		currentPosition = SERVER_ASISTANT;
		break;
	default:
		break;
	}
}
DoublesPositionManger::DOUBLES_POSITION_t DoublesPositionManger::getCurrentPosition()
{
	return currentPosition;
}

