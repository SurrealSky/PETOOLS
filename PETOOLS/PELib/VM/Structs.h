#pragma once
#include <Windows.h>
#include<map>
#include<list>
#include<disasm/disasm.h>

typedef struct _CFunctionCode
{
	//std::list<CodeNode>	mCodes;
	std::map<ulong,CodeNode> mCodes;//转换成map的树结构，提高搜索效率
	DWORD	dwSize;
	DWORD	dwBeginVirtualAddress;
	DWORD	dwEndVirtualAddress;
}CFunctionCode,*PCFunctionCode;

typedef struct _AddrNode
{
	ulong ip;
	ulong addrconst;
	ulong offset;
	_AddrNode()
	{
		memset(this,0,sizeof(_AddrNode));
	}
}AddrNode,*PAddrNode;
