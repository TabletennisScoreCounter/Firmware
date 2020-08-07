#include <stdint.h>

typedef enum{
    LEFTSCORE_BUTTON_PUSH,
    RIGHTSCORE_BUTTON_PUSH,
    BLUE_BUTTON_PUSH,
    SERVER_SWAP_PUSH,
    RECEIVER_SWAP_PUSH,
    NO_EVENT
}ButtonEvent_t;

void ButtonEventManagingTask(const void* args);
ButtonEvent_t GetLastEvent();