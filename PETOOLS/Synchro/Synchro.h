// Synchro.h : Synchro DLL 的主头文件
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
#include"pack.h"


// CSynchroApp
// 有关此类实现的信息，请参阅 Synchro.cpp
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
