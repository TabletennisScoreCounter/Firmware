#include "ButtonEventManager.h"
#include <stdbool.h>
#include "gpio.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"


typedef enum{
  STATUS_STANDBY,
  STATUS_LONGPUSH_CHECKING,
  STATUS_DEADTIME
}ModuleStatus_t;

#define NUMBER_OF_BUTTONS 5

#define NO_BUTTON_PUSHED NUMBER_OF_BUTTONS

#define TIMER_HANDLE_LONGPUSH_CHECK htim4

#define LONGPUSH_TIMER_COUNT_THRESHOLD_MS 2000
#define DEADTIME_TIMER_COUNT_THRESHOLD_MS 500

static ButtonEvent_t eventStatus = NO_EVENT;

static ModuleStatus_t moduleStatus = STATUS_STANDBY;

static const GPIO_TypeDef* buttonGPIOPorts[NUMBER_OF_BUTTONS] = {
    BUTTON_COUNTUP_LEFTSCORE_GPIO_Port,
    BUTTON_COUNTUP_RIGHTSCORE_GPIO_Port,
    BUTTON_SERVERSWAP_GPIO_Port,
    BUTTON_RECEIVERSWAP_GPIO_Port,
    BLUE_BUTTON_GPIO_Port
};
static const uint16_t buttonGPIOPins[NUMBER_OF_BUTTONS] = {
    BUTTON_COUNTUP_LEFTSCORE_Pin,
    BUTTON_COUNTUP_RIGHTSCORE_Pin,
    BUTTON_SERVERSWAP_Pin,
    BUTTON_RECEIVERSWAP_Pin,
    BLUE_BUTTON_Pin
};
static const ButtonEvent_t buttonEventMap[NUMBER_OF_BUTTONS + 1] = {
    LEFTSCORE_BUTTON_PUSH,
    RIGHTSCORE_BUTTON_PUSH,
    SERVER_SWAP_PUSH,
    RECEIVER_SWAP_PUSH,
    BLUE_BUTTON_PUSH,
    NO_BUTTON_PUSHED
};
static const GPIO_PinState buttonAssertStates[NUMBER_OF_BUTTONS] = {
  GPIO_PIN_RESET,
  GPIO_PIN_RESET,
  GPIO_PIN_RESET,
  GPIO_PIN_RESET,
  GPIO_PIN_RESET,
};
static bool buttonPushLong[NUMBER_OF_BUTTONS] = {
    false,
    false,
    false,
    false,
    false,
};

static void resetTimerCount();
static bool checkTimerCountErapsed(int targetCount);
static bool checkButtonPushed(int index);

bool checkButtonPushed(int index)
{
  return (HAL_GPIO_ReadPin((GPIO_TypeDef*)buttonGPIOPorts[index], buttonGPIOPins[index]) == buttonAssertStates[index]);
}
void resetTimerCount()
{
  __HAL_TIM_SET_COUNTER(&TIMER_HANDLE_LONGPUSH_CHECK, 0);
}
bool checkTimerCountErapsed(int targetCount)
{
  return (__HAL_TIM_GET_COUNTER(&TIMER_HANDLE_LONGPUSH_CHECK) >= targetCount);
}
int checkPushedButtonIndex()
{
  int result = NO_BUTTON_PUSHED;

  for(int i = 0; i < NUMBER_OF_BUTTONS; i++){
    if(checkButtonPushed(i)){
      result = i;
      break;
    }
  }

  return result;
}
void ButtonEventManagingTask(const void* args)
{
  int lastPushedButtonIndex = NO_BUTTON_PUSHED;

  HAL_TIM_Base_Start(&TIMER_HANDLE_LONGPUSH_CHECK);

  while(1){
    switch(moduleStatus){
      case STATUS_STANDBY:
        lastPushedButtonIndex = checkPushedButtonIndex();
        if(lastPushedButtonIndex != NO_BUTTON_PUSHED){
          moduleStatus = STATUS_LONGPUSH_CHECKING;
          resetTimerCount();
        }
        break;
      case STATUS_LONGPUSH_CHECKING:
        if(!checkTimerCountErapsed(LONGPUSH_TIMER_COUNT_THRESHOLD_MS) && !checkButtonPushed(lastPushedButtonIndex)){//時間内にボタンが離されたら
          eventStatus = buttonEventMap[lastPushedButtonIndex];//押下イベント発生
          buttonPushLong[lastPushedButtonIndex] = false;//短時間押下
          moduleStatus = STATUS_DEADTIME;//デッドタイム入り
          resetTimerCount();//デッドタイムカウント開始
        }else if(checkTimerCountErapsed(LONGPUSH_TIMER_COUNT_THRESHOLD_MS) && checkButtonPushed(lastPushedButtonIndex)){//ボタンが押されたまま時間経過したら
          eventStatus = buttonEventMap[lastPushedButtonIndex];//押下イベント発生
          buttonPushLong[lastPushedButtonIndex] = true;//長時間押下
          moduleStatus = STATUS_DEADTIME;//デッドタイム入り
          resetTimerCount();//デッドタイムカウント開始
        }else{
          //Do Nothing
        }
        break;
      case STATUS_DEADTIME:
        if(checkTimerCountErapsed(DEADTIME_TIMER_COUNT_THRESHOLD_MS) && !checkButtonPushed(lastPushedButtonIndex)){//デッドタイム経過し, ボタンが離されていたら
          lastPushedButtonIndex = NO_BUTTON_PUSHED;//ボタン押下履歴消去
          moduleStatus = STATUS_STANDBY;//新規イベント発生許可
        }
        break;
      default:
        break;
    }
    osDelay(10);
  }
}
ButtonEvent_t GetLastEvent()
{
    ButtonEvent_t result = eventStatus;
    eventStatus = NO_EVENT;
    
    return result;
}
