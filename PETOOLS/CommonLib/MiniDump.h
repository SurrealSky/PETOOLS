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
	// �������ʱ�Ƿ������Զ�����dump�ļ�;
	// ֻ��Ҫ��main������ʼ�����øú�������;
	static void EnableAutoDump(STbool bEnable = TRUE);

private:

	static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException);

	static void CreateDumpFile(LPCTSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException);
};

