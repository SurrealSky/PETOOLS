
// PEMake.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPEMakeApp:
// �йش����ʵ�֣������ PEMake.cpp
//

class CPEMakeApp : public CWinApp
{
public:
	CPEMakeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPEMakeApp theApp;