
/*
 * MainWrapper.cpp
 *
 *  Created on: 2018/08/14
 *      Author: Shuji
 */

#include "MainWrapper.hpp"

#include "tim.h"
#include "gpio.h"
#include "BusOut.hpp"
#include "DigitalOut.hpp"

#include "ScoreManager.hpp"

#include "DoublesPositionManager.hpp"
#include "SinglesPositionManager.hpp"

#include "FullcolorLEDDriver.hpp"
#include "SegmentControl.hpp"

enum GAME_MODE_t{
	SINGLES,
	DOUBLES
};
enum ACTION_t{
	UP_MY_POINT,
	UP_ENEMY_POINT,
	UP_MY_POINT_WITH_SERVE_CHANGE,
	UP_ENEMY_POINT_WITH_SERVE_CHANGE
};
static const uint8_t FIVE_GAMES_MATCH_POINT = 3;
static const uint8_t SEVEN_GAMES_MATCH_POINT = 4;

void callBack();
void callBackButton();
void callBackButton2();
void callBackBlueButton();
void callBackButton3();
void callBackButton4();
void callBackChattering();
void refleshSegmentValue();
void refleshServerReceiverLED(GAME_MODE_t mode);
static bool changeSideFlag = false;

SegmentControl* seg;
BusOut* channelSel;
uint8_t segmentValue[6]{0};
ScoreManager scoreManager;
void initializeSegment();

DoublesPositionManger player1(PlayerPositionManager::SERVER);
DoublesPositionManger player2(PlayerPositionManager::SERVER_ASISTANT);
DoublesPositionManger player3(PlayerPositionManager::RECEIVER);
DoublesPositionManger player4(PlayerPositionManager::RECEIVER_ASISTANT);

SinglesPositionManger singlesPlayer1(PlayerPositionManager::SERVER);
SinglesPositionManger singlesPlayer2(PlayerPositionManager::RECEIVER);

FullcolorLEDDriver* led1;
FullcolorLEDDriver* led2;

void initializeServerReceiverLED();
void initializeButtons();
bool antiChatteringFlag[10]{false};

void refleshGameState(GAME_MODE_t mode);
GAME_MODE_t gameMode = SINGLES;

bool longPushFlag[3]{false};

int previousAction;
void cancelPreviousAction();

static uint8_t myPrevScore = 0;
static uint8_t enemyPrevScore = 0;

void CWrappedMain()
{
	initializeServerReceiverLED();

	  initializeSegment();

	  initializeButtons();

	  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == GPIO_PIN_SET){
		  gameMode = DOUBLES;
	  }
	  else{
		  gameMode = SINGLES;
	  }

	  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10) == GPIO_PIN_SET){
		  scoreManager.setGamesToWin(SEVEN_GAMES_MATCH_POINT);
	  }
	  else{
		  scoreManager.setGamesToWin(FIVE_GAMES_MATCH_POINT);
	  }

	  while (1)
	  {
	  	  refleshGameState(gameMode);
	  }
}
void callBack()
{
	static uint8_t count = 0;

	*channelSel = (0x01 << count);
	*seg = segmentValue[count];

	count++;
	if (count >= 6) {
		count = 0;
	}
}
void callBackButton()
{
	if(!antiChatteringFlag[0]){
		if(!longPushFlag[0]){//長押し非検知
			scoreManager.addMyPoint();
			refleshSegmentValue();
			previousAction = UP_MY_POINT;
		}
		else{
			//scoreManager.reduceMyPoint();
			//refleshSegmentValue();
			longPushFlag[0] = false;
		}
		antiChatteringFlag[0] = true;
	}
}
void callBackButton2()
{
	if(!antiChatteringFlag[1]){
		if(!longPushFlag[1]){
			scoreManager.addEnemyPoint();
			refleshSegmentValue();
			//antiChatteringFlag[0] = true;
			previousAction = UP_ENEMY_POINT;
		}
		else{
			//scoreManager.reduceMyPoint();
			//refleshSegmentValue();
			longPushFlag[1] = false;
		}
		antiChatteringFlag[1] = true;
	}
}
void callBackButton3()
{
	if(!antiChatteringFlag[2]){
		if(scoreManager.getSum() == 0){//セットの途中では機能しない
			if(gameMode == SINGLES){
				if(scoreManager.getGameSum() == 0){//初期しか動作しない
					singlesPlayer1.rotatePosition();
					singlesPlayer2.rotatePosition();
//					refleshServerReceiverLED_Singles();
				}
			}
			else{
				if(scoreManager.getGameSum() == 0){//初期は, チーム入れ替えも含めて動作する
					player1.rotatePosition();
					player2.rotatePosition();
					player3.rotatePosition();
					player4.rotatePosition();
				}
				else{//ゲームが進んだ状態では, サーバー入れ替えのみ
					player1.rotatePosition();
					player2.rotatePosition();
					player3.rotatePosition();
					player4.rotatePosition();
					player1.rotatePosition();
					player2.rotatePosition();
					player3.rotatePosition();
					player4.rotatePosition();
				}
//				refleshServerReceiverLED_Doubles();
			}
			refleshServerReceiverLED(gameMode);
		}
		antiChatteringFlag[2] = true;
	}
}
void callBackButton4()
{
	if(!antiChatteringFlag[3]){
		if(gameMode == DOUBLES){//ダブルスの時しか機能しない
			if(scoreManager.getGameSum() == 0 && scoreManager.getSum() == 0){//ゲーム未開始時のレシーバ入れ替えでしか使えない
				//receiver,receiver_assistantの入れ替えは,2回ローテーションと同値
				if(player1.getCurrentPosition() == DoublesPositionManger::RECEIVER ||
						player2.getCurrentPosition() == DoublesPositionManger::RECEIVER){//1,2ペアがレシーバのときは1,2をスワップ
					player1.rotatePosition();
					player1.rotatePosition();
					player2.rotatePosition();
					player2.rotatePosition();

				}
				else{//3,4ペアがレシーバの場合, 3,4をスワップ
					player3.rotatePosition();
					player3.rotatePosition();
					player4.rotatePosition();
					player4.rotatePosition();
				}
//				refleshServerReceiverLED_Doubles();
				refleshServerReceiverLED(DOUBLES);
			}

		}
		antiChatteringFlag[3] = true;
	}
}
void callBackChattering()
{
	static uint8_t count[10]{0};

	for(int i = 0; i < 10; i++){
		if(antiChatteringFlag[i]){
			count[i]++;

			if(count[i] >= 100){
				antiChatteringFlag[i] = false;
				count[i] = 0;
			}
		}
	}

	static uint16_t count2 = 0;
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET){//ボタン押されていたら
		if(!longPushFlag[0]){
			count2++;
			if(count2 >= 300){
				longPushFlag[0] = true;
				count2 = 0;

				scoreManager.reduceMyPoint();
				refleshSegmentValue();
			}
		}
	}
	else{
		count2 = 0;
		longPushFlag[0] = false;
	}

	static uint16_t count3 = 0;
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == GPIO_PIN_RESET){//ボタン押されていたら
		if(!longPushFlag[1]){
			count3++;
			if(count3 >= 300){
				longPushFlag[1] = true;
				scoreManager.reduceEnemyPoint();
				refleshSegmentValue();
				count3 = 0;
			}
		}
	}
	else{
		count3 = 0;
		longPushFlag[1] = false;
	}

	static uint16_t count4 = 0;
	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET){//ボタン押されていたら
		if(!longPushFlag[2]){
			count4++;
			if(count4 >= 300){
				longPushFlag[2] = true;
				//scoreManager.reduceEnemyPoint();
				//refleshSegmentValue();
				cancelPreviousAction();
//				if(scoreManager.isTheGameFinished()){
//					changeSideFlag = !changeSideFlag;//MyとEnemyを入れ替え
//					scoreManager.swapPoint();
//					scoreManager.nextGame();//ゲーム更新
//					refleshSegmentValue();
//				}
				count4 = 0;
			}
		}
	}
	else{
		count4 = 0;
		longPushFlag[2] = false;
	}
}
void refleshSegmentValue()
{
	segmentValue[0] = scoreManager.getMyPoint() / 10;
	segmentValue[1] = scoreManager.getMyPoint() % 10;

	segmentValue[2] = scoreManager.getMyGame();
	segmentValue[3] = scoreManager.getEnemyGame();

	segmentValue[4] = scoreManager.getEnemyPoint() / 10;
	segmentValue[5] = scoreManager.getEnemyPoint() % 10;
}
void callBackBlueButton()
{
	if(!antiChatteringFlag[4]){
		if(!longPushFlag[2]){//長押し非検知
			//changeSideFlag = !changeSideFlag;//MyとEnemyを入れ替え

			//scoreManager.swapPoint();

			//scoreManager.nextGame();//ゲーム更新

			//refleshSegmentValue();
			//cancelPreviousAction();
			if(scoreManager.isTheGameFinished()){
				changeSideFlag = !changeSideFlag;//MyとEnemyを入れ替え
				scoreManager.swapPoint();
				scoreManager.nextGame();//ゲーム更新
				refleshSegmentValue();
			}
		}
		else{
			//scoreManager.reduceMyPoint();
			//refleshSegmentValue();
			longPushFlag[2] = false;
		}

		antiChatteringFlag[4] = true;
	}
}
void refleshServerReceiverLED(GAME_MODE_t mode)
{
	if(mode == SINGLES){
		if(singlesPlayer1.getCurrentPosition() == SinglesPositionManger::SERVER){
			led1->setColor(FullcolorLEDDriver::RED);
		}
		else if(singlesPlayer2.getCurrentPosition() == SinglesPositionManger::SERVER){
			led1->setColor(FullcolorLEDDriver::BLUE);
		}

		if(singlesPlayer1.getCurrentPosition() == SinglesPositionManger::RECEIVER){
				led2->setColor(FullcolorLEDDriver::RED);
		}
		else if(singlesPlayer2.getCurrentPosition() == SinglesPositionManger::RECEIVER){
			led2->setColor(FullcolorLEDDriver::BLUE);
		}
	}
	else{
		if(player1.getCurrentPosition() == DoublesPositionManger::SERVER){
			led1->setColor(FullcolorLEDDriver::RED);
		}
		else if(player2.getCurrentPosition() == DoublesPositionManger::SERVER){
			led1->setColor(FullcolorLEDDriver::GREEN);
		}
		else if(player3.getCurrentPosition() == DoublesPositionManger::SERVER){
			led1->setColor(FullcolorLEDDriver::BLUE);
		}
		else if(player4.getCurrentPosition() == DoublesPositionManger::SERVER){
			led1->setColor(FullcolorLEDDriver::YELLOW);
		}

		if(player1.getCurrentPosition() == DoublesPositionManger::RECEIVER){
			led2->setColor(FullcolorLEDDriver::RED);
		}
		else if(player2.getCurrentPosition() == DoublesPositionManger::RECEIVER){
			led2->setColor(FullcolorLEDDriver::GREEN);
		}
		else if(player3.getCurrentPosition() == DoublesPositionManger::RECEIVER){
			led2->setColor(FullcolorLEDDriver::BLUE);
		}
		else if(player4.getCurrentPosition() == DoublesPositionManger::RECEIVER){
			led2->setColor(FullcolorLEDDriver::YELLOW);
		}
	}
}

void initializeServerReceiverLED()
{
	LEDPWMPort_t led1_Red = {
			  .PortName = PA9,
			  .TimerHandle = &htim1,
			  .TimerChannel = TIM_CHANNEL_2

	  };

	  LEDPWMPort_t led1_Green = {
			  .PortName = PB10,
			  .TimerHandle = &htim2,
			  .TimerChannel = TIM_CHANNEL_3
	  };

	  LEDPWMPort_t led1_Blue = {
			  .PortName = PA8,
			  .TimerHandle = &htim1,
			  .TimerChannel = TIM_CHANNEL_1
	  };

	  LEDPWMPort_t led2_Red = {
	  		  .PortName = PB4,
	  		  .TimerHandle = &htim3,
	  		  .TimerChannel = TIM_CHANNEL_1
	  };
	  LEDPWMPort_t led2_Green = {
	  		  .PortName = PA10,
	  		  .TimerHandle = &htim1,
	  		  .TimerChannel = TIM_CHANNEL_3
	  };
	  LEDPWMPort_t led2_Blue = {
	  		  .PortName = PB5,
	  		  .TimerHandle = &htim3,
	  		  .TimerChannel = TIM_CHANNEL_2
	  };


	  led1 = new FullcolorLEDDriver(led1_Red, led1_Green, led1_Blue);
	  led2 = new FullcolorLEDDriver(led2_Red, led2_Green, led2_Blue);

	  led1->setDuty(5);
	  led2->setDuty(5);

	  led1->setColor(FullcolorLEDDriver::RED);
	  led2->setColor(FullcolorLEDDriver::BLUE);
}
void initializeSegment()
{
	  seg = new SegmentControl(PC5, PC6, PC8, PB11, PB12, PA11, PA12);
	  channelSel = new BusOut(PB1, PB2, PB15, PB14, PC4, PB13);

	  IRQAttachTIM5(callBack);

	  startTIM5();
}
void initializeButtons()
{

	IRQAttachTIM4(callBackChattering);
	startTIM4();

	GPIOIRQAttach(PA0,callBackButton);
	GPIOIRQAttach(PA1,callBackButton2);
	GPIOIRQAttach(PC13,callBackBlueButton);
	GPIOIRQAttach(PA4,callBackButton3);
	GPIOIRQAttach(PC3,callBackButton4);
}
void refleshGameState(GAME_MODE_t mode)
{
	 //static uint8_t myScore = 0;
     //static uint8_t enemyScore = 0;

     static uint8_t setCount = 0;

     static PlayerPositionManager::POSITION_t singlesPositionStatus[2];//singlesPlayer1, singlesPlayer2の状態を把握
     static PlayerPositionManager::POSITION_t doublesPositionStatus[4];//player1, player2, player3, player4の状態を把握

     if(scoreManager.getGameSum() == 0 && scoreManager.getSum() == 0){//ゲームスタート時にポジション記憶
    	 	 singlesPositionStatus[0] = singlesPlayer1.getCurrentPosition();
		 singlesPositionStatus[1] = singlesPlayer2.getCurrentPosition();

    	 	 doublesPositionStatus[0] = player1.getCurrentPosition();
		 doublesPositionStatus[1] = player2.getCurrentPosition();
		 doublesPositionStatus[2] = player3.getCurrentPosition();
		 doublesPositionStatus[3] = player4.getCurrentPosition();
     }

     if(scoreManager.getGameSum() - setCount > 0){//ゲームセットの場合リセット
        myPrevScore = 0;
	    enemyPrevScore = 0;

	    if(mode == SINGLES){//シングルスの場合, 前のゲームセットごとに反転
			while(singlesPlayer1.getCurrentPosition() != singlesPositionStatus[0]){//初期状態に戻す
				singlesPlayer1.rotatePosition();
				singlesPlayer2.rotatePosition();
			}
			//反転
			singlesPlayer1.rotatePosition();
			singlesPlayer2.rotatePosition();
			//新しい値を記憶
			singlesPositionStatus[0] = singlesPlayer1.getCurrentPosition();
			singlesPositionStatus[1] = singlesPlayer2.getCurrentPosition();

//			refleshServerReceiverLED_Singles();
	    }
	    else{//ダブルスの場合, 前のゲームセットと, チームを反転し, さらにサーバレシーバ関係をずらす
			while(player1.getCurrentPosition() != doublesPositionStatus[0]){//初期状態に戻す
				player1.rotatePosition();
			    player2.rotatePosition();
			    player3.rotatePosition();
			    player4.rotatePosition();
			}
			//チーム反転
			player1.rotatePosition();
			player2.rotatePosition();
			player3.rotatePosition();
			player4.rotatePosition();

			//サーバレシーバ関係ずらす
			player1.rotatePosition();
			player1.rotatePosition();
			player2.rotatePosition();
			player2.rotatePosition();

			//新しい値を記憶
			doublesPositionStatus[0] = player1.getCurrentPosition();
			doublesPositionStatus[1] = player2.getCurrentPosition();
			doublesPositionStatus[2] = player3.getCurrentPosition();
			doublesPositionStatus[3] = player4.getCurrentPosition();

//			refleshServerReceiverLED_Doubles();
	    }
	    refleshServerReceiverLED(mode);
	    setCount = scoreManager.getGameSum();

     }

     if(scoreManager.isDeuce()){//デュース
		  if(scoreManager.getSum() - myPrevScore - enemyPrevScore > 0 ){//1本進むごとにサーブ交代
			  if(mode == SINGLES){
				  singlesPlayer1.rotatePosition();
				  singlesPlayer2.rotatePosition();
//				  refleshServerReceiverLED_Singles();

			  }
			  else{
				  player1.rotatePosition();
				  player2.rotatePosition();
				  player3.rotatePosition();
				  player4.rotatePosition();
//				  refleshServerReceiverLED_Doubles();
			  }
			  refleshServerReceiverLED(mode);

			  myPrevScore = scoreManager.getMyPoint();
			  enemyPrevScore = scoreManager.getEnemyPoint();

			  if(previousAction == UP_MY_POINT){//ポイント上昇を上書き
				  previousAction = UP_MY_POINT_WITH_SERVE_CHANGE;
			  }
			  else if(previousAction == UP_ENEMY_POINT){
				  previousAction = UP_ENEMY_POINT_WITH_SERVE_CHANGE;
			  }
		  }
	 }
	 else
	 {
		  if(scoreManager.getSum() - myPrevScore - enemyPrevScore > 1){//2本進むごとにサーブ交代
			  if(mode == SINGLES){
				  singlesPlayer1.rotatePosition();
				  singlesPlayer2.rotatePosition();
//				  refleshServerReceiverLED_Singles();
			  }
			  else{
				  player1.rotatePosition();
				  player2.rotatePosition();
				  player3.rotatePosition();
				  player4.rotatePosition();
//				  refleshServerReceiverLED_Doubles();
			  }
			  refleshServerReceiverLED(mode);

			  myPrevScore = scoreManager.getMyPoint();
			  enemyPrevScore = scoreManager.getEnemyPoint();

			  if(previousAction == UP_MY_POINT){//ポイント上昇を上書き
				  previousAction = UP_MY_POINT_WITH_SERVE_CHANGE;
			  }
			  else if(previousAction == UP_ENEMY_POINT){
				  previousAction = UP_ENEMY_POINT_WITH_SERVE_CHANGE;
			  }
		  }
	 }
     static bool fivePointFlag = false;
     if(!fivePointFlag && scoreManager.isFinalGame()){
    	 	 if(scoreManager.getMyPoint() == 5 || scoreManager.getEnemyPoint() == 5){
    	 		 if(mode == DOUBLES){//ダブルスの最終ゲームのとき
    	 			//どちらかが5ポイントになった場合にレシーバ交代
				if(player1.getCurrentPosition() == DoublesPositionManger::RECEIVER ||
					player2.getCurrentPosition() == DoublesPositionManger::RECEIVER){//1,2ペアがレシーバのときは1,2をスワップ
					player1.rotatePosition();
					player1.rotatePosition();
					player2.rotatePosition();
					player2.rotatePosition();
				}
				else{//3,4ペアがレシーバの場合, 3,4をスワップ
					player3.rotatePosition();
					player3.rotatePosition();
					player4.rotatePosition();
					player4.rotatePosition();
				 }
    	 		 }
    	 		 else{
    	 			 singlesPlayer1.rotatePosition();
    	 			 singlesPlayer2.rotatePosition();

    	 		 }

//    	 		refleshServerReceiverLED_Doubles();
    	 		refleshServerReceiverLED(mode);
    	 		//scoreManager.swapPoint();
    	 		fivePointFlag = true;
    	 	 }
     }
}
void cancelPreviousAction()
{
	if(previousAction == UP_MY_POINT || previousAction == UP_MY_POINT_WITH_SERVE_CHANGE){
		//自分のスコアを減らす
		if(scoreManager.isDeuce()){
			myPrevScore--;
		}
		else{
			if(previousAction == UP_MY_POINT_WITH_SERVE_CHANGE){
				myPrevScore--;
				myPrevScore--;
			}
		}
		scoreManager.reduceMyPoint2();
		/*
		if(previousAction == UP_MY_POINT_WITH_SERVE_CHANGE){
			myPrevScore--;
			myPrevScore--;
		}
		*/

	}
	else if(previousAction == UP_ENEMY_POINT || previousAction == UP_ENEMY_POINT_WITH_SERVE_CHANGE){//敵のスコアを減らす
		if(scoreManager.isDeuce()){
			enemyPrevScore--;
		}
		else{
			if(previousAction == UP_ENEMY_POINT_WITH_SERVE_CHANGE){
				enemyPrevScore--;
				enemyPrevScore--;
			}
		}
		scoreManager.reduceEnemyPoint2();
		/*
		if(previousAction == UP_ENEMY_POINT_WITH_SERVE_CHANGE){
			enemyPrevScore--;
			enemyPrevScore--;
		}
		*/
	}
	refleshSegmentValue();

	//ポジションを元に戻す
	if(gameMode == SINGLES){
		if(previousAction == UP_MY_POINT_WITH_SERVE_CHANGE || previousAction == UP_ENEMY_POINT_WITH_SERVE_CHANGE){
			singlesPlayer1.rotatePositionInverse();
			singlesPlayer2.rotatePositionInverse();
		}
	}
	else{
		if(previousAction == UP_MY_POINT_WITH_SERVE_CHANGE || previousAction == UP_ENEMY_POINT_WITH_SERVE_CHANGE){
			player1.rotatePositionInverse();
			player2.rotatePositionInverse();
			player3.rotatePositionInverse();
			player4.rotatePositionInverse();
		}
	}
	refleshServerReceiverLED(gameMode);
}
