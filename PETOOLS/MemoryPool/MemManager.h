#pragma once
#include "OtherMempryPool.h"
#include "Pool.h"
#include "MemMgr.h"
using namespace SurrealMemMgr;

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


class MemMgr::MemManager
{
public:
	MemManager(void);
	MemManager(const MemManager&);
	virtual ~MemManager(void);
private:
	StdAllocT alloc1;
	SGIAllocT alloc2;
	SGIVirtualAllocT alloc3;
	SGIHeapAllocT alloc4;
	SGIMTAllocator alloc5;
private:
	//存储（内存地址-内存大小）
	std::map<void*,unsigned int> StdAllocTList;
	std::map<void*,unsigned int> SGIAllocTList;
	std::map<void*,unsigned int> SGIVirtualAllocTList;
	std::map<void*,unsigned int> SGIHeapAllocTList;
	std::map<void*,unsigned int> SGIMTAllocatorList;
private:
	char* StdAllocTAlloc(const DWORD dwSize);
	void StdAllocTDeallocate(char *p,const DWORD dwSize);
	char* SGIAllocTAlloc(const DWORD dwSize);
	void SGIAllocTDeallocate(char *p,const DWORD dwSize);
	char* SGIVirtualAllocTAlloc(const DWORD dwSize);
	void SGIVirtualAllocTDeallocate(char *p,const DWORD dwSize);
	char* SGIHeapAllocTAlloc(const DWORD dwSize);
	void SGIHeapAllocTDeallocate(char *p,const DWORD dwSize);
	char* SGIMTAllocatorAlloc(const DWORD dwSize);
	void SGIMTAllocatorDeallocate(char *p,const DWORD dwSize);
public:
	char* CommonAlloc(const SurrealMemMgr::MemAllocType,const DWORD dwSize);
	void CommonDeallocate(const SurrealMemMgr::MemAllocType,char *p,const DWORD dwSize=0);
};