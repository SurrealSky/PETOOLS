#include "mem.h"
#include"../MemoryPool/MemoryPool.h"

//Ä¬ÈÏ·ÖÅäº¯Êý
char* WZHMem::StdAlloc(const DWORD dwSize)
{
	return WZHMemManager::CommonAlloc(WZHMemManager::TypeStdAllocTAlloc,dwSize);
}
void WZHMem::StdDeallocate(char *p,const DWORD dwSize)
{
	WZHMemManager::CommonDeallocate(WZHMemManager::TypeStdAllocTAlloc,p,dwSize);
}

char* WZHMem::SGIAlloc(const DWORD dwSize)
{
	return WZHMemManager::CommonAlloc(WZHMemManager::TypeSGIAllocTAlloc,dwSize);
}
void WZHMem::SGIDeallocate(char *p,const DWORD dwSize)
{
	WZHMemManager::CommonDeallocate(WZHMemManager::TypeSGIAllocTAlloc,p,dwSize);
}

char* WZHMem::SGIVirtualAlloc(const DWORD dwSize)
{
	return WZHMemManager::CommonAlloc(WZHMemManager::TypeSGIVirtualAllocTAlloc,dwSize);
}
void WZHMem::SGIVirtualDeallocate(char *p,const DWORD dwSize)
{
	WZHMemManager::CommonDeallocate(WZHMemManager::TypeSGIVirtualAllocTAlloc,p,dwSize);
}

char* WZHMem::SGIHeapAlloc(const DWORD dwSize)
{
	return WZHMemManager::CommonAlloc(WZHMemManager::TypeSGIHeapAllocTAlloc,dwSize);
}
void WZHMem::SGIHeapDeallocate(char *p,const DWORD dwSize)
{
	WZHMemManager::CommonDeallocate(WZHMemManager::TypeSGIHeapAllocTAlloc,p,dwSize);
}

char* WZHMem::SGIMTAlloc(const DWORD dwSize)
{
	return WZHMemManager::CommonAlloc(WZHMemManager::TypeSGIMTAllocatorAlloc,dwSize);
}
void WZHMem::SGIMTDeallocate(char *p,const DWORD dwSize)
{
	WZHMemManager::CommonDeallocate(WZHMemManager::TypeSGIMTAllocatorAlloc,p,dwSize);
}
