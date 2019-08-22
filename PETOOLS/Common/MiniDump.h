#pragma once
#include<DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")

#ifdef UNICODE
#define TSprintf	wsprintf
#else
#define TSprintf	sprintf
#endif

class CMiniDump
{
public:
	CMiniDump();
	~CMiniDump();
public:
	// 程序崩溃时是否启动自动生成dump文件;
	// 只需要在main函数开始处调用该函数即可;
	static void EnableAutoDump(bool bEnable = true);

private:

	static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException);

	static void CreateDumpFile(LPCTSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException);
};

