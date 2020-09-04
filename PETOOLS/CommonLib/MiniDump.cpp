#include<stdio.h>
#include<Windows.h>
#include "MiniDump.h"


CMiniDump::CMiniDump()
{
}


CMiniDump::~CMiniDump()
{
}

void CMiniDump::EnableAutoDump(STbool bEnable)
{
	if (bEnable)
	{
		SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
	}
}

LONG CMiniDump::ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	/*if (IsDebuggerPresent())
	{
	return EXCEPTION_CONTINUE_SEARCH;
	}*/

	STu8 szDumpDir[MAX_PATH] = { 0 };
	STu8 szDumpFile[MAX_PATH] = { 0 };
	STu8 szMsg[MAX_PATH] = { 0 };
	SYSTEMTIME	stTime = { 0 };
	// ����dump�ļ�·��;
	GetLocalTime(&stTime);
	::GetCurrentDirectory(MAX_PATH, (char*)szDumpDir);
	TSprintf((char*)szDumpFile,
		"%s\\%04d%02d%02d_%02d%02d%02d.dmp", szDumpDir,
		stTime.wYear, stTime.wMonth, stTime.wDay,
		stTime.wHour, stTime.wMinute, stTime.wSecond);
	// ����dump�ļ�;
	CreateDumpFile((char*)szDumpFile, pException);

	// ����һ������Ի��������ʾ�ϴ��� ���˳�����;
	TSprintf((char*)szMsg, "I'm so sorry, but the program crashed.\r\ndump file : %s", szDumpFile);
	FatalAppExit(-1, (char*)szMsg);

	return EXCEPTION_EXECUTE_HANDLER;
}

void CMiniDump::CreateDumpFile(LPCTSTR strPath, EXCEPTION_POINTERS *pException)
{
	// ����Dump�ļ�;
	HANDLE hDumpFile = CreateFile(strPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Dump��Ϣ;
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;

	// д��Dump�ļ�����;
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
	CloseHandle(hDumpFile);
}