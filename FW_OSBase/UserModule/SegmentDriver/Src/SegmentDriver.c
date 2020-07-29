#include "SegmentDriver.h"
#include "gpio.h"

//private definition
#define SEGMENT_ON GPIO_PIN_SET
#define SEGMENT_OFF_GPIO_PIN_RESET
 
//private typedef
typedef GPIO_PinState SegmentAnode_state_t;

//private valuables
static uint8_t segmentValue_leftScoreUpper = 0;
static uint8_t segmentValue_leftScoreLower = 0;
static uint8_t segmentValue_leftGame = 0;
static uint8_t segmentValue_rightGame = 0;
static uint8_t segmentValue_rightScoreUpper = 0;
static uint8_t segmentValue_rightScoreLower = 0;


//private functions


void SegmentDriverTask(void* args)
{
}
void SetValue(SegmentPairName_t segmentPair, uint8_t value)
{
  switch(segmentPair){
    case LEFT_SCORE_SEGMENTPAIR:
      segmentValue_leftScoreLower = value % 10;
      segmentValue_leftScoreUpper = value / 10;
      break;
    case LEFT_GAMECOUNT_SEGMENT_PAIR:
      segmentValue_leftGame = value;
      break;
    case RIGHT_GAMECOUNT_SEGMENT_PAIR:
      segmentValue_rightGame = value;
      break;
    case RIGHT_SCORE_SEGMENTPAIR:
      segmentValue_rightScoreLower = value % 10;
      segmentValue_rightScoreUpper = value / 10;
      break;
    default:
      break;
  }
}
