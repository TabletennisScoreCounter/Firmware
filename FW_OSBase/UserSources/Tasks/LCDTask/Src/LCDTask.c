#include "LCDTask.h"
#include "MiddlewareCommon.h"
#include "TaskCommon.h"
#include "LCDControl.h"

//! スレッドスリープ時間[ms]
#define TASK_SLEEP_TIME 10

//! タスク名
#define TASK_NAME "LCDTask"

//! スタックサイズ[DWORD]
#define TASK_STACK_SIZE 128

#define STRING_QUEUE_DEPTH 5

typedef struct lcdStringsTypeDef{
  const char* line1;
  const char* line2;
}lcdStringTypeDef_t;

static void taskFunc(void* args);

static xQueueHandle stringQueue;

void LCDTask_Start()
{
  stringQueue = xQueueCreate(STRING_QUEUE_DEPTH, sizeof(lcdStringTypeDef_t));
  TaskCommon_CreateTask(TASK_NAME, (os_pthread)taskFunc, osPriorityLow, TASK_STACK_SIZE, NULL);
}
static void taskFunc(void* args)
{
  MiddlewareResultTypeDef_t result = LCDControl_Init();

  while(1){
    lcdStringTypeDef_t buf;
    xQueueReceive(stringQueue, &buf, portMAX_DELAY);

    if(result == Middleware_OK){
      result = LCDControl_Print(buf.line1, buf.line2);
    }
  }
}
void LCDTask_RequestString(const char* _line1, const char* _line2)
{
  lcdStringTypeDef_t buf = {
    .line1 = _line1,
    .line2 = _line2
  };
  xQueueSendToBack(stringQueue, &buf, 0);
}
