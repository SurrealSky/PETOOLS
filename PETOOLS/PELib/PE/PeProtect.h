#pragma once
#include"PeClass.h"
#include"../PER/PER.h"
#include"../VM/comm.h"

class PeProtect:public PeClass
{
private:
	PeProtect(void);
public:
	PeProtect(pe_ctx_t&);
	~PeProtect(void);
private:
	PER mPer;
	bool OCXType;
public:
	DWORD	SectionAlignmentSize(DWORD);
	DWORD	FileAlignmentSize(DWORD);
	DWORD	GetNewSection();	
public:
	bool CheckifSYS();
	DWORD CheckifDLL();
	bool CheckCOMRuntime();
	bool CheckifProtect();
	bool CheckifSectionName();
	bool CheckifPEvalid();
	bool CheckifVCM2();
	bool CheckifForwarderChain(char* pFileImage,DWORD pITBaseRO);
	DWORD PreAllocateVariable(char* Base);
	void PosAllocateVariable(char* Base,DWORD mOffset);
	bool ITMaker(char* pFileImage,DWORD pITBaseRO);
	DWORD EnDeCryptString(char* Base,DWORD dwRO);
	DWORD ProcessOrgIT(char* pFileImage,DWORD pITBaseRO);
	void AssembleIT(char* Base,DWORD dwNewSectionRO,DWORD dwNewSectionRVA);
	void ProcessTlsTable(char* Base,DWORD CryptSectionVA);
	void CryptPE();
	void CompressPE();
	void CompressResourceDirectory(char* Base,DWORD dwBaseRVA,DWORD dwRVA);
	void CryptResourceDirectory(char* Base,DWORD dwBaseRVA,DWORD dwRVA);
	void CrypterPackerwithCall(char* pFuncBody,DWORD dwSize);
	void FillWithShit(char* Base,DWORD dwSize);
	DWORD GetCallOpCodeRandom();
	void GetEncryptRO(char* pFuncBody);
	void GetOepJumpCodeRO(char* pFuncBody);
	void OepJumpEncrypt(char* Base);
	void RemoveSectionNames();
	DWORD GetChecksum(char* Base,DWORD FileSize);
	void adjustSectionCharacteristics();
	bool ClsRelocDataDirectory();
	bool ClsImportDataDirectory();
	bool ClsBoundImportDirectory();
	bool EliminateDebug();
	bool OptimizeDOSHeader();
	bool EliminateDOSHeader();
	bool RebuiltSections();
	bool EncryptImportTable();
	bool AddSectionData(const char *,const size_t,DWORD&);
	bool AddSectionToEnd(const char *,const size_t);
	bool AddOverlay(PeClass *,size_t);
	bool AddPatch(const char*,const void *,const unsigned int,const unsigned int);
	bool EncryptOne(const char*,const void*,const unsigned int,const unsigned int);
	bool EncryptTwo(const char*,const void*,const unsigned int,const unsigned int);
	bool EncryptThree(const char*);
	bool MapEncrypt(const char*,MapStructrue*);
	bool TestDis();
private:
	bool ExpandLastSection(const size_t,DWORD &);
};

