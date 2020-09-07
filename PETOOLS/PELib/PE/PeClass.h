#pragma once
#include"PEStruct.h"
#include"../VM/comm.h"
#include <stdlib.h>
#include <string>
#include <delayimp.h>
#include <vector>
#include <map>
#include "../VM/CCodeILFactory.h"

class PeClass
{
public:
	PeClass(void);
	PeClass(pe_ctx_t&);
	~PeClass(void);
public:
	pe_ctx_t	*mBaseCtx;
	bool		isAnalysised;
public:
	//初始化
	bool PeLoadFile(const char *lpPath,const char *lpModel);
	bool PeUnload();
	void InitCtx(pe_ctx_t&);
	void ClsCtx(pe_ctx_t&);
	void CopyPeCtx(pe_ctx_t & mNewCtx,const pe_ctx_t& mOldCtx);
	pe_ctx_t &Ctx(){return *mBaseCtx;};
public://映射文件
	std::vector<MapStructrue*> MapVector;
	void LoadMap(char* pmapfilename);//载入分析map文件
	MapStructrue* GetMap(char* funcname);
	BOOL GetFileAddr(char* StrAddress,int* Segment,int* FileOffset);//分割得到段和偏移
	void FreeMapVector();
public://分析函数
	bool	CheckPeSig();
	bool	Analysis();
	void	ResourceAnalysis(const STu8 *lpRes,const STu8 *lpResDir,const int dwLevel);//资源表地址，目录地址，目录级别
	const	DWORD	RvaToFoa(DWORD) const;
	const	DWORD	FoaToRva(DWORD) const;
	const	DWORD	SectionAlignmentSize(DWORD) const;
	const	DWORD	FileAlignmentSize(DWORD) const;
private:
	bool	WriteDosHeader();
	bool	WriteDosStub();
	bool	WriteSignature();
	bool	WriteImageFileHeader();
	bool	WriteImageOptionalHeader();
public:
	//将Ctx结构写入VirMem
	bool	WriteCtx2VirMem();
};