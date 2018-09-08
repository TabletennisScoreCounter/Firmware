/*
 * GameStateManager.cpp
 *
 *  Created on: 2018/01/03
 *      Author: Shuji
 */
#include "GameStateManager.hpp"

GameStateManager::GameStateManager(GameStateManager::GAME_MODE_t gameMode)
{
	GameMode = gameMode;

	prevPoint1 = 0;
	prevPoint2 = 0;
	prevGame1 = 0;
	prevGame2 = 0;
}



