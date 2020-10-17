#include "IndicateManager.h"
#include "SegmentDriver.h"
#include "GameManager.h"
#include "FullColorLEDDriver.h"
#include "cmsis_os.h"

void IndicateManagingTask(const void* args)
{
  while(1){
    uint32_t scoreLeft = GetScoreCount(PLAYSIDE_LEFT);
    uint32_t scoreRight = GetScoreCount(PLAYSIDE_RIGHT);
    uint32_t gameLeft = GetGameCount(PLAYSIDE_LEFT);
    uint32_t gameRight = GetGameCount(PLAYSIDE_RIGHT);

    PlayerColor_t serverColor = GetCurrentServerColor();
    PlayerColor_t receiverColor = GetCurrentReceiverColor();
    
    SetValue(LEFT_SCORE_INDICATOR, scoreLeft);
    SetValue(RIGHT_SCORE_INDICATOR, scoreRight);
    SetValue(LEFT_GAMECOUNT_INDICATOR, gameLeft);
    SetValue(RIGHT_GAMECOUNT_INDICATOR, gameRight);

    SetServerLEDColor((LEDColor_t)serverColor);
    SetReceiverLEDColor((LEDColor_t)receiverColor);

    osDelay(20);
  }
}
