#pragma once
#include "OtherMempryPool.h"
#include "Pool.h"
#include "MemoryPool.h"

const DWORD dwCount = 10000;
const DWORD dwSize = 40960000;

typedef std::allocator<char>	StdAllocT;

// SGIMemoryPool,单线程不加锁 malloc分配策略
typedef Allocator<char, SGIMemoryPool<false, dwSize> > SGIAllocT;

// SGIMemoryPool,单线程不加锁 VirtualAlloc分配策略
typedef Allocator<char, SGIMemoryPool<false, dwSize, VirtualAllocateTraits>> SGIVirtualAllocT;

// SGIMemoryPool,单线程不加锁 HeapAlloc小碎片堆分配策略
typedef Allocator<char, SGIMemoryPool<false, dwSize, HeapAllocateTraits>> SGIHeapAllocT;

// SGIMemoryPool，多线程枷锁， malloc分配策略
typedef Allocator<char, SGIMemoryPool<true, dwSize> > SGIMTAllocator;


class MemManager
{
public:
	MemManager(void);
	virtual ~MemManager(void);
private:
	static StdAllocT alloc1;
	static SGIAllocT alloc2;
	static SGIVirtualAllocT alloc3;
	static SGIHeapAllocT alloc4;
	static SGIMTAllocator alloc5;
	//存储（内存地址-内存大小）
	static std::map<void*,unsigned int> StdAllocTList;
	static std::map<void*,unsigned int> SGIAllocTList;
	static std::map<void*,unsigned int> SGIVirtualAllocTList;
	static std::map<void*,unsigned int> SGIHeapAllocTList;
	static std::map<void*,unsigned int> SGIMTAllocatorList;
private:
	static char* StdAllocTAlloc(const DWORD dwSize);
	static void StdAllocTDeallocate(char *p,const DWORD dwSize);
	static char* SGIAllocTAlloc(const DWORD dwSize);
	static void SGIAllocTDeallocate(char *p,const DWORD dwSize);
	static char* SGIVirtualAllocTAlloc(const DWORD dwSize);
	static void SGIVirtualAllocTDeallocate(char *p,const DWORD dwSize);
	static char* SGIHeapAllocTAlloc(const DWORD dwSize);
	static void SGIHeapAllocTDeallocate(char *p,const DWORD dwSize);
	static char* MemManager::SGIMTAllocatorAlloc(const DWORD dwSize);
	static void MemManager::SGIMTAllocatorDeallocate(char *p,const DWORD dwSize);
public:
	static char* CommonAlloc(const WZHMemManager::MemAllocType,const DWORD dwSize);
	static void CommonDeallocate(const WZHMemManager::MemAllocType,char *p,const DWORD dwSize=0);
};