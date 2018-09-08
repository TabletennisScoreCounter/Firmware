/*
 * GameStateManager.hpp
 *
 *  Created on: 2018/01/03
 *      Author: Shuji
 */

#ifndef GAMESTATEMANAGER_HPP_
#define GAMESTATEMANAGER_HPP_

#include "../../ScoreManager/Inc/ScoreManager.hpp"

#include "../../PositionManager/Inc/DoublesPositionManager.hpp"
#include "../../PositionManager/Inc/SinglesPositionManager.hpp"



class GameStateManager{
public:
	enum GAME_MODE_t{
		SINGLES,
		DOUBLES
	};
	GameStateManager(GAME_MODE_t gameMode);
private:
	ScoreManager* scoreManager = nullptr;
	SinglesPositionManger* singlesPosition1 = nullptr;
	SinglesPositionManger* singlesPosition2 = nullptr;
	DoublesPositionManger* doublesPosition1[2] = {nullptr};
	DoublesPositionManger* doublesPosition2[2] = {nullptr};
	uint8_t prevPoint1;
	uint8_t prevPoint2;
	uint8_t prevGame1;
	uint8_t prevGame2;
	PlayerPositionManager* prevServer = nullptr;
	PlayerPositionManager* prevReciever = nullptr;
	GAME_MODE_t GameMode;
};



#endif /* GAMESTATEMANAGER_HPP_ */
