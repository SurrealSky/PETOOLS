// Synchro.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Synchro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSynchroApp ����

CSynchroApp::CSynchroApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

bool CSynchroApp::SynchroEventWorkThread(int value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString str;
	if(!str.LoadStringW(AfxGetInstanceHandle(),IDS_PBEVENT))
		return FALSE;

	HANDLE hEvent=OpenEvent(EVENT_ALL_ACCESS,FALSE,str);
	if(hEvent)
	{
		OutputDebugString(L"�򿪹���д������");
		//�Ѿ�����
		str.Empty();
		if(!str.LoadStringW(AfxGetInstanceHandle(),IDS_PBMEMORY))
		{
			CloseHandle(hEvent);
			return FALSE;
		}
		HANDLE hFileMapping=OpenFileMapping(PAGE_READWRITE,FALSE,str);
		if(!hFileMapping) 
		{
			CloseHandle(hEvent);
			return FALSE;
		}
		PVOID pView=MapViewOfFile(hFileMapping,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
		ZeroMemory(pView,sizeof(PBPack));
		PBPack p={0};
		(p.value=value)==100?p.isFinish=TRUE:p.isFinish=FALSE;
		memcpy_s(pView,sizeof(PBPack),&p,sizeof(PBPack));
		FlushViewOfFile(pView,0);
		//UnmapViewOfFile(pView);
		//CloseHandle(hFileMapping);
		//CloseHandle(hEvent);
	}else
	{
		if(value!=0)
			return FALSE;
		OutputDebugString(L"��������");
		hEvent=CreateEvent(NULL,FALSE,FALSE,str); //�Զ����ö���

		str.Empty();
		if(!str.LoadStringW(AfxGetInstanceHandle(),IDS_PBMEMORY))
		{
			CloseHandle(hEvent);
			return FALSE;
		}
		HANDLE hFileMapping=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(PBPack),str);
		if(!hFileMapping) 
		{
			CloseHandle(hEvent);
			return FALSE;
		}
		PVOID pView=MapViewOfFile(hFileMapping,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
		ZeroMemory(pView,sizeof(PBPack));
		PBPack p={0};
		memcpy_s(pView,sizeof(PBPack),&p,sizeof(PBPack));
		//UnmapViewOfFile(pView);
		//CloseHandle(hFileMapping);
		//CloseHandle(hEvent);
	}
	SetEvent(hEvent);  //���Զ������¼���������
	return TRUE;
}

bool CSynchroApp::SynchroEventUiThread(PBPack *pPBPack)
{
	OutputDebugString(L"ȡ������");
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString str;
	if(!str.LoadStringW(AfxGetInstanceHandle(),IDS_PBEVENT))
		return FALSE;
	HANDLE hEvent=OpenEvent(EVENT_ALL_ACCESS,FALSE,str);
	WaitForSingleObject(hEvent,INFINITE);

	str.Empty();
	if(!str.LoadStringW(AfxGetInstanceHandle(),IDS_PBMEMORY))
	{
		CloseHandle(hEvent);
		return FALSE;
	}
	HANDLE hFileMapping=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(PBPack),str);
	if(!hFileMapping) 
	{
		CloseHandle(hEvent);
		return FALSE;
	}
	PVOID pView=MapViewOfFile(hFileMapping,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	memcpy_s(pPBPack,sizeof(PBPack),pView,sizeof(PBPack));
	return TRUE;
}

bool CSynchroApp::ReleaseSynchroEvent()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString str;
	if(!str.LoadStringW(AfxGetInstanceHandle(),IDS_PBEVENT))
		return FALSE;
	HANDLE hEvent=OpenEvent(EVENT_ALL_ACCESS,FALSE,str);
	if(hEvent)
	{
		str.Empty();
		if(!str.LoadStringW(AfxGetInstanceHandle(),IDS_PBMEMORY))
		{
			CloseHandle(hEvent);
			return FALSE;
		}
		HANDLE hFileMapping=OpenFileMapping(PAGE_READWRITE,FALSE,str);
		if(!hFileMapping) 
		{
			CloseHandle(hEvent);
			return FALSE;
		}
		PVOID pView=MapViewOfFile(hFileMapping,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);

		UnmapViewOfFile(pView);
		CloseHandle(hFileMapping);
		CloseHandle(hEvent);
	}
	return FALSE;
}
