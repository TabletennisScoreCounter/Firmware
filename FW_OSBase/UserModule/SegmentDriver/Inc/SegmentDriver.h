#include <stdint.h>

typedef enum {
    LEFT_SCORE_SEGMENTPAIR,
    RIGHT_SCORE_SEGMENTPAIR,
    LEFT_GAMECOUNT_SEGMENT_PAIR,
    RIGHT_GAMECOUNT_SEGMENT_PAIR
}SegmentPairName_t;

void SetValue(SegmentPairName_t segmentPair, uint8_t value);
void SegmentDriverTask(void* args);
