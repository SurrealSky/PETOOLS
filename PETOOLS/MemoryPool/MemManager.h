#pragma once
#include "OtherMempryPool.h"
#include "Pool.h"
#include "MemoryPool.h"

const DWORD dwCount = 10000;
const DWORD dwSize = 40960000;

typedef std::allocator<char>	StdAllocT;

// SGIMemoryPool,���̲߳����� malloc�������
typedef Allocator<char, SGIMemoryPool<false, dwSize> > SGIAllocT;

// SGIMemoryPool,���̲߳����� VirtualAlloc�������
typedef Allocator<char, SGIMemoryPool<false, dwSize, VirtualAllocateTraits>> SGIVirtualAllocT;

// SGIMemoryPool,���̲߳����� HeapAllocС��Ƭ�ѷ������
typedef Allocator<char, SGIMemoryPool<false, dwSize, HeapAllocateTraits>> SGIHeapAllocT;

// SGIMemoryPool�����̼߳����� malloc�������
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
	//�洢���ڴ��ַ-�ڴ��С��
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