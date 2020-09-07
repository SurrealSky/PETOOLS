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
	//��ʼ��
	bool PeLoadFile(const char *lpPath,const char *lpModel);
	bool PeUnload();
	void InitCtx(pe_ctx_t&);
	void ClsCtx(pe_ctx_t&);
	void CopyPeCtx(pe_ctx_t & mNewCtx,const pe_ctx_t& mOldCtx);
	pe_ctx_t &Ctx(){return *mBaseCtx;};
public://ӳ���ļ�
	std::vector<MapStructrue*> MapVector;
	void LoadMap(char* pmapfilename);//�������map�ļ�
	MapStructrue* GetMap(char* funcname);
	BOOL GetFileAddr(char* StrAddress,int* Segment,int* FileOffset);//�ָ�õ��κ�ƫ��
	void FreeMapVector();
public://��������
	bool	CheckPeSig();
	bool	Analysis();
	void	ResourceAnalysis(const STu8 *lpRes,const STu8 *lpResDir,const int dwLevel);//��Դ���ַ��Ŀ¼��ַ��Ŀ¼����
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
	//��Ctx�ṹд��VirMem
	bool	WriteCtx2VirMem();
};