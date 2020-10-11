#include "FullColorLEDDriver.h"
#include "tim.h"

#define NUM_OF_COLORS 4
#define NUM_OF_COLOR_ELEMENTS 3
#define RED_ELEMENT 0
#define GREEN_ELEMENT 1
#define BLUE_ELEMENT 2

#define CONTRAST 0.05

const uint8_t rgbValues[NUM_OF_COLORS][NUM_OF_COLOR_ELEMENTS] = {
  {0, 0, 100},
  {100, 0, 0},
  {0, 100, 0},
  {50, 50, 0}
};

const TIM_HandleTypeDef* serverLED_PWMTimers[NUM_OF_COLOR_ELEMENTS] = {
  &htim1,
  &htim2,
  &htim1
};

const uint32_t serverLED_PWMTimerChannels[NUM_OF_COLOR_ELEMENTS] = {
  TIM_CHANNEL_2,
  TIM_CHANNEL_3,
  TIM_CHANNEL_1
};

const TIM_HandleTypeDef* receiverLED_PWMTimers[NUM_OF_COLOR_ELEMENTS] = {
  &htim3,
  &htim1,
  &htim3
};

const uint32_t receiverLED_PWMTimerChannels[NUM_OF_COLOR_ELEMENTS] = {
  TIM_CHANNEL_1,
  TIM_CHANNEL_3,
  TIM_CHANNEL_2
};

static void setPWMDuty(TIM_HandleTypeDef* phtim, uint32_t timerChannel, uint32_t duty);

void EnableFullColorLED()
{
  for(int i = 0; i < NUM_OF_COLOR_ELEMENTS; i++){
    HAL_TIM_PWM_Start((TIM_HandleTypeDef*)serverLED_PWMTimers[i], serverLED_PWMTimerChannels[i]);
    HAL_TIM_PWM_Start((TIM_HandleTypeDef*)receiverLED_PWMTimers[i], receiverLED_PWMTimerChannels[i]);
  }
}

void SetServerLEDColor(LEDColor_t ledColor)
{
  for(int i = 0; i < NUM_OF_COLOR_ELEMENTS; i++){
    setPWMDuty((TIM_HandleTypeDef*)serverLED_PWMTimers[i], serverLED_PWMTimerChannels[i], rgbValues[ledColor][i]);
  }
  EnableFullColorLED();
}
void SetReceiverLEDColor(LEDColor_t ledColor)
{
  for(int i = 0; i < NUM_OF_COLOR_ELEMENTS; i++){
    setPWMDuty((TIM_HandleTypeDef*)receiverLED_PWMTimers[i], receiverLED_PWMTimerChannels[i], rgbValues[ledColor][i]);
  }
  EnableFullColorLED();
}
void setPWMDuty(TIM_HandleTypeDef* phtim, uint32_t timerChannel, uint32_t duty)
{
  TIM_OC_InitTypeDef sConfigOC;
  
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = (uint32_t)(CONTRAST * (double)duty);
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(phtim, &sConfigOC, timerChannel) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
