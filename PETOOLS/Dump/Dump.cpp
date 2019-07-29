// Dump.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Dump.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CDumpApp

BEGIN_MESSAGE_MAP(CDumpApp, CWinApp)
END_MESSAGE_MAP()


// CDumpApp 构造

CDumpApp::CDumpApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// CDumpApp 初始化

BOOL CDumpApp::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}



void CDumpApp::CreateMiniDump(EXCEPTION_POINTERS* pep, LPCSTR strFileName)
{
	HANDLE hFile = CreateFile(strFileName,GENERIC_READ | GENERIC_WRITE,0,
		NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
  {
     MINIDUMP_EXCEPTION_INFORMATION mdei;
     mdei.ThreadId           = GetCurrentThreadId();
     mdei.ExceptionPointers  = pep;
     mdei.ClientPointers     = FALSE;
     MINIDUMP_CALLBACK_INFORMATION mci;
     mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
     mci.CallbackParam       = 0;
     MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)(MiniDumpWithPrivateReadWriteMemory | 
         MiniDumpWithDataSegs | 
         MiniDumpWithHandleData |
         0x00000800 /*MiniDumpWithFullMemoryInfo*/ | 
         0x00001000 /*MiniDumpWithThreadInfo*/ | 
         MiniDumpWithUnloadedModules);
     MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
         hFile, mdt, (pep != 0) ? &mdei : 0, 0, &mci);
     CloseHandle(hFile); 
	 OutputDebugString("转储文件写入完毕");
  }
}


BOOL CALLBACK MiniDumpCallback(PVOID pParam,const PMINIDUMP_CALLBACK_INPUT pInput,PMINIDUMP_CALLBACK_OUTPUT pOutput)
{
  if(pInput == 0 || pOutput == 0)
     return FALSE;
  switch(pInput->CallbackType)
  {
	  case ModuleCallback: 
		 if(pOutput->ModuleWriteFlags & ModuleWriteDataSeg) 
			 if(!IsDataSectionNeeded(pInput->Module.FullPath)) 
				pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg); 
	  case IncludeModuleCallback:
	  case IncludeThreadCallback:
	  case ThreadCallback:
	  case ThreadExCallback:
		return TRUE;
	  default:;
  }
  return FALSE;
}

BOOL IsDataSectionNeeded(const wchar_t* pModuleName)
{
  if(pModuleName == 0)
  {
     return FALSE;
  }
  WCHAR szFileName[_MAX_FNAME] = L"";
  _wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);
  if(wcsicmp(szFileName, L"ntdll") == 0)
     return TRUE;
  return FALSE; 
}




