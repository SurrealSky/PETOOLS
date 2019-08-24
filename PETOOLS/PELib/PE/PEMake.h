#pragma once
#ifdef PELIB_EXPORTS
#define PELIB_EXPORTS_API __declspec(dllexport)
#else
#define PELIB_EXPORTS_API __declspec(dllimport)
#endif

#include"PEStruct.h"

extern class PeProtect;

class PELIB_EXPORTS_API PEMake {
public:
	PEMake(void);
	virtual ~PEMake(void);
private:
	PeProtect *ptrPeProtect;
public:
	pe_ctx_t	mPeCtx;
public:
	bool isAnalysised();
	bool PELoadFile(const char *lpPath,const char *lpModel);
	void PEUnload();
	bool CheckPESig();
	bool Analysis();
	void SetAnalysised(bool isAnalysised);
public:
	unsigned int RvaToFoa(unsigned int rva);
	unsigned int FoaToRva(unsigned int foa);
	bool ClsRelocDataDirectory();
	bool AddSectionToEnd(const char*, unsigned int);
	bool EncryptImportTable();
public:
	bool AddPatch(const char *pName, const void *pPatch, const unsigned int dwSize, unsigned int mOffset);
public:
	bool Protect1A();	//��һ���A���鱾13.3�ڣ�����AddPatch�������������������Ի���
	bool Protect1B();	//��һ���B���鱾20.4�ڣ�EXE�����������û���������֤����֤ʧ�ܷ����˳�
	bool Protect2A();	//�ڶ����A���鱾21�£�EXE���ܣ���ǻ�ԭIAT�������������ν���
	bool Protect3A();	//yoda��
	bool Protect4A();
};