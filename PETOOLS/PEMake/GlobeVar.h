//此处用于定义全局的宏定义
#pragma once
#include<Windows.h>
#include<typedef.h>
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

#ifdef UNICODE
#define MAX_LENGTH 128
#define MAX_FUNLENGTH  128
#define MAX_HEADLENGTH	128
#else
#define MAX_LENGTH 128
#define MAX_FUNLENGTH  128
#define MAX_HEADLENGTH	128
#endif




