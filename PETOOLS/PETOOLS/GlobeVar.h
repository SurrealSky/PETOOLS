//此处用于定义全局的宏定义
#pragma once
#include "stdafx.h"
#include<Windows.h>
#include<MiniDump.h>
#include<LogLib\DebugLog.h>
using namespace SurrealDebugLog;

#include"../MemoryPool/MemMgr.h"
using namespace SurrealMemMgr;

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MemMgr.lib")
#else
#pragma comment(lib, "..\\Release\\MemMgr.lib")
#endif

#include"../OtherLib/16Edit/16EditDll.h"

#pragma comment(lib,"MemoryPool.lib")
#pragma comment(lib,"PELib.lib")
#pragma comment(lib,"..\\OtherLib\\16Edit\\16Edit.lib")

#ifdef UNICODE

#define MAX_LENGTH 128
#define MAX_FUNLENGTH  128
#define MAX_HEADLENGTH	128
#else
#define MAX_LENGTH 128
#define MAX_FUNLENGTH  128
#define MAX_HEADLENGTH	128
#endif


extern const char *UNUSE;
#define xLength	4
extern TCHAR *_TUNUSE;
#define xxLength	8


void Create16EditWindow(unsigned char *buffer, unsigned int size, unsigned int startoff, unsigned int endoff);


