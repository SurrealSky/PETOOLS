#pragma once
#include<typedef.h>
using namespace SurrealTypes;
#include<DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")

#define TSprintf	sprintf

class CMiniDump
{
public:
	CMiniDump();
	~CMiniDump();
public:
	// 程序崩溃时是否启动自动生成dump文件;
	// 只需要在main函数开始处调用该函数即可;
	static void EnableAutoDump(STbool bEnable = TRUE);

private:

	static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException);

	static void CreateDumpFile(LPCTSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException);
};

