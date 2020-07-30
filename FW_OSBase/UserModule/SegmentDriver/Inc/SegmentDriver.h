#include <stdint.h>

typedef enum {
    LEFT_SCORE_INDICATOR,
    RIGHT_SCORE_INDICATOR,
    LEFT_GAMECOUNT_INDICATOR,
    RIGHT_GAMECOUNT_INDICATOR
}IndicatorName_t;

void SetValue(IndicatorName_t indicatorName, uint8_t value);
void SegmentDriverTask(void* args);
