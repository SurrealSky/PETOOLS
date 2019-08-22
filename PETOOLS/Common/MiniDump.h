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
	// �������ʱ�Ƿ������Զ�����dump�ļ�;
	// ֻ��Ҫ��main������ʼ�����øú�������;
	static void EnableAutoDump(bool bEnable = true);

private:

	static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException);

	static void CreateDumpFile(LPCTSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException);
};

