#include"HelpFunc.h"


LONG WINAPI HelpFunc::GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	//写共享内存
	HANDLE hMapFile=CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,1024,"Surreal");
	if(hMapFile)
	{
		LPWSTR lpMapAddr=(LPWSTR)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,0);
		memcpy_s(lpMapAddr,1024,(LPWSTR)pExceptionInfo,sizeof(EXCEPTION_POINTERS));
		FlushViewOfFile(lpMapAddr,0);
		OutputDebugString("共享内存写入完毕");
	}else
	{
		return EXCEPTION_EXECUTE_HANDLER;
		OutputDebugString("共享内存写入失败");
	}


	ResumeThread(::g_DumpThread);
	WaitForSingleObject(::g_DumpThread,INFINITE);
	return EXCEPTION_EXECUTE_HANDLER;  // 程序停止运行

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
		OutputDebugString("共享内存读取成功");
	}else
	{
		OutputDebugString("共享内存读取失败");
		return FALSE;
	}
	OutputDebugString("开始生成转储文件");

	theDumpApp.CreateMiniDump(&ExceptionInfo,"Exception.dmp");
	MessageBox(NULL,"程序发生崩溃","警告",MB_OK|MB_ICONERROR);
	exit(ExceptionInfo.ExceptionRecord->ExceptionCode);
	return TRUE;
}
