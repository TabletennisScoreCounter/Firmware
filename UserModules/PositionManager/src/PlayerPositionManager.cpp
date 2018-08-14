/*
 * PlayerPositionManager.cpp
 *
 *  Created on: 2018/01/03
 *      Author: Shuji
 */
#include "PlayerPositionManager.hpp"

PlayerPositionManager::POSITION_t PlayerPositionManager::getCurrentPosition()
{
	return CurrentPosition;
}
PlayerPositionManager::PlayerPositionManager(PlayerPositionManager::POSITION_t initialPosition)
{
	CurrentPosition = initialPosition;
}


