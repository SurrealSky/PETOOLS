// Synchro.h : Synchro DLL ����ͷ�ļ�
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
#include"pack.h"


// CSynchroApp
// �йش���ʵ�ֵ���Ϣ������� Synchro.cpp
//

class DIPPEREXPORTS_API CSynchroApp
{
public:
	CSynchroApp();
public:
	bool SynchroEventWorkThread(int);
	bool SynchroEventUiThread(PBPack*);
	bool ReleaseSynchroEvent();
};
