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
	bool CheckifForwarderChain(STu8* pFileImage,DWORD pITBaseRO);
	DWORD PreAllocateVariable(STu8* Base);
	void PosAllocateVariable(STu8* Base,DWORD mOffset);
	bool ITMaker(STu8* pFileImage,DWORD pITBaseRO);
	DWORD EnDeCryptString(STu8* Base,DWORD dwRO);
	DWORD ProcessOrgIT(STu8* pFileImage,DWORD pITBaseRO);
	void AssembleIT(STu8* Base,DWORD dwNewSectionRO,DWORD dwNewSectionRVA);
	void ProcessTlsTable(STu8* Base,DWORD CryptSectionVA);
	void CryptPE();
	void CompressPE();
	void CompressResourceDirectory(STu8* Base,DWORD dwBaseRVA,DWORD dwRVA);
	void CryptResourceDirectory(STu8* Base,DWORD dwBaseRVA,DWORD dwRVA);
	void CrypterPackerwithCall(STu8* pFuncBody,DWORD dwSize);
	void FillWithShit(STu8* Base,DWORD dwSize);
	DWORD GetCallOpCodeRandom();
	void GetEncryptRO(STu8* pFuncBody);
	void GetOepJumpCodeRO(STu8* pFuncBody);
	void OepJumpEncrypt(STu8* Base);
	void RemoveSectionNames();
	DWORD GetChecksum(STu8* Base,DWORD FileSize);
	void adjustSectionCharacteristics();
	bool ClsRelocDataDirectory();
	bool ClsImportDataDirectory();
	bool ClsBoundImportDirectory();
	bool EliminateDebug();
	bool OptimizeDOSHeader();
	bool EliminateDOSHeader();
	bool RebuiltSections();
	bool EncryptImportTable();
	bool AddSectionData(const STu8 *,const size_t,DWORD&);
	bool AddSectionToEnd(const STu8 *,const size_t);
	bool AddOverlay(PeClass *,size_t);
	bool AddPatch(const STu8*,const void *,const unsigned int,const unsigned int);
	bool EncryptOne(const STu8*,const void*,const unsigned int,const unsigned int);
	bool EncryptTwo(const STu8*,const void*,const unsigned int,const unsigned int);
	bool EncryptThree(const STu8*);
	bool MapEncrypt(const STu8*,MapStructrue*);
	bool TestDis();
private:
	bool ExpandLastSection(const size_t,DWORD &);
};

