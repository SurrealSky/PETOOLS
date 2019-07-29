// ProBarThread.cpp : 实现文件
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "ProBarThread.h"
#include"ProgressDialog.h"
#include"GlobeVar.h"
#include<Windows.h>

//globe var
volatile BOOL gWait=FALSE;

CProgressDialog *ProDialog;

// CProBarThread

IMPLEMENT_DYNCREATE(CProBarThread, CWinThread)

CProBarThread::CProBarThread()
{
}

CProBarThread::~CProBarThread()
{
}
//包含创建线程之外的工作
void CProBarThread::Create()
{
	this->CreateThread();

	ProDialog=new CProgressDialog();
	ProDialog->Create(IDD_PROGRESS);

	int cx = GetSystemMetrics(SM_CXFULLSCREEN); 
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	RECT rect={0};
	ProDialog->GetWindowRect(&rect);
	ProDialog->MoveWindow((cx-rect.right+rect.left)/2,(cy-rect.bottom+rect.top)/2,rect.right-rect.left,rect.bottom-rect.top,TRUE);
	ProDialog->ShowWindow(TRUE);
	//ProDialog->GetParent()->EnableWindow(FALSE);

	/*while(InterlockedExchange((long*)&gWait,(long)TRUE)==TRUE)     //主要用于等待工作线程准备完毕
	{
		Sleep(0);
	}
	*/
}
/*
*等待相应线程，进度条走完结束
*/
void ThreadProc( LPVOID lpParam )
{/*
	InterlockedExchange((long*)&gWait,(long)FALSE);

	int value=0;
	PBPack model={0};
	CSynchroApp CSyn;
	while(TRUE)
	{
		
		CSyn.SynchroEventUiThread(&model);
		if(model.isFinish) break;
		
		while(TRUE)
		{
			if(ProDialog.m_ProCtrl) 
				Sleep(0);
			else
			{
				ProDialog.m_ProCtrl.SetPos(model.value);
				break;
			}
		}
	}
	//释放资源
	CSyn.ReleaseSynchroEvent();
	ProDialog.EndDialog(TRUE);
	*/
}
/*
*创建模态对话框线程
*/
void ThreadProc1(LPVOID lpParam)
{
	CProgressDialog *ProDialog=new CProgressDialog();
	ProDialog->Create(IDD_PROGRESS);


	int cx = GetSystemMetrics(SM_CXFULLSCREEN); 
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	RECT rect={0};
	ProDialog->GetWindowRect(&rect);

	ProDialog->MoveWindow((cx-rect.right+rect.left)/2,(cx-rect.bottom+rect.top)/2,rect.right-rect.left,rect.bottom-rect.top,TRUE);

	ProDialog->ShowWindow(TRUE);
}


void CProBarThread::SetProValue(int value)
{
	if(ProDialog!=NULL)
	{
		ProDialog->m_ProCtrl.SetPos(value);
		Sleep(100);
		
		if(value==100)
		{
			this->ExitInstance();
		}
	}
}

BOOL CProBarThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化

	//CProBarThread::SetProValue(0);

	//HANDLE hNew=(HANDLE)_beginthread(ThreadProc,NULL,NULL);
	
	//WaitForSingleObject(hNew,INFINITE);


	//HANDLE hOld=(HANDLE)_beginthread(ThreadProc1,NULL,NULL);

	//WaitForSingleObject(hOld,INFINITE);        //直到进度条终止


	return TRUE;
}

int CProBarThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	//ProDialog->GetParent()->EnableWindow(TRUE);
	ProDialog->DestroyWindow();
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CProBarThread, CWinThread)
	ON_THREAD_MESSAGE(PB_SETVALUE, &CProBarThread::OnSetValue)
END_MESSAGE_MAP()


// CProBarThread 消息处理程序


void AFX_MSG_CALL CProBarThread::OnSetValue(WPARAM wParam, LPARAM lParam)
{
	//if(ProDialog!=NULL)
	//{
	//	ProDialog->m_ProCtrl.SetPos(lParam);
	//	if(lParam==100)
	//	{
	//		this->ExitInstance();
	//		delete this;
	//	}
	//}
	
}
