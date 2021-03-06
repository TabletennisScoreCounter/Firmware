/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2020 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

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

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
 #define USE_FULL_ASSERT    1U 

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
