#include"HelpFunc.h"


LONG WINAPI HelpFunc::GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	//д�����ڴ�
	HANDLE hMapFile=CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,1024,"Surreal");
	if(hMapFile)
	{
		LPWSTR lpMapAddr=(LPWSTR)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,0);
		memcpy_s(lpMapAddr,1024,(LPWSTR)pExceptionInfo,sizeof(EXCEPTION_POINTERS));
		FlushViewOfFile(lpMapAddr,0);
		OutputDebugString("�����ڴ�д�����");
	}else
	{
		return EXCEPTION_EXECUTE_HANDLER;
		OutputDebugString("�����ڴ�д��ʧ��");
	}


	ResumeThread(::g_DumpThread);
	WaitForSingleObject(::g_DumpThread,INFINITE);
	return EXCEPTION_EXECUTE_HANDLER;  // ����ֹͣ����

}

DWORD WINAPI HelpFunc::ThreadProc( LPVOID lpParam )
{
	EXCEPTION_POINTERS ExceptionInfo;
	HANDLE hMapFile=OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE,"Surreal");

	if(hMapFile)
	{
		LPWSTR lpMapAddr = (LPWSTR)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,0); 
		memcpy_s(&ExceptionInfo,sizeof(EXCEPTION_POINTERS),lpMapAddr,sizeof(EXCEPTION_POINTERS));
		FlushViewOfFile(lpMapAddr,0);  
		UnmapViewOfFile(lpMapAddr);
		CloseHandle(hMapFile);
		OutputDebugString("�����ڴ��ȡ�ɹ�");
	}else
	{
		OutputDebugString("�����ڴ��ȡʧ��");
		return FALSE;
	}
	OutputDebugString("��ʼ����ת���ļ�");

	theDumpApp.CreateMiniDump(&ExceptionInfo,"Exception.dmp");
	MessageBox(NULL,"����������","����",MB_OK|MB_ICONERROR);
	exit(ExceptionInfo.ExceptionRecord->ExceptionCode);
	return TRUE;
}
