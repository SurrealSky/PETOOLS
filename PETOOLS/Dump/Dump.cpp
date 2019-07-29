// Dump.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Dump.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CDumpApp

BEGIN_MESSAGE_MAP(CDumpApp, CWinApp)
END_MESSAGE_MAP()


// CDumpApp ����

CDumpApp::CDumpApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// CDumpApp ��ʼ��

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
	 OutputDebugString("ת���ļ�д�����");
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




