#include "SegmentDriver.h"
#include "gpio.h"
#include "cmsis_os.h"
#include "main.h"
#include "stm32l4xx_hal_gpio.h"

//private definition
#define SEGMENT_ON GPIO_PIN_SET
#define SEGMENT_OFF GPIO_PIN_RESET
#define NUMBER_OF_SEGMENTS 7
#define NUMBER_OF_INDICATOR 6
#define INDICATOR_INDEX_LEFTSCORE_UPPER 0
#define INDICATOR_INDEX_LEFTSCORE_LOWER 1
#define INDICATOR_INDEX_LEFTGAME 2
#define INDICATOR_INDEX_RIGHTGAME 3
#define INDICATOR_INDEX_RIGHTSCORE_UPPER 4
#define INDICATOR_INDEX_RIGHTSCORE_LOWER 5
#define SEGMENT_POS_TOP 0
#define SEGMENT_POS_TOPLEFT 1
#define SEGMENT_POS_TOPRIGHT 2
#define SEGMENT_POS_MIDDLE 3
#define SEGMENT_POS_BOTTOMLEFT 4
#define SEGMENT_POS_BOTTOMRIGHT 5
#define SEGMENT_POS_BOTTOM 6
#define DYNAMIC_LIGHTING_PERIOD_ms 2

//private typedef
typedef GPIO_PinState SegmentAnode_state_t;

//private valuables
static SegmentAnode_state_t segmentLEDStates[NUMBER_OF_INDICATOR][NUMBER_OF_SEGMENTS];
static const GPIO_TypeDef* segmentGPIOPorts[NUMBER_OF_SEGMENTS] = {
  SEGMENT_ANODE_TOP_GPIO_Port,
  SEGMENT_ANODE_TOPLEFT_GPIO_Port,
  SEGMENT_ANODE_TOPRIGHT_GPIO_Port,
  SEGMENT_ANODE_MIDDLE_GPIO_Port,
  SEGMENT_ANODE_BOTTOMLEFT_GPIO_Port,
  SEGMENT_ANODE_BOTTOMRIGHT_GPIO_Port,
  SEGMENT_ANODE_BOTTOM_GPIO_Port
};
static const uint16_t segmentGPIOPins[NUMBER_OF_SEGMENTS] = {
  SEGMENT_ANODE_TOP_Pin,
  SEGMENT_ANODE_TOPLEFT_Pin,
  SEGMENT_ANODE_TOPRIGHT_Pin,
  SEGMENT_ANODE_MIDDLE_Pin,
  SEGMENT_ANODE_BOTTOMLEFT_Pin,
  SEGMENT_ANODE_BOTTOMRIGHT_Pin,
  SEGMENT_ANODE_BOTTOM_Pin
};

static const GPIO_TypeDef* indicatorSelGPIOPorts[NUMBER_OF_INDICATOR] = {
  SEGMENT_CH_LEFTSCORE_UPPER_GPIO_Port,
  SEGMENT_CH_LEFTSCORE_LOWER_GPIO_Port,
  SEGMENT_CH_LEFTGAMECOUNT_GPIO_Port,
  SEGMENT_CH_RIGHTGAMECOUNT_GPIO_Port,
  SEGMENT_CH_RIGHTSCORE_UPPER_GPIO_Port,
  SEGMENT_CH_RIGHTSCORE_LOWER_GPIO_Port,
};
static const uint16_t indicatorSelGPIOPins[NUMBER_OF_INDICATOR] = {
  SEGMENT_CH_LEFTSCORE_UPPER_Pin,
  SEGMENT_CH_LEFTSCORE_LOWER_Pin,
  SEGMENT_CH_LEFTGAMECOUNT_Pin,
  SEGMENT_CH_RIGHTGAMECOUNT_Pin,
  SEGMENT_CH_RIGHTSCORE_UPPER_Pin,
  SEGMENT_CH_RIGHTSCORE_LOWER_Pin,
};

//private functions
static void setSegmentValue(int indicatorIndex, uint8_t value);
static void selectIndicator(int indicatorIndex);
static void reflectSegmentValue(int indicatorIndex);

void SegmentDriverTask(const void* args)
{
  int indicatorIndex = INDICATOR_INDEX_LEFTSCORE_UPPER;

  while(1){
    //CH select
    selectIndicator(indicatorIndex);

    //set segment state
    reflectSegmentValue(indicatorIndex);

    //index increment
    indicatorIndex = (indicatorIndex + 1) % NUMBER_OF_INDICATOR;

    //delay
    osDelay(DYNAMIC_LIGHTING_PERIOD_ms);
  }
}
void SetValue(IndicatorName_t indicatorName, uint8_t value)
{
  switch(indicatorName){
    case LEFT_SCORE_INDICATOR:
      setSegmentValue(INDICATOR_INDEX_LEFTSCORE_UPPER, value / 10);
      setSegmentValue(INDICATOR_INDEX_LEFTSCORE_LOWER, value % 10);
      break;
    case LEFT_GAMECOUNT_INDICATOR:
      setSegmentValue(INDICATOR_INDEX_LEFTGAME, value);
      break;
    case RIGHT_GAMECOUNT_INDICATOR:
      setSegmentValue(INDICATOR_INDEX_RIGHTGAME, value);
      break;
    case RIGHT_SCORE_INDICATOR:
      setSegmentValue(INDICATOR_INDEX_RIGHTSCORE_UPPER, value / 10);
      setSegmentValue(INDICATOR_INDEX_RIGHTSCORE_LOWER, value % 10);
      break;
    default:
      break;
  }
}

void setSegmentValue(int indicatorIndex, uint8_t value)
{
  uint8_t valueToWrite = value % 10;

  if(valueToWrite == 0 ||
      valueToWrite == 2 ||
      valueToWrite == 3 || 
      valueToWrite == 5 ||
      valueToWrite == 6 || 
      valueToWrite == 7 ||
      valueToWrite == 8 || 
      valueToWrite == 9){
    segmentLEDStates[indicatorIndex][SEGMENT_POS_TOP] = SEGMENT_ON;
  }else{
    segmentLEDStates[indicatorIndex][SEGMENT_POS_TOP] = SEGMENT_OFF;
  }
  
  if(valueToWrite == 0 ||
      valueToWrite == 4 ||
      valueToWrite == 5 ||
      valueToWrite == 6 || 
      valueToWrite == 8 || 
      valueToWrite == 9){
    segmentLEDStates[indicatorIndex][SEGMENT_POS_TOPLEFT] = SEGMENT_ON;
  }else{
    segmentLEDStates[indicatorIndex][SEGMENT_POS_TOPLEFT] = SEGMENT_OFF;
  }

  if(valueToWrite == 0 ||
      valueToWrite == 1 ||
      valueToWrite == 2 ||
      valueToWrite == 3 ||
      valueToWrite == 4 ||
      valueToWrite == 7 ||
      valueToWrite == 8 || 
      valueToWrite == 9){
    segmentLEDStates[indicatorIndex][SEGMENT_POS_TOPRIGHT] = SEGMENT_ON;
  }else{
    segmentLEDStates[indicatorIndex][SEGMENT_POS_TOPRIGHT] = SEGMENT_OFF;
  }

  if(valueToWrite == 2 ||
      valueToWrite == 3 ||
      valueToWrite == 4 ||
      valueToWrite == 3 ||
      valueToWrite == 5 ||
      valueToWrite == 6 ||
      valueToWrite == 8 || 
      valueToWrite == 9){
    segmentLEDStates[indicatorIndex][SEGMENT_POS_MIDDLE] = SEGMENT_ON;
  }else{
    segmentLEDStates[indicatorIndex][SEGMENT_POS_MIDDLE] = SEGMENT_OFF;
  }

  if(valueToWrite == 0 ||
      valueToWrite == 2 ||
      valueToWrite == 6 ||
      valueToWrite == 8){
    segmentLEDStates[indicatorIndex][SEGMENT_POS_BOTTOMLEFT] = SEGMENT_ON;
  }else{
    segmentLEDStates[indicatorIndex][SEGMENT_POS_BOTTOMLEFT] = SEGMENT_OFF;
  }

  if(valueToWrite == 0 ||
      valueToWrite == 1 ||
      valueToWrite == 3 ||
      valueToWrite == 4 ||
      valueToWrite == 5 ||
      valueToWrite == 6 ||
      valueToWrite == 7 ||
      valueToWrite == 8 ||
      valueToWrite == 9){
    segmentLEDStates[indicatorIndex][SEGMENT_POS_BOTTOMRIGHT] = SEGMENT_ON;
  }else{
    segmentLEDStates[indicatorIndex][SEGMENT_POS_BOTTOMRIGHT] = SEGMENT_OFF;
  }

  if(valueToWrite == 0 ||
      valueToWrite == 2 ||
      valueToWrite == 3 ||
      valueToWrite == 5 ||
      valueToWrite == 6 ||
      valueToWrite == 8){
    segmentLEDStates[indicatorIndex][SEGMENT_POS_BOTTOM] = SEGMENT_ON;
  }else{
    segmentLEDStates[indicatorIndex][SEGMENT_POS_BOTTOM] = SEGMENT_OFF;
  }
}
void reflectSegmentValue(int indicatorIndex)
{
  for(int i = 0; i < NUMBER_OF_SEGMENTS; i++){
    HAL_GPIO_WritePin((GPIO_TypeDef*)segmentGPIOPorts[i], segmentGPIOPins[i], segmentLEDStates[indicatorIndex][i]);
  }
}
void selectIndicator(int indicatorIndex)
{
  for(int i = 0; i < NUMBER_OF_INDICATOR; i++){
    if(i == indicatorIndex){
      HAL_GPIO_WritePin((GPIO_TypeDef*)indicatorSelGPIOPorts[i], indicatorSelGPIOPins[i], GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin((GPIO_TypeDef*)indicatorSelGPIOPorts[i], indicatorSelGPIOPins[i], GPIO_PIN_RESET);
    }
  }
}
