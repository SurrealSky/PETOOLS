#include "StdAfx.h"
#include "LOG.h"


LOG::LOG(void)
{
	ZeroMemory(this->GetPath(),MAX_PATH);
	ZeroMemory(this->GetTemp(),MAX_PATH);

	::GetModuleFileName(NULL,this->GetPath(),MAX_PATH);
	*(_tcsrchr(this->GetPath(),'\\')+1)=0x00;

	memcpy(this->GetTemp(),this->GetPath(),MAX_PATH);
	_tcscat_s(this->GetTemp(),MAX_PATH,"LOG");
	if(GetFileAttributes(this->GetTemp())!=FILE_ATTRIBUTE_DIRECTORY)
	{
		OutputDebugString("������־Ŀ¼");
		if(!CreateDirectory(this->GetTemp(),NULL))
		{
			OutputDebugString("������־Ŀ¼ʧ��");
			return;
		}
	}
}

BOOL LOG::LogControl(TCHAR *pMsg)
{
	TCHAR buffer[MAX_PATH]={0};

	ZeroMemory(this->GetTemp(),MAX_PATH);
	memcpy_s(this->GetTemp(),MAX_PATH,this->GetPath(),MAX_PATH);
	_tcscat_s(this->GetTemp(),MAX_PATH,"LOG\\MainLog.txt");
	//���ɵ�ǰ��ʱ��
	SetLastError(ERROR_SUCCESS);
	HANDLE hFile=CreateFile(this->GetTemp(),GENERIC_WRITE|GENERIC_READ,NULL,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	SYSTEMTIME st;
	GetLocalTime(&st);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		OutputDebugString("��־�ļ�����ʧ��");
		return FALSE;
	}

	ZeroMemory(buffer,sizeof(buffer));

	if(GetLastError()==ERROR_SUCCESS)
	{
		//sprintf(buffer,"%c%d-%02d-%02d %02d:%02d:%02d  %s",0xfeff,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,pMsg);
		sprintf(buffer,"%c%s",0xfeff,pMsg);
	}else
	{
		//sprintf(buffer,"\r\n%d-%02d-%02d %02d:%02d:%02d  %s",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,pMsg);
		sprintf(buffer,"\r\n%s",pMsg);
	}
	
	DWORD WriteNum=0;
	if(SetFilePointer(hFile,0,NULL,FILE_END)==0xFFFFFFFF)
	{
		OutputDebugString("�ļ�����");
		return FALSE;
	}

	if(!WriteFile(hFile,buffer,_tcslen(buffer)*(2),&WriteNum,NULL))
	{
		OutputDebugString("��־�ļ�дʧ��");
		return FALSE;
	}
	CloseHandle(hFile);
	return TRUE;
}

LOG::~LOG(void)
{
}
