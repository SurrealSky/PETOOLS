// Dump.h : Dump DLL ����ͷ�ļ�
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
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "..\Common\dbghelp.h"
#pragma comment(lib, "dbghelp.lib")

// CDumpApp
// �йش���ʵ�ֵ���Ϣ������� Dump.cpp
//

class DIPPEREXPORTS_API CDumpApp : public CWinApp
{
public:
	CDumpApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
public:
	void CreateMiniDump(EXCEPTION_POINTERS*,LPCSTR);
};

DIPPEREXPORTS_API CDumpApp theDumpApp;
BOOL CALLBACK MiniDumpCallback(PVOID,const PMINIDUMP_CALLBACK_INPUT,PMINIDUMP_CALLBACK_OUTPUT);
BOOL IsDataSectionNeeded(const wchar_t* pModuleName);