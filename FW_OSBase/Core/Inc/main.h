/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLUE_BUTTON_Pin GPIO_PIN_13
#define BLUE_BUTTON_GPIO_Port GPIOC
#define BUTTON_RECEIVERSWAP_Pin GPIO_PIN_3
#define BUTTON_RECEIVERSWAP_GPIO_Port GPIOC
#define BUTTON_COUNTUP_LEFTSCORE_Pin GPIO_PIN_0
#define BUTTON_COUNTUP_LEFTSCORE_GPIO_Port GPIOA
#define BUTTON_COUNTUP_RIGHTSCORE_Pin GPIO_PIN_1
#define BUTTON_COUNTUP_RIGHTSCORE_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define BUTTON_SERVERSWAP_Pin GPIO_PIN_4
#define BUTTON_SERVERSWAP_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define SEGMENT_CH_RIGHTSCORE_UPPER_Pin GPIO_PIN_4
#define SEGMENT_CH_RIGHTSCORE_UPPER_GPIO_Port GPIOC
#define SEGMENT_ANODE_BOTTOMLEFT_Pin GPIO_PIN_5
#define SEGMENT_ANODE_BOTTOMLEFT_GPIO_Port GPIOC
#define GAMEMODE_SELECT_SWITCH_Pin GPIO_PIN_0
#define GAMEMODE_SELECT_SWITCH_GPIO_Port GPIOB
#define SEGMENT_CH_LEFTSCORE_UPPER_Pin GPIO_PIN_1
#define SEGMENT_CH_LEFTSCORE_UPPER_GPIO_Port GPIOB
#define SEGMENT_CH_LEFTSCORE_LOWER_Pin GPIO_PIN_2
#define SEGMENT_CH_LEFTSCORE_LOWER_GPIO_Port GPIOB
#define SERVERLEDANODE_GREEN_Pin GPIO_PIN_10
#define SERVERLEDANODE_GREEN_GPIO_Port GPIOB
#define SEGMENT_ANODE_MIDDLE_Pin GPIO_PIN_11
#define SEGMENT_ANODE_MIDDLE_GPIO_Port GPIOB
#define SEGMENT_ANODE_TOPLEFT_Pin GPIO_PIN_12
#define SEGMENT_ANODE_TOPLEFT_GPIO_Port GPIOB
#define SEGMENT_CH_RIGHTSCORE_LOWER_Pin GPIO_PIN_13
#define SEGMENT_CH_RIGHTSCORE_LOWER_GPIO_Port GPIOB
#define SEGMENT_CH_RIGHTGAMECOUNT_Pin GPIO_PIN_14
#define SEGMENT_CH_RIGHTGAMECOUNT_GPIO_Port GPIOB
#define SEGMENT_CH_LEFTGAMECOUNT_Pin GPIO_PIN_15
#define SEGMENT_CH_LEFTGAMECOUNT_GPIO_Port GPIOB
#define SEGMENT_ANODE_BOTTOM_Pin GPIO_PIN_6
#define SEGMENT_ANODE_BOTTOM_GPIO_Port GPIOC
#define SEGMENT_ANODE_BOTTOMRIGHT_Pin GPIO_PIN_8
#define SEGMENT_ANODE_BOTTOMRIGHT_GPIO_Port GPIOC
#define SERVERLEDANODE_BLUE_Pin GPIO_PIN_8
#define SERVERLEDANODE_BLUE_GPIO_Port GPIOA
#define SERVERLEDANODE_RED_Pin GPIO_PIN_9
#define SERVERLEDANODE_RED_GPIO_Port GPIOA
#define RECEIVERLEDANODE_GREEN_Pin GPIO_PIN_10
#define RECEIVERLEDANODE_GREEN_GPIO_Port GPIOA
#define SEGMENT_ANODE_TOP_Pin GPIO_PIN_11
#define SEGMENT_ANODE_TOP_GPIO_Port GPIOA
#define SEGMENT_ANODE_TOPRIGHT_Pin GPIO_PIN_12
#define SEGMENT_ANODE_TOPRIGHT_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define MATCHCOUNT_SELECT_SWITCH_Pin GPIO_PIN_11
#define MATCHCOUNT_SELECT_SWITCH_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define RECEIVERLEDANODE_RED_Pin GPIO_PIN_4
#define RECEIVERLEDANODE_RED_GPIO_Port GPIOB
#define RECEIVERLEDANODE_BLUE_Pin GPIO_PIN_5
#define RECEIVERLEDANODE_BLUE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
