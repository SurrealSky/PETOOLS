#pragma once
#include<Windows.h>

namespace WZHMem
{
	//Ä¬ÈÏ·ÖÅäº¯Êý
	char* StdAlloc(const DWORD dwSize);
	void StdDeallocate(char *p,const DWORD dwSize=0);

	char* SGIAlloc(const DWORD dwSize);
	void SGIDeallocate(char *p,const DWORD dwSize=0);

	char* SGIVirtualAlloc(const DWORD dwSize);
	void SGIVirtualDeallocate(char *p,const DWORD dwSize=0);

	char* SGIHeapAlloc(const DWORD dwSize);
	void SGIHeapDeallocate(char *p,const DWORD dwSize=0);

	char* SGIMTAlloc(const DWORD dwSize);
	void SGIMTDeallocate(char *p,const DWORD dwSize=0);
}