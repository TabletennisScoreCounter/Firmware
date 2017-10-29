/*
 * ScoreManager.hpp
 *
 *  Created on: 2017/07/08
 *      Author: admin
 */

#ifndef SCOREMANAGER_HPP_
#define SCOREMANAGER_HPP_
/*
 * ScoreManager.cpp
 *
 *  Created on: 2017/07/08
 *      Author: admin
 */
#include "stm32l4xx_hal.h"
class ScoreManager {
public:
	static const uint8_t GAME_POINT = 11;
	static const uint8_t GAMES_TO_WIN = 3;

private:
	uint8_t myPoint;
	uint8_t enemyPoint;
	uint8_t myGame;
	uint8_t enemyGame;
public:
	void addMyPoint();
	void addEnemyPoint();
	void reduceMyPoint();
	void reduceEnemyPoint();
	void resetPoint();
	void swapPoint();
	uint8_t getMyPoint(){return myPoint;}
	uint8_t getEnemyPoint(){return enemyPoint;}
	uint8_t getMyGame(){return myGame;}
	uint8_t getEnemyGame(){return enemyGame;}
	bool isDeuce();
	uint8_t getSum();
	uint8_t getGameSum();
	bool isFinalGame();
private:

};







#endif /* SCOREMANAGER_HPP_ */
