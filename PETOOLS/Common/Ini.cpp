#include "StdAfx.h"
#include "Ini.h"


Ini::Ini(void)
{
	ZeroMemory(this->PATH,sizeof(this->PATH));
}

TCHAR* Ini::GetPath(void)
{
	return this->PATH;
}

int Ini::GetIntKey(IN TCHAR *File,IN TCHAR *section,IN TCHAR *key)
{
	::GetModuleFileName(NULL,this->GetPath(),MAX_PATH);
	*(_tcsrchr(this->GetPath(),'\\')+1)=0x00;
	_tcscat(this->GetPath(),File);
	return ::GetPrivateProfileInt(section,key,0,this->GetPath());
	
}

 void Ini::GetStrKey(IN TCHAR *File,IN TCHAR *section,IN TCHAR *key,OUT TCHAR *pOutBuffer)
{
	::GetModuleFileName(NULL,this->GetPath(),MAX_PATH);
	*(_tcsrchr(this->GetPath(),'\\')+1)=0x00;
	_tcscat(this->GetPath(),File);
	GetPrivateProfileString(section,key,0,pOutBuffer,MAX_PATH,this->GetPath());
}

Ini::~Ini(void)
{
}


