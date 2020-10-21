#include "IndicateManager.h"
#include "SegmentDriver.h"
#include "GameManager.h"
#include "FullColorLEDDriver.h"
#include "cmsis_os.h"
#include "LCDDisplayDriver.h"
#include <string.h>
#include <stdio.h>

static void printLCD(uint32_t scoreLeft, uint32_t scoreRight, uint32_t gameLeft, uint32_t gameRight);

void IndicateManagingTask(const void* args)
{
  Initialize_LCDDisplayDriver();

  ClearChar_LCDDisplayDriver();

  uint32_t scoreLeft = 0;
  uint32_t scoreRight = 0;
  uint32_t gameLeft = 0;
  uint32_t gameRight = 0;

  printLCD(scoreLeft, scoreRight, gameLeft, gameRight);

  while(1){
    uint32_t scoreLeftNew = GetScoreCount(PLAYSIDE_LEFT);
    uint32_t scoreRightNew = GetScoreCount(PLAYSIDE_RIGHT);
    uint32_t gameLeftNew = GetGameCount(PLAYSIDE_LEFT);
    uint32_t gameRightNew = GetGameCount(PLAYSIDE_RIGHT);

    PlayerColor_t serverColor = GetCurrentServerColor();
    PlayerColor_t receiverColor = GetCurrentReceiverColor();
    
    SetValue(LEFT_SCORE_INDICATOR, scoreLeftNew);
    SetValue(RIGHT_SCORE_INDICATOR, scoreRightNew);
    SetValue(LEFT_GAMECOUNT_INDICATOR, gameLeftNew);
    SetValue(RIGHT_GAMECOUNT_INDICATOR, gameRightNew);

    SetServerLEDColor((LEDColor_t)serverColor);
    SetReceiverLEDColor((LEDColor_t)receiverColor);
    
    if(scoreLeftNew != scoreLeft ||
        scoreRightNew != scoreRight ||
        gameLeftNew != gameLeft ||
        gameRightNew != gameRight){
      printLCD(scoreLeftNew, scoreRightNew, gameLeftNew, gameRightNew);
    }

    scoreLeft = scoreLeftNew;
    scoreRight = scoreRightNew;
    gameLeft = gameLeftNew;
    gameRight = gameRightNew;

    osDelay(20);
  }
}
void printLCD(uint32_t scoreLeft, uint32_t scoreRight, uint32_t gameLeft, uint32_t gameRight)
{
  char gameChar[20];
  char pointChar[20];
  
  sprintf(gameChar, "Game : %d - %d", (int)gameLeft, (int)gameRight);
  sprintf(pointChar, "Point : %d - %d", (int)scoreLeft, (int)scoreRight);
  
  ClearChar_LCDDisplayDriver();
  SetChar_LCDDisplayDriver((uint8_t*)gameChar, strlen(gameChar), 1);
  SetChar_LCDDisplayDriver((uint8_t*)pointChar, strlen(pointChar), 2);
}
