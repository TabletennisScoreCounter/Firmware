#include "GameManager.h"
#include "gpio.h"
#include "main.h"
#include "cmsis_os.h"

typedef enum{
  SINGLES_MODE,
  DOUBLES_MODE
}GameMode_t;

typedef enum{
  ROLE_SERVER,
  ROLE_SERVER_PARTNER,
  ROLE_RECEIVER,
  ROLE_RECEIVER_PARTENR
}PlayerRole_t;

static GameMode_t checkGameModeSwitch();
static void singlesGameSequence();
static void doublesGameSequence();

void GameManagingTask(const void* args)
{
  GameMode_t gameMode = checkGameModeSwitch();

  if(gameMode == SINGLES_MODE){
    singlesGameSequence();
  }else{
    doublesGameSequence();
  }
}
void singlesGameSequence()
{
  while(1){
    osDelay(10);
  }
}
void doublesGameSequence()
{
  while(1){
    osDelay(10);
  }
}
GameMode_t checkGameModeSwitch()
{
  GameMode_t result = SINGLES_MODE;

  if(HAL_GPIO_ReadPin(GAMEMODE_SELECT_SWITCH_GPIO_Port, GAMEMODE_SELECT_SWITCH_Pin) == GPIO_PIN_SET){
    result = SINGLES_MODE;
  }else{
    result = DOUBLES_MODE;
  }
  return result;
}
