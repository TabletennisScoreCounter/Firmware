/*
 * PositionManager.cpp
 *
 *  Created on: 2017/09/16
 *      Author: Shuji
 */


#include "../Inc/DoublesPositionManager.hpp"

void DoublesPositionManger::rotatePosition()
{
	switch(CurrentPosition){
	case SERVER:
		CurrentPosition = RECEIVER_ASISTANT;
		break;
	case RECEIVER_ASISTANT:
		CurrentPosition = SERVER_ASISTANT;
		break;
	case SERVER_ASISTANT:
		CurrentPosition = RECEIVER;
		break;
	case RECEIVER:
		CurrentPosition = SERVER;
		break;
	default:
		break;
	}
}
void DoublesPositionManger::rotatePositionInverse()
{
	switch(CurrentPosition){
	case SERVER:
		//currentPosition = RECEIVER_ASISTANT;
		CurrentPosition = RECEIVER;
		break;
	case RECEIVER_ASISTANT:
		//currentPosition = SERVER_ASISTANT;
		CurrentPosition = SERVER;
		break;
	case SERVER_ASISTANT:
		//currentPosition = RECEIVER;
		CurrentPosition = RECEIVER_ASISTANT;
		break;
	case RECEIVER:
		//currentPosition = SERVER;
		CurrentPosition = SERVER_ASISTANT;
		break;
	default:
		break;
	}
}

