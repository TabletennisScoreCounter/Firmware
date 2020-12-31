#include <stdint.h>

#define LONG_PUSH_FLAG 0x10

typedef enum{
    LEFTSCORE_BUTTON_PUSH = 0,
    RIGHTSCORE_BUTTON_PUSH,
    BLUE_BUTTON_PUSH,
    SERVER_SWAP_PUSH,
    RECEIVER_SWAP_PUSH,

    LEFTSCORE_BUTTON_PUSH_LONG = LEFTSCORE_BUTTON_PUSH | LONG_PUSH_FLAG,
    RIGHTSCORE_BUTTON_PUSH_LONG = RIGHTSCORE_BUTTON_PUSH | LONG_PUSH_FLAG,
    BLUE_BUTTON_PUSH_LONG = BLUE_BUTTON_PUSH | LONG_PUSH_FLAG,
    SERVER_SWAP_PUSH_LONG = SERVER_SWAP_PUSH | LONG_PUSH_FLAG,
    RECEIVER_SWAP_PUSH_LONG = RECEIVER_SWAP_PUSH | LONG_PUSH_FLAG,

    NO_EVENT
}ButtonEvent_t;

void ButtonEventManagingTask(const void* args);
ButtonEvent_t GetLastEvent();
