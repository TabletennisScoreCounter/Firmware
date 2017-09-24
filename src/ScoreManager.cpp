#include "ScoreManager.hpp"
#include <cmath>
void ScoreManager::addMyPoint()
{
	if(myGame < GAMES_TO_WIN && enemyGame < GAMES_TO_WIN){
		uint8_t myNextPoint = myPoint + 1;
		if(myNextPoint < GAME_POINT){//自分の次のスコアが11点未満ならただ足すだけ
			myPoint++;
		}
		else{//11点以上になる場合
			if((int)myNextPoint - (int)enemyPoint < 2){//次の, 相手とのスコア差が2点未満なら足すだけ
				myPoint++;
			}
			else{//相手とのスコア差が2点以上開いた場合はゲームが加算
				myPoint = 0;
				enemyPoint = 0;
				myGame++;
			}
		}
	}
}
void ScoreManager::addEnemyPoint()
{
	if(myGame < GAMES_TO_WIN && enemyGame < GAMES_TO_WIN){
		uint8_t enemyNextPoint = enemyPoint + 1;
		if(enemyNextPoint < GAME_POINT){//敵の次のスコアが11点未満ならただ足すだけ
			enemyPoint++;
		}
		else{//11点以上になる場合
			if((int)enemyNextPoint - (int)myPoint < 2){//次の, 相手とのスコア差が2点未満なら足すだけ
				enemyPoint++;
			}
			else{//相手とのスコア差が2点以上開いた場合はゲームが加算
				myPoint = 0;
				enemyPoint = 0;
				enemyGame++;
			}
		}
	}
}
void ScoreManager::resetPoint()
{
	myPoint = 0;
	myGame = 0;
	enemyPoint = 0;
	enemyGame = 0;
}
void ScoreManager::swapPoint()
{
	uint8_t tempPoint = myPoint;
	uint8_t tempGame = myGame;

	myPoint = enemyPoint;
	myGame = enemyGame;

	enemyPoint = tempPoint;
	enemyGame = tempGame;
}
bool ScoreManager::isDeuce()
{
	return ((myPoint >= GAME_POINT - 1) && (enemyPoint >= GAME_POINT - 1));
}
uint8_t ScoreManager::getSum()
{
	return (myPoint + enemyPoint);
}
uint8_t ScoreManager::getGameSum()
{
	return (myGame + enemyGame);
}
void ScoreManager::reduceMyPoint()
{
	if(myPoint > 0 && enemyPoint < GAME_POINT){
		myPoint--;
		enemyPoint++;
	}
}
void ScoreManager::reduceEnemyPoint()
{
	if(enemyPoint > 0 && myPoint < GAME_POINT){
		myPoint++;
		enemyPoint--;
	}
}
