#include <windows.h>
#include <stdio.h>

#include "./DebugLog.h"
#include"../Common/log4z.h"
using namespace zsummer::log4z;


void DebugLog(LPCSTR lpOutputString)
{
#ifdef Dbg
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./log");
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
	//LOGD: LOG WITH level LOG_DEBUG
	//LOGI: LOG WITH level LOG_INFO

	LOGD(lpOutputString);

#endif
}

void DebugLog(LPCSTR lpTag, LPCSTR lpOutputString)
{
#ifdef Dbg
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./log");
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
	//LOGD: LOG WITH level LOG_DEBUG
	//LOGI: LOG WITH level LOG_INFO

	LOGFMTT("%s:%s(%d)", lpTag,lpOutputString,strlen(lpOutputString));

#endif
}

void DebugLogHex(LPCSTR lpTag, LPCSTR lpOutputString,DWORD lpOutputStringLen)
{
#ifdef Dbg
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./log");
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
	//LOGD: LOG WITH level LOG_DEBUG
	//LOGI: LOG WITH level LOG_INFO

	LOGD(lpTag<<":"<<Log4zBinary(lpOutputString, lpOutputStringLen));
	//LOGD(lpTag << ":" << lpOutputStringLen);

#endif
}