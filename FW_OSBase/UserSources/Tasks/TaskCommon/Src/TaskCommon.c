#include "TaskCommon.h"

osThreadId TaskCommon_CreateTask(const char* _name, os_pthread _threadFunc, osPriority _priority, uint32_t _stackSize, void* _args)
{
  osThreadDef_t threadDef = {
    .name = (char*)_name,
    .pthread = _threadFunc,
    .tpriority = _priority,
    .instances = 0,
    .stacksize = _stackSize
  };

  osThreadId threadHandle = osThreadCreate(&threadDef, _args);

  return threadHandle;
}
