#ifndef TASKCOMMON_H_
#define TASKCOMMON_H_

#include <FreeRTOS.h>
#include <cmsis_os.h>

/**
 * @brief タスクを生成する
 *
 * @param _name タスク名
 * @param _threadFunc タスク関数
 * @param _priority タスク優先度
 * @param _stackSize スタックサイズ[DWORD]
 * @param _args タスクに渡す引数(NULL可)
 *
 * @return タスクハンドル
 */
osThreadId TaskCommon_CreateTask(const char* _name, os_pthread _threadFunc, osPriority _priority, uint32_t _stackSize, void* _args);

#endif
