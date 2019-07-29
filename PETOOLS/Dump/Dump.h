// Dump.h : Dump DLL 的主头文件
//

#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_API __declspec(dllimport)
#endif

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include "..\Common\dbghelp.h"
#pragma comment(lib, "dbghelp.lib")

// CDumpApp
// 有关此类实现的信息，请参阅 Dump.cpp
//

class DIPPEREXPORTS_API CDumpApp : public CWinApp
{
public:
	CDumpApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
public:
	void CreateMiniDump(EXCEPTION_POINTERS*,LPCSTR);
};

DIPPEREXPORTS_API CDumpApp theDumpApp;
BOOL CALLBACK MiniDumpCallback(PVOID,const PMINIDUMP_CALLBACK_INPUT,PMINIDUMP_CALLBACK_OUTPUT);
BOOL IsDataSectionNeeded(const wchar_t* pModuleName);