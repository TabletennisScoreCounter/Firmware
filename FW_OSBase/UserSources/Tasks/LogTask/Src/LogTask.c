#include "LogTask.h"

#include "TaskCommon.h"
#include <string.h>
#include "usart.h"

//! スレッドスリープ時間[ms]
#define TASK_SLEEP_TIME 10

//! タスク名
#define TASK_NAME "LogTask"

//! スタックサイズ[DWORD]
#define TASK_STACK_SIZE 256

#define MESSAGE_QUEUE_DEPTH 20
#define QUEUE_SIZE (LOGMESSAGE_MAX_LENGTH + 1)
#define LOG_UART_HANDLE huart2
#define EOL "\r\n"

static void taskFunc(void* args);

static QueueHandle_t requestedMessageQueueHandle = NULL;
static bool uartTxRunningFlg = false;

void LogTask_Start()
{
  requestedMessageQueueHandle = xQueueCreate(MESSAGE_QUEUE_DEPTH, sizeof(char) * QUEUE_SIZE);
  TaskCommon_CreateTask(TASK_NAME, (os_pthread)taskFunc, osPriorityLow, TASK_STACK_SIZE, NULL);
}
bool LogTask_RequenstLogPrint(const char* _logMessage)
{
  bool result = true;

  int length = strlen(_logMessage);

  if(length > LOGMESSAGE_MAX_LENGTH){
    result = false;
  }else{
    char buffer[QUEUE_SIZE] = {0};
    strncpy(buffer, _logMessage, length);

    result = (pdPASS == xQueueSendToBack(requestedMessageQueueHandle, buffer, 0));
  }

  return result;
}
bool LogTask_RequenstLogPrintLn(const char* _logMessage)
{
  bool result = LogTask_RequenstLogPrint(_logMessage);

  if(result){
    LogTask_RequenstLogPrint(EOL);
  }

  return result;
}
static void taskFunc(void* args)
{
  while(1){
    if(!uartTxRunningFlg){
      char buf[LOGMESSAGE_MAX_LENGTH] = {0};
      xQueueReceive(requestedMessageQueueHandle, buf, portMAX_DELAY);
      uartTxRunningFlg = true;
      HAL_UART_Transmit_IT(&LOG_UART_HANDLE, (const uint8_t*)buf, strlen((const char*)buf));
    }else{
      osDelay(TASK_SLEEP_TIME);
    }
  }
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &LOG_UART_HANDLE){
    uartTxRunningFlg = false;
  }
}
