#include "StdAfx.h"
#include "MemManager.h"
#include<LogLib\DebugLog.h>

MemMgr::MemManager::MemManager(void)
{
	StdAllocTList.clear();
	SGIAllocTList.clear();
	SGIVirtualAllocTList.clear();
	SGIHeapAllocTList.clear();
	SGIMTAllocatorList.clear();
}

MemMgr::MemManager::MemManager(const MemManager &m)
{

}

MemMgr::MemManager::~MemManager(void)
{
	//清除内存
	SurrealDebugLog::DebugLog("MemManager","start free all alloc...");
	map<void*, unsigned int>::iterator it;
	if(MemManager::StdAllocTList.size()>0)
	{
		for(it=MemManager::StdAllocTList.begin();it!=MemManager::StdAllocTList.end();++it)
		{
			alloc1.deallocate((char*)it->first,it->second);
			SurrealDebugLog::DebugLog(SurrealDebugLog::string_format("%s:MemType=%02X,address=0x%08X,size=%X free!", "MemManager", TypeStdAllocTAlloc, it->first, it->second));
		}
	}
	MemManager::StdAllocTList.clear();

	if(SGIAllocTList.size()>0)
	{
		for(it=MemManager::SGIAllocTList.begin();it!=MemManager::SGIAllocTList.end();++it)
		{
			alloc2.Deallocate((char*)it->first,it->second);
			SurrealDebugLog::DebugLog(SurrealDebugLog::string_format("%s:MemType=%02X,address=0x%08X,size=%X free!", "MemManager", TypeSGIAllocTAlloc, it->first, it->second));
		}
	}
	MemManager::SGIAllocTList.clear();

	if(MemManager::SGIVirtualAllocTList.size()>0)
	{
		for(it=MemManager::SGIVirtualAllocTList.begin();it!=MemManager::SGIVirtualAllocTList.end();++it)
		{
			alloc3.Deallocate((char*)it->first,it->second);
			SurrealDebugLog::DebugLog(SurrealDebugLog::string_format("%s:MemType=%02X,address=0x%08X,size=%X free!", "MemManager", TypeSGIVirtualAllocTAlloc, it->first, it->second));
		}
	}
	MemManager::SGIVirtualAllocTList.clear();

	if(MemManager::SGIHeapAllocTList.size()>0)
	{
		for(it=MemManager::SGIHeapAllocTList.begin();it!=MemManager::SGIHeapAllocTList.end();++it)
		{
			alloc4.Deallocate((char*)it->first,it->second);
			SurrealDebugLog::DebugLog(SurrealDebugLog::string_format("%s:MemType=%02X,address=0x%08X,size=%X free!", "MemManager", TypeSGIHeapAllocTAlloc, it->first, it->second));
		}
	}
	MemManager::SGIHeapAllocTList.clear();

	if(MemManager::SGIMTAllocatorList.size()>0)
	{
		for(it=MemManager::SGIMTAllocatorList.begin();it!=MemManager::SGIMTAllocatorList.end();++it)
		{
			alloc5.Deallocate((char*)it->first,it->second);
			SurrealDebugLog::DebugLog(SurrealDebugLog::string_format("%s:MemType=%02X,address=0x%08X,size=%X free!", "MemManager", TypeSGIMTAllocatorAlloc, it->first, it->second));
		}
	}
	MemManager::SGIMTAllocatorList.clear();
}


char* MemMgr::MemManager::StdAllocTAlloc(const DWORD dwSize)
{
	char *_ptr=alloc1.allocate(dwSize);
	StdAllocTList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}

void MemMgr::MemManager::StdAllocTDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =StdAllocTList.find(p);
		if (it!=StdAllocTList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc1.deallocate(p,dwSize);
			StdAllocTList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemMgr::MemManager::SGIAllocTAlloc(const DWORD dwSize)
{
	char *_ptr=alloc2.Allocate(dwSize);
	SGIAllocTList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}

void MemMgr::MemManager::SGIAllocTDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =SGIAllocTList.find(p);
		if (it!=SGIAllocTList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc2.Deallocate(p,dwSize);
			SGIAllocTList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemMgr::MemManager::SGIVirtualAllocTAlloc(const DWORD dwSize)
{
	char *_ptr=alloc3.Allocate(dwSize);
	SGIVirtualAllocTList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}

void MemMgr::MemManager::SGIVirtualAllocTDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =SGIVirtualAllocTList.find(p);
		if (it!=SGIVirtualAllocTList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc3.Deallocate(p,dwSize);
			SGIVirtualAllocTList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemMgr::MemManager::SGIHeapAllocTAlloc(const DWORD dwSize)
{
	char *_ptr=alloc4.Allocate(dwSize);
	SGIHeapAllocTList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}

void MemMgr::MemManager::SGIHeapAllocTDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =SGIHeapAllocTList.find(p);
		if (it!=SGIHeapAllocTList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc4.Deallocate(p,dwSize);
			SGIHeapAllocTList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemMgr::MemManager::SGIMTAllocatorAlloc(const DWORD dwSize)
{
	char *_ptr=alloc5.Allocate(dwSize);
	SGIMTAllocatorList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}

void MemMgr::MemManager::SGIMTAllocatorDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =MemManager::SGIMTAllocatorList.find(p);
		if (it!=SGIMTAllocatorList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc5.Deallocate(p,dwSize);
			SGIMTAllocatorList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemMgr::MemManager::CommonAlloc(const MemAllocType _type,const DWORD dwSize)
{
	switch(_type)
	{
	case TypeStdAllocTAlloc:
		{
			return StdAllocTAlloc(dwSize);
		}break;
	case TypeSGIAllocTAlloc:
		{
			return SGIAllocTAlloc(dwSize);
		}break;
	case TypeSGIVirtualAllocTAlloc:
		{
			return SGIVirtualAllocTAlloc(dwSize);
		}break;
	case TypeSGIHeapAllocTAlloc:
		{
			return SGIHeapAllocTAlloc(dwSize);
		}break;
	case TypeSGIMTAllocatorAlloc:
		{
			return SGIMTAllocatorAlloc(dwSize);
		}break;
	}
	return "";
}

void MemMgr::MemManager::CommonDeallocate(const MemAllocType _type,char *p,const DWORD dwSize)
{
	switch(_type)
	{
		case TypeStdAllocTAlloc:
		{
			return StdAllocTDeallocate(p,dwSize);
		}break;
	case TypeSGIAllocTAlloc:
		{
			return SGIAllocTDeallocate(p,dwSize);
		}break;
	case TypeSGIVirtualAllocTAlloc:
		{
			return SGIVirtualAllocTDeallocate(p,dwSize);
		}break;
	case TypeSGIHeapAllocTAlloc:
		{
			return SGIHeapAllocTDeallocate(p,dwSize);
		}break;
	case TypeSGIMTAllocatorAlloc:
		{
			return SGIMTAllocatorDeallocate(p,dwSize);
		}break;
	}
}