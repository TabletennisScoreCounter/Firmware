#include "LCDTask.h"
#include "TaskCommon.h"

//! スレッドスリープ時間[ms]
#define TASK_SLEEP_TIME 10

//! タスク名
#define TASK_NAME "LCDTask"

//! スタックサイズ[DWORD]
#define TASK_STACK_SIZE 128

static void taskFunc(void* args);

void LCDTask_Start()
{
  TaskCommon_CreateTask(TASK_NAME, (os_pthread)taskFunc, osPriorityNormal, TASK_STACK_SIZE, NULL);
}
static void taskFunc(void* args)
{
}
