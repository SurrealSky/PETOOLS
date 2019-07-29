//此处用于定义全局的宏定义
#pragma once
#include<Windows.h>
#include"..\MemoryPool\MemoryPool.h"
#include"../PELib/PE/PEMake.h"


#pragma comment(lib,"MemoryPool.lib")
#pragma comment(lib,"PELib.lib")

#ifdef UNICODE
#define MAX_LENGTH 128
#define MAX_FUNLENGTH  128
#define MAX_HEADLENGTH	128
#else
#define MAX_LENGTH 128
#define MAX_FUNLENGTH  128
#define MAX_HEADLENGTH	128
#endif




