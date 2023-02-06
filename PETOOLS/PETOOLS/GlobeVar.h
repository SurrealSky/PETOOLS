//此处用于定义全局的宏定义
#pragma once
#include "stdafx.h"
#include<Windows.h>
#include<MiniDump.h>
#include<LogLib\DebugLog.h>
using namespace SurrealDebugLog;

#include<PELib/PE/PEMake.h>
#ifdef _DEBUG
#pragma comment(lib, "CommonLib\\PELib\\bind\\PELib.lib")
#else
#pragma comment(lib, "CommonLib\\PELib\\bin\\PELib.lib")
#endif

#include<MemoryPool/MemMgr.h>
using namespace SurrealMemMgr;

#ifdef _DEBUG
#pragma comment(lib, "CommonLib\\MemoryPool\\bind\\MemMgr.lib")
#else
#pragma comment(lib, "CommonLib\\MemoryPool\\bin\\MemMgr.lib")
#endif

#include<16Edit/16EditDll.h>
#pragma comment(lib,"CommonLib\\16Edit\\16Edit.lib")


#include<PELib/PE/PEMake.h>
#ifdef _DEBUG
#pragma comment(lib,"PELib.lib")
#else
#pragma comment(lib,"PELib.lib")
#endif

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


