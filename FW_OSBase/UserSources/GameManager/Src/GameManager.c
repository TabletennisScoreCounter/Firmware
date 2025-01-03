#include "GameManager.h"
#include "TaskCommon.h"
#include "gpio.h"
#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>
#include "ButtonEventManager.h"
#include "Flags.h"

#define NUM_OF_PLAYERS 4 
#define NUM_OF_GAMEMODE 2
#define NUM_OF_ROLES 4
#define NUM_OF_SIDE 2
#define NUM_OF_MATCH_RULE 3

#define NORMALY_GAMESET_POINT 11
#define DUCE_POINT 10

#define SERVER_CHANGE_STEP_NORMAL 2
#define SERVER_CHANGE_SETP_DUCE 1

//! スレッドスリープ時間[ms]
#define TASK_SLEEP_TIME 10

//! タスク名
#define TASK_NAME "GameManagingTask"

//! スタックサイズ[DWORD]
#define TASK_STACK_SIZE 128

typedef enum{
  SINGLES_MODE = 0, 
  DOUBLES_MODE
}GameMode_t;

typedef enum{
  ROLE_SERVER = 0,
  ROLE_SERVER_PARTNER,
  ROLE_RECEIVER,
  ROLE_RECEIVER_PARTENR
}PlayerRole_t;

typedef enum {
  THREE_SET_MATCH = 0,
  FIVE_SET_MATCH,
  SEVEN_SET_MATCH
} GameMatchRule_t;

static PlayerRole_t playerRoles[NUM_OF_PLAYERS] = { 
  ROLE_SERVER, 
  ROLE_RECEIVER, 
  ROLE_SERVER_PARTNER, 
  ROLE_RECEIVER_PARTENR 
};

static const int rotationStep[NUM_OF_GAMEMODE] = {
  2,
  3
};

static PlayerColor_t playerColor[NUM_OF_PLAYERS] = {
  PLAYERCOLOR_RED,
  PLAYERCOLOR_BLUE,
  PLAYERCOLOR_GREEN,
  PLAYERCOLOR_YELLOW
};

static uint32_t gameCount[NUM_OF_SIDE] = {
  0,
  0
};

static uint32_t scoreCount[NUM_OF_SIDE] = {
  0,
  0
};

static const uint32_t matchCount[NUM_OF_MATCH_RULE] = {
  2,
  3,
  4
};

static uint32_t scoreCountLog[NUM_OF_SIDE];
static PlayerRole_t playerRolesLog[NUM_OF_PLAYERS];

static void GameManagingTask(const void* args);
static void normalyRotatePlayerRoles(GameMode_t gameMode);
static void receiverSideSwap();
static GameMode_t checkGameModeSwitch();
static void rotationSequence(GameMode_t gameMode);
static void countUpScore(PlaySide_t playSide);
static bool isGameSet();
static void startNextGame();
static void swapSide();
static GameMatchRule_t checkGameMatchRuleSwitch();
static bool checkDuce();
static bool isMatchStarted();
static void cancelPreviousAction();
static void memorizeCurrentStatus();
static bool isStartOfSet();

uint32_t GetScoreCount(PlaySide_t playSide)
{
  return scoreCount[playSide];
}
uint32_t GetGameCount(PlaySide_t playSide)
{
  return gameCount[playSide];
}
PlayerColor_t GetCurrentServerColor()
{
  PlayerColor_t result = PLAYERCOLOR_RED;
  for(int i = 0; i < NUM_OF_PLAYERS; i++){
    if(playerRoles[i] == ROLE_SERVER){
      result = playerColor[i];
      break;
    }
  }
  return result;
}
PlayerColor_t GetCurrentReceiverColor()
{
  PlayerColor_t result = PLAYERCOLOR_RED;
  for(int i = 0; i < NUM_OF_PLAYERS; i++){
    if(playerRoles[i] == ROLE_RECEIVER){
      result = playerColor[i];
      break;
    }
  }
  return result;
}
void GameManagingTask(const void* args)
{
  GameMode_t gameMode = checkGameModeSwitch();

  int countToMatch = matchCount[checkGameMatchRuleSwitch()];

  PlayerRole_t initialPlayerRolesOfTheSet[NUM_OF_PLAYERS];

  memorizeCurrentStatus();

  for(int i = 0; i < NUM_OF_PLAYERS; i++){//セット開始時の配置状態を記録
    initialPlayerRolesOfTheSet[i] = playerRoles[i];
  }

  while(1){
    ButtonEvent_t event = NO_EVENT;
    if(gameCount[PLAYSIDE_LEFT] < countToMatch && gameCount[PLAYSIDE_RIGHT] < countToMatch){//試合終了でなければ, ボタン押下を受け付ける
      event = GetLastEvent();
    }

    switch(event){//イベント応答
      case LEFTSCORE_BUTTON_PUSH:
        memorizeCurrentStatus();
        countUpScore(PLAYSIDE_LEFT);
        if(!isGameSet()){
          rotationSequence(gameMode);
        }
        break;
      case RIGHTSCORE_BUTTON_PUSH:
        memorizeCurrentStatus();
        countUpScore(PLAYSIDE_RIGHT);
        if(!isGameSet()){
          rotationSequence(gameMode);
        }
        break;
      case BLUE_BUTTON_PUSH:
        if(isGameSet()){
          for(int i = 0; i < NUM_OF_PLAYERS; i++){
            playerRoles[i] = initialPlayerRolesOfTheSet[i];
          }
          
          normalyRotatePlayerRoles(gameMode);
          if(gameMode == DOUBLES_MODE){
            receiverSideSwap();
          }

          startNextGame();
          memorizeCurrentStatus();

          for(int i = 0; i < NUM_OF_PLAYERS; i++){//セット開始時の配置状態を記録
            initialPlayerRolesOfTheSet[i] = playerRoles[i];
          }
        }

        break;
      case SERVER_SWAP_PUSH:
        if(isStartOfSet()){
          normalyRotatePlayerRoles(gameMode);
        }
        break;
      case RECEIVER_SWAP_PUSH:
        if(!isMatchStarted() && gameMode == DOUBLES_MODE){
          receiverSideSwap();
        }
        break;
      case BLUE_BUTTON_PUSH_LONG:
        cancelPreviousAction();
        break;
      default:
        break;
    }

    osDelay(10);
  }
}
void rotationSequence(GameMode_t gameMode)
{
  if(!checkDuce()){//デュースになっていないときは, 2ポイントごとにサーバ交代
    if((scoreCount[PLAYSIDE_LEFT] + scoreCount[PLAYSIDE_RIGHT]) % SERVER_CHANGE_STEP_NORMAL == 0){
      normalyRotatePlayerRoles(gameMode);
    }
  }else{//デュースになったら1ポイントごとにサーバ交代
    normalyRotatePlayerRoles(gameMode);
  }
}
GameMode_t checkGameModeSwitch()
{
  GameMode_t result = SINGLES_MODE;

  if(HAL_GPIO_ReadPin(GAMEMODE_SELECT_SWITCH_GPIO_Port, GAMEMODE_SELECT_SWITCH_Pin) == GPIO_PIN_RESET){
    result = SINGLES_MODE;
  }else{
    result = DOUBLES_MODE;
  }
  return result;
}
GameMatchRule_t checkGameMatchRuleSwitch()
{
  GameMatchRule_t result = FIVE_SET_MATCH;
  if(HAL_GPIO_ReadPin(MATCHCOUNT_SELECT_SWITCH_GPIO_Port, MATCHCOUNT_SELECT_SWITCH_Pin) == GPIO_PIN_SET){
    result = SEVEN_SET_MATCH;
  }

  if(REDUCE_GAMES == 1){
    result = (GameMatchRule_t)((int)result - 1);
  }

  return result;
}
void normalyRotatePlayerRoles(GameMode_t gameMode)
{
  for(int i = 0; i < NUM_OF_PLAYERS; i++){
    playerRoles[i] = (PlayerRole_t)(((int)playerRoles[i] + rotationStep[gameMode]) % NUM_OF_ROLES);
  }
}
void receiverSideSwap()
{
  for(int i = 0; i < NUM_OF_PLAYERS; i++){
    switch(playerRoles[i]){
      case ROLE_RECEIVER:
        playerRoles[i] = ROLE_RECEIVER_PARTENR;
        break;
      case ROLE_RECEIVER_PARTENR:
        playerRoles[i] = ROLE_RECEIVER;
        break;
      default:
        break;
    }
  }
}
void countUpScore(PlaySide_t playSide)
{
  if(!isGameSet()){
    scoreCount[playSide]++;
  }
}
bool isGameSet()
{
  bool result = false;

  if(!checkDuce()){//デュースを迎えてなければ, どちらかが11取ったら終わり
    result = (scoreCount[PLAYSIDE_LEFT] == NORMALY_GAMESET_POINT || scoreCount[PLAYSIDE_RIGHT] == NORMALY_GAMESET_POINT);
  }else{//デュース時は, 2ポイント差がつけば終わり
    result = (scoreCount[PLAYSIDE_LEFT] == scoreCount[PLAYSIDE_RIGHT] + 2 || scoreCount[PLAYSIDE_LEFT] == scoreCount[PLAYSIDE_RIGHT] - 2);
  }

  return result;
}
void startNextGame()
{
  if(isGameSet()){
    if(scoreCount[PLAYSIDE_LEFT] > scoreCount[PLAYSIDE_RIGHT]){
      gameCount[PLAYSIDE_LEFT]++;
    }else{
      gameCount[PLAYSIDE_RIGHT]++;
    }

    scoreCount[PLAYSIDE_LEFT] = 0;
    scoreCount[PLAYSIDE_RIGHT] = 0;
    swapSide();
  }
}
void swapSide()
{
  if(CHANGE_SIDE == 1){
    uint32_t leftSidePoint = gameCount[PLAYSIDE_LEFT];

    gameCount[PLAYSIDE_LEFT] = gameCount[PLAYSIDE_RIGHT];
    gameCount[PLAYSIDE_RIGHT] = leftSidePoint;
  }
}
bool checkDuce()
{
  return (scoreCount[PLAYSIDE_LEFT] + scoreCount[PLAYSIDE_RIGHT] >= 2 * DUCE_POINT);
}
bool isMatchStarted()
{
  //ゲーム数もスコア数も全部ゼロ(足して0と同値)でなければスタートしている
  return (scoreCount[PLAYSIDE_LEFT] + scoreCount[PLAYSIDE_RIGHT] + gameCount[PLAYSIDE_LEFT] + gameCount[PLAYSIDE_RIGHT] != 0);
}
void cancelPreviousAction()
{
  for(int i = 0; i < NUM_OF_SIDE; i++){
    scoreCount[i] = scoreCountLog[i];
  }

  for(int i = 0; i < NUM_OF_PLAYERS; i++){
    playerRoles[i] = playerRolesLog[i];
  }
}
void memorizeCurrentStatus()
{
  for(int i = 0; i < NUM_OF_SIDE; i++){
    scoreCountLog[i] = scoreCount[i];
  }

  for(int i = 0; i < NUM_OF_PLAYERS; i++){
    playerRolesLog[i] = playerRoles[i];
  }
}
bool isStartOfSet()
{
  //ゲーム数もスコア数も全部ゼロ(足して0と同値)でなければスタートしている
  return (scoreCount[PLAYSIDE_LEFT] + scoreCount[PLAYSIDE_RIGHT] == 0);
}
void GameManagingTask_Start(void* args)
{
  TaskCommon_CreateTask(TASK_NAME, (os_pthread)GameManagingTask, osPriorityNormal, TASK_STACK_SIZE, NULL);
}
