#include"stdafx.h"
#include"MemMgr.h"
#include"MemManager.h"
#include<Lock.h>
#include<LogLib\DebugLog.h>
#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

using namespace SurrealMemMgr;


MemMgr &MemMgr::GetInstance()
{
	//static MemMgr *instance = NULL;
	//if (!instance)
	//{
	//	AutoLock lock;
	//	if (!instance)
	//	{
	//		instance = new MemMgr();
	//	}
	//}
	//return *instance;
	SurrealDebugLog::DebugLog("MemMgr","MemMgr");
	AutoLock lock;
	static MemMgr instance;
	return instance;
}

MemMgr::MemMgr()
{
	pImpl = new MemManager();
	SurrealDebugLog::DebugLog("MemManager","init");
}

MemMgr::~MemMgr()
{
	if (pImpl)
	{
		delete pImpl;
		pImpl = NULL;
	}
	SurrealDebugLog::DebugLog("MemManager","destory");
}

const MemMgr &MemMgr::operator=(const MemMgr &m)
{
	if (pImpl)
	{
		delete pImpl;
	}
	pImpl = new MemManager(*m.pImpl);
	return *this;
}

MemMgr::MemMgr(const MemMgr &m)
{
	if (pImpl)
	{
		delete pImpl;
	}
	pImpl = new MemManager(*m.pImpl);
}

int MemMgr::GetState()
{
	return 42;
}

STu8* MemMgr::CommonAlloc(const MemAllocType _type,const STu64 Size)
{
	STu8 *pointer= (STu8*)pImpl->CommonAlloc(_type, Size);
	SurrealDebugLog::DebugLog(SurrealDebugLog::string_format("%s:MemAlloc=%02X,address=0x%08X,size=0x%X","CommonAlloc", _type, pointer,Size));
	return pointer;
}

void MemMgr::CommonDeallocate(const MemAllocType _type, STu8 *p, const STu64 Size)
{
	SurrealDebugLog::DebugLog(SurrealDebugLog::string_format("%s:MemFree=%02X,address=0x%08X,size=%X","CommonAlloc", _type, p,Size));
	return pImpl->CommonDeallocate(_type,(char*)p, Size);
}