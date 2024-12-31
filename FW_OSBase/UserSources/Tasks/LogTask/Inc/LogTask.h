#ifndef LOGTASK_H_
#define LOGTASK_H_

#include <stdbool.h>

#define LOGMESSAGE_MAX_LENGTH 100

void LogTask_Start();
bool LogTask_RequenstLogPrint(const char* _logMessage);
bool LogTask_RequenstLogPrintLn(const char* _logMessage);

#endif
