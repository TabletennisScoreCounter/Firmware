/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"


/* USER CODE BEGIN Includes */
#include "tim.h"
#include "BusOut.hpp"
#include "SegmentControl.hpp"
#include "ScoreManager.hpp"
#include "DigitalOut.hpp"
#include "DoublesPositionManager.hpp"
#include "SinglesPositionManager.hpp"

#include "FullcolorLEDDriver.hpp"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
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

static bool waitingAfterButton = false;
/* USER CODE END 0 */

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();

  /* USER CODE BEGIN 2 */
  initializeServerReceiverLED();

  initializeSegment();

  initializeButtons();

  StartTIM6();

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
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  refleshGameState(gameMode);

	  if(waitingAfterButton){
		  uint16_t currentCount = GetCountTIM6();

		  if(currentCount > 10000){
			  waitingAfterButton = false;
		  }
	  }
  /* USER CODE END WHILE */
  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  __HAL_RCC_PWR_CLK_ENABLE();

  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
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
	if(!waitingAfterButton){
		ClearCountTIM6();
		waitingAfterButton = true;

		if(!antiChatteringFlag[0]){
			if(!longPushFlag[0]){//長押し非検知
				scoreManager.addMyPoint();
				refleshSegmentValue();
				previousAction = UP_MY_POINT;
			}
			else{
				longPushFlag[0] = false;
			}
			antiChatteringFlag[0] = true;
		}
	}
}
void callBackButton2()
{
	if(!waitingAfterButton){
		ClearCountTIM6();
		waitingAfterButton = true;
		if(!antiChatteringFlag[1]){
			if(!longPushFlag[1]){
				scoreManager.addEnemyPoint();
				refleshSegmentValue();
				previousAction = UP_ENEMY_POINT;
			}
			else{
				longPushFlag[1] = false;
			}
			antiChatteringFlag[1] = true;
		}
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
				cancelPreviousAction();
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
			if(scoreManager.isTheGameFinished()){
				changeSideFlag = !changeSideFlag;//MyとEnemyを入れ替え
				scoreManager.swapPoint();
				scoreManager.nextGame();//ゲーム更新
				refleshSegmentValue();
			}
		}
		else{
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
	    }
	    refleshServerReceiverLED(mode);
	    setCount = scoreManager.getGameSum();

     }

     if(scoreManager.isDeuce()){//デュース
		  if(scoreManager.getSum() - myPrevScore - enemyPrevScore > 0 ){//1本進むごとにサーブ交代
			  if(mode == SINGLES){
				  singlesPlayer1.rotatePosition();
				  singlesPlayer2.rotatePosition();

			  }
			  else{
				  player1.rotatePosition();
				  player2.rotatePosition();
				  player3.rotatePosition();
				  player4.rotatePosition();
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
			  }
			  else{
				  player1.rotatePosition();
				  player2.rotatePosition();
				  player3.rotatePosition();
				  player4.rotatePosition();
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

    	 		refleshServerReceiverLED(mode);
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
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler */
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
