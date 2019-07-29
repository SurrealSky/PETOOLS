#include "StdAfx.h"
#include "MemManager.h"

using namespace WZHMemManager;

StdAllocT MemManager::alloc1;
SGIAllocT MemManager::alloc2;
SGIVirtualAllocT MemManager::alloc3;
SGIHeapAllocT MemManager::alloc4;
SGIMTAllocator MemManager::alloc5;

std::map<void*,unsigned int> MemManager::StdAllocTList;
std::map<void*,unsigned int> MemManager::SGIAllocTList;
std::map<void*,unsigned int> MemManager::SGIVirtualAllocTList;
std::map<void*,unsigned int> MemManager::SGIHeapAllocTList;
std::map<void*,unsigned int> MemManager::SGIMTAllocatorList;

MemManager::MemManager(void)
{
	MemManager::StdAllocTList.clear();
	MemManager::SGIAllocTList.clear();
	MemManager::SGIVirtualAllocTList.clear();
	MemManager::SGIHeapAllocTList.clear();
	MemManager::SGIMTAllocatorList.clear();
}

MemManager::~MemManager(void)
{
	//清除内存
	map<void*, unsigned int>::iterator it;
	if(MemManager::StdAllocTList.size()>0)
	{
		for(it=MemManager::StdAllocTList.begin();it!=MemManager::StdAllocTList.end();++it)
		{
			alloc1.deallocate((char*)it->first,it->second);
		}
	}
	MemManager::StdAllocTList.clear();

	if(MemManager::SGIAllocTList.size()>0)
	{
		for(it=MemManager::SGIAllocTList.begin();it!=MemManager::SGIAllocTList.end();++it)
		{
			alloc1.deallocate((char*)it->first,it->second);
		}
	}
	MemManager::SGIAllocTList.clear();

	if(MemManager::SGIVirtualAllocTList.size()>0)
	{
		for(it=MemManager::SGIVirtualAllocTList.begin();it!=MemManager::SGIVirtualAllocTList.end();++it)
		{
			alloc1.deallocate((char*)it->first,it->second);
		}
	}
	MemManager::SGIVirtualAllocTList.clear();

	if(MemManager::SGIHeapAllocTList.size()>0)
	{
		for(it=MemManager::SGIHeapAllocTList.begin();it!=MemManager::SGIHeapAllocTList.end();++it)
		{
			alloc1.deallocate((char*)it->first,it->second);
		}
	}
	MemManager::SGIHeapAllocTList.clear();

	if(MemManager::SGIMTAllocatorList.size()>0)
	{
		for(it=MemManager::SGIMTAllocatorList.begin();it!=MemManager::SGIMTAllocatorList.end();++it)
		{
			alloc1.deallocate((char*)it->first,it->second);
		}
	}
	MemManager::SGIMTAllocatorList.clear();
}


char* MemManager::StdAllocTAlloc(const DWORD dwSize)
{
	char *_ptr=MemManager::alloc1.allocate(dwSize);
	MemManager::StdAllocTList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}
void MemManager::StdAllocTDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =MemManager::StdAllocTList.find(p);
		if (it!=MemManager::StdAllocTList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc1.deallocate(p,dwSize);
			MemManager::StdAllocTList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemManager::SGIAllocTAlloc(const DWORD dwSize)
{
	char *_ptr=MemManager::alloc2.Allocate(dwSize);
	MemManager::SGIAllocTList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}
void MemManager::SGIAllocTDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =MemManager::SGIAllocTList.find(p);
		if (it!=MemManager::SGIAllocTList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc2.Deallocate(p,dwSize);
			MemManager::SGIAllocTList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemManager::SGIVirtualAllocTAlloc(const DWORD dwSize)
{
	char *_ptr=MemManager::alloc3.Allocate(dwSize);
	MemManager::SGIVirtualAllocTList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}
void MemManager::SGIVirtualAllocTDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =MemManager::SGIVirtualAllocTList.find(p);
		if (it!=MemManager::SGIVirtualAllocTList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc3.Deallocate(p,dwSize);
			MemManager::SGIVirtualAllocTList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemManager::SGIHeapAllocTAlloc(const DWORD dwSize)
{
	char *_ptr=MemManager::alloc4.Allocate(dwSize);
	MemManager::SGIHeapAllocTList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}
void MemManager::SGIHeapAllocTDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =MemManager::SGIHeapAllocTList.find(p);
		if (it!=MemManager::SGIHeapAllocTList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc4.Deallocate(p,dwSize);
			MemManager::SGIHeapAllocTList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemManager::SGIMTAllocatorAlloc(const DWORD dwSize)
{
	char *_ptr=MemManager::alloc5.Allocate(dwSize);
	MemManager::SGIMTAllocatorList.insert(std::pair<void*,unsigned int>(_ptr,dwSize));
	return _ptr;
}
void MemManager::SGIMTAllocatorDeallocate(char *p,const DWORD dwSize)
{
	if(p!=NULL)
	{
		map<void*, unsigned int>::iterator it =MemManager::SGIMTAllocatorList.find(p);
		if (it!=MemManager::SGIMTAllocatorList.end())
		{
			if(it->second!=dwSize)
			{
				//check size
			}
			alloc5.Deallocate(p,dwSize);
			MemManager::SGIMTAllocatorList.erase(it);
		}
		else
		{
			//内存不在列表
		}
	}
}

char* MemManager::CommonAlloc(const MemAllocType _type,const DWORD dwSize)
{
	switch(_type)
	{
	case TypeStdAllocTAlloc:
		{
			return MemManager::StdAllocTAlloc(dwSize);
		}break;
	case TypeSGIAllocTAlloc:
		{
			return MemManager::SGIAllocTAlloc(dwSize);
		}break;
	case TypeSGIVirtualAllocTAlloc:
		{
			return MemManager::SGIVirtualAllocTAlloc(dwSize);
		}break;
	case TypeSGIHeapAllocTAlloc:
		{
			return MemManager::SGIHeapAllocTAlloc(dwSize);
		}break;
	case TypeSGIMTAllocatorAlloc:
		{
			return MemManager::SGIMTAllocatorAlloc(dwSize);
		}break;
	}
	return "";
}
void MemManager::CommonDeallocate(const MemAllocType _type,char *p,const DWORD dwSize)
{
	switch(_type)
	{
		case TypeStdAllocTAlloc:
		{
			return MemManager::StdAllocTDeallocate(p,dwSize);
		}break;
	case TypeSGIAllocTAlloc:
		{
			return MemManager::SGIAllocTDeallocate(p,dwSize);
		}break;
	case TypeSGIVirtualAllocTAlloc:
		{
			return MemManager::SGIVirtualAllocTDeallocate(p,dwSize);
		}break;
	case TypeSGIHeapAllocTAlloc:
		{
			return MemManager::SGIHeapAllocTDeallocate(p,dwSize);
		}break;
	case TypeSGIMTAllocatorAlloc:
		{
			return MemManager::SGIMTAllocatorDeallocate(p,dwSize);
		}break;
	}
}