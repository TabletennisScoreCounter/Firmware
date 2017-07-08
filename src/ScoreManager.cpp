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
