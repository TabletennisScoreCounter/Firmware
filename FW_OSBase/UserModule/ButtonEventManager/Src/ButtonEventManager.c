#include "ButtonEventManager.h"
#include "gpio.h"

#define NUMBER_OF_BUTTONS 4

#define NO_BUTTON_PUSHED NUMBER_OF_BUTTONS

static ButtonEvent_t eventStatus = NO_EVENT;

static const GPIO_TypeDef* buttonGPIOPorts[NUMBER_OF_BUTTONS] = {
    BUTTON_COUNTUP_LEFTSCORE_GPIO_Port,
    BUTTON_COUNTUP_RIGHTSCORE_GPIO_Port,
    BUTTON_SERVERSWAP_GPIO_Port,
    BUTTON_RECEIVERSWAP_GPIO_Port,
    B1_GPIO_Port
}
static const uint16_t buttonGPIOPins[NUMBER_OF_BUTTONS] = {
    BUTTON_COUNTUP_LEFTSCORE_Pin,
    BUTTON_COUNTUP_RIGHTSCORE_Pin,
    BUTTON_SERVERSWAP_Pin,
    BUTTON_RECEIVERSWAP_Pin,
    B1_Pin
}
static const ButtonEvent_t buttonEventMap[NUMBER_OF_BUTTONS + 1] = {
    LEFTSCORE_BUTTON_PUSH,
    RIGHTSCORE_BUTTON_PUSH,
    SERVER_SWAP_PUSH,
    RECEIVER_SWAP_PUSH,
    BLUE_BUTTON_PUSH,
    NO_BUTTON_PUSHED
}
static bool buttonPushLong[NUMBER_OF_BUTTONS] = {
    false;
    false;
    false;
    false;
    false;
}

static int checkPushedButtonIndex()
{
    int result = NO_BUTTON_PUSHED;

    for(int i = 0; i < NUMBER_OF_BUTTONS; i++){
        if(HAL_GPIO_ReadPin(buttonGPIOPorts[i], buttonGPIOPins[i]) == GPIO_PIN_SET){
            result = i;
            break;
        }
    }
}
void ButtonEventManagingTask(const void* args)
{
    buttonEventMap[NO_BUTTON_PUSHED] = NO_EVENT;
    
    while(1){
        if(eventStatus == NO_EVENT){
            eventStatus = buttonEventMap[checkPushedButtonIndex()];
        } 
    }
}
ButtonEvent_t GetLastEvent()
{
    ButtonEvent_t result = eventStatus;
    eventStatus = NO_EVENT;
    
    return result;
}