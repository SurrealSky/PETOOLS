#pragma once
#include<Windows.h>
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_API __declspec(dllimport)
#endif

namespace WZHMemManager
{

	//内存分配类型
	enum MemAllocType
	{
		TypeStdAllocTAlloc,
		TypeSGIAllocTAlloc,
		TypeSGIVirtualAllocTAlloc,
		TypeSGIHeapAllocTAlloc,
		TypeSGIMTAllocatorAlloc
	};

	DIPPEREXPORTS_API char* CommonAlloc(const MemAllocType,const DWORD dwSize);
	DIPPEREXPORTS_API void CommonDeallocate(const MemAllocType,char *p,const DWORD dwSize=0);

}
