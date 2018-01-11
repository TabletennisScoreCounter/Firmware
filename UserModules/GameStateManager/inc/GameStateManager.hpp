/*
 * GameStateManager.hpp
 *
 *  Created on: 2018/01/03
 *      Author: Shuji
 */

#ifndef GAMESTATEMANAGER_HPP_
#define GAMESTATEMANAGER_HPP_

#include "ScoreManager.hpp"
#include "SinglesPositionManager.hpp"
#include "DoublesPositionManager.hpp"



class GameStateManager{
public:
	enum GAME_MODE_t{
		SINGLES,
		DOUBLES
	};
	GameStateManager(GAME_MODE_t gameMode);
private:
	ScoreManager* scoreManager;
	SinglesPositionManger* singlesPosition1;
	SinglesPositionManger* singlesPosition2;
	DoublesPositionManger* doublesPosition1[2];
	DoublesPositionManger* doublesPosition2[2];
	uint8_t prevPoint1;
	uint8_t prevPoint2;
	uint8_t prevGame1;
	uint8_t prevGame2;
	uint8_t prevServer;
	uint8_t prevReciever;
	GAME_MODE_t GameMode;
	void posRotate();
};



#endif /* GAMESTATEMANAGER_HPP_ */
