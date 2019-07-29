#include"stdafx.h"
#include "OtherMempryPool.h"
#include "Pool.h"
#include "MemoryPool.h"
#include"MemManager.h"

/*
DIPPEREXPORTS_API char* StdAllocTAlloc(const DWORD dwSize)
{
	return MemManager::CommonAlloc(TypeStdAllocTAlloc,dwSize);
}
DIPPEREXPORTS_API void StdAllocTDeallocate(char *p,const DWORD dwSize)
{
	MemManager::CommonDeallocate(TypeStdAllocTAlloc,p,dwSize);
}

DIPPEREXPORTS_API char* SGIAllocTAlloc(const DWORD dwSize)
{
	return MemManager::CommonAlloc(TypeSGIAllocTAlloc,dwSize);
}
DIPPEREXPORTS_API void SGIAllocTDeallocate(char *p,const DWORD dwSize)
{
	MemManager::CommonDeallocate(TypeSGIAllocTAlloc,p,dwSize);
}

DIPPEREXPORTS_API char* SGIVirtualAllocTAlloc(const DWORD dwSize)
{
	return MemManager::CommonAlloc(TypeSGIVirtualAllocTAlloc,dwSize);
}
DIPPEREXPORTS_API void SGIVirtualAllocTDeallocate(char *p,const DWORD dwSize)
{
	MemManager::CommonDeallocate(TypeSGIVirtualAllocTAlloc,p,dwSize);
}

DIPPEREXPORTS_API char* SGIHeapAllocTAlloc(const DWORD dwSize)
{
	return MemManager::CommonAlloc(TypeSGIHeapAllocTAlloc,dwSize);
}
DIPPEREXPORTS_API void SGIHeapAllocTDeallocate(char *p,const DWORD dwSize)
{
	MemManager::CommonDeallocate(TypeSGIHeapAllocTAlloc,p,dwSize);
}

DIPPEREXPORTS_API char* SGIMTAllocatorAlloc(const DWORD dwSize)
{
	return MemManager::CommonAlloc(TypeSGIMTAllocatorAlloc,dwSize);
}
DIPPEREXPORTS_API void SGIMTAllocatorDeallocate(char *p,const DWORD dwSize)
{
	MemManager::CommonDeallocate(TypeSGIMTAllocatorAlloc,p,dwSize);
}
*/

char* WZHMemManager::CommonAlloc(const MemAllocType _type,const DWORD dwSize)
{
	return MemManager::CommonAlloc(_type,dwSize);
}
void WZHMemManager::CommonDeallocate(const MemAllocType _type,char *p,const DWORD dwSize)
{
	return MemManager::CommonDeallocate(_type,p,dwSize);
}