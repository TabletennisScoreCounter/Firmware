#include "MainTask.h"
#include "GameManager.h"
#include "IndicateManager.h"
#include "SegmentDriver.h"
#include "TaskCommon.h"
#include "ButtonEventManager.h"

//! スレッドスリープ時間[ms]
#define TASK_SLEEP_TIME 10

//! タスク名
#define TASK_NAME "MainTask"

//! スタックサイズ[DWORD]
#define TASK_STACK_SIZE 128

/**
 * @brief MainTaskの中身
 *
 * @param args 特に意味はない. NULLでOK
 */
static void mainTask(void* args);

void MainTask_Start(void *args)
{
  TaskCommon_CreateTask(TASK_NAME, (os_pthread)mainTask, osPriorityNormal, TASK_STACK_SIZE, NULL);
}
static void mainTask(void* args)
{
  ButtonPushDetectTask_Start(NULL);
  GameManagingTask_Start(NULL);
  IndicateManagingTask_Start(NULL);
  SegmentDriverTask_Start(NULL);

  while(1){
    osDelay(TASK_SLEEP_TIME);
  }
}
