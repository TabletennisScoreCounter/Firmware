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
void callBack();
void callBackButton();
void callBackButton2();
void callBackChattering();
void callBackChattering2();
void refleshSegmentValue();
static bool chatteringTimerFlag = false;
static bool chatteringTimerFlag2 = false;
SegmentControl* seg/*(PB4,PB10,PA8,PA4,PA1,PA0,PB5)*/;
BusOut* channelSel/*(PA5, PA6, PA7, PB6, PC7, PA9)*/;
uint8_t segmentValue[6]{0};
ScoreManager scoreManager;
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
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();

  /* USER CODE BEGIN 2 */
  seg = new SegmentControl(PB4,PB10,PA8,PA4,PA1,PA0,PB5);
  channelSel = new BusOut(PA5, PA6, PA7, PB6, PC7, PA9);

//  seg->write(0);
//  seg->write(1);
//  seg->write(2);
//
//  *channelSel = 0x01;
//  *channelSel = 0x02;
//  *channelSel = 0x04;
//  *channelSel = 0x08;
//  *channelSel = 0x10;
//  *channelSel = 0x20;
//  *channelSel = 0x00;

  IRQAttachTIM2(callBack);
  IRQAttachTIM3(callBackChattering);
  IRQAttachTIM4(callBackChattering2);

  startTIM2();

  GPIOIRQAttach(PB8,callBackButton);
  GPIOIRQAttach(PB9,callBackButton2);
  /* USER CODE END 2 */



  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
	/*
	switch (count % 3) {
		case 0:
			channelSel = 0x01 | 0x02;
			break;
		case 1:
			channelSel = 0x04 | 0x08;
			break;
		case 2:
			channelSel = 0x10 | 0x20;
			break;
		default:
			break;
	}
	*/


	*channelSel = (0x01 << count);
	*seg = segmentValue[count];

	count++;
	if (count >= 6) {
		count = 0;
	}
}
void callBackButton()
{
	if(!chatteringTimerFlag){
		scoreManager.addMyPoint();

//		segmentValue[0] = scoreManager.getMyPoint() / 10;
//		segmentValue[1] = scoreManager.getMyPoint() % 10;
//
//		segmentValue[2] = scoreManager.getMyGame();
//		segmentValue[3] = scoreManager.getEnemyGame();
//
//		segmentValue[4] = scoreManager.getEnemyPoint() / 10;
//		segmentValue[5] = scoreManager.getEnemyPoint() % 10;
		refleshSegmentValue();
		startTIM3();
		chatteringTimerFlag = true;
	}

}
void callBackButton2()
{
	if(!chatteringTimerFlag2){
		scoreManager.addEnemyPoint();
		refleshSegmentValue();
		startTIM4();
		chatteringTimerFlag2 = true;
	}
}

void callBackChattering()
{
	chatteringTimerFlag = false;
	stopTIM3();
}
void callBackChattering2()
{
	chatteringTimerFlag2 = false;
	stopTIM4();
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
