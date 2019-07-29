#pragma once
#include "stdafx.h"
#include <Windows.h>
#include "GlobeVar.h"

extern HANDLE g_DumpThread;


class HelpFunc
{
public:
	HelpFunc(void) {};
	~HelpFunc(void) {};
public:
	static LONG WINAPI GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo);
	static DWORD WINAPI ThreadProc( LPVOID lpParam );
};