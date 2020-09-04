//此处用于定义全局的宏定义
#pragma once
#include<Windows.h>
#include<typedef.h>
#include"../PELib/PE/PEMake.h"
#pragma comment(lib,"PELib.lib")

#include"../MemoryPool/MemMgr.h"
using namespace SurrealMemMgr;

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MemMgr.lib")
#else
#pragma comment(lib, "..\\Release\\MemMgr.lib")
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




