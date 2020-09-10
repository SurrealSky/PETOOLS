#include "PEMake.h"
#include<Windows.h>
#include"PeProtect.h"
#include"../Patch.h"


PEMake::PEMake()
{
	ptrPeProtect = new PeProtect(mPeCtx);
}

PEMake::~PEMake()
{
	delete ptrPeProtect;
	ptrPeProtect = NULL;
}

bool PEMake::isAnalysised()
{
	return ptrPeProtect->isAnalysised;
}

bool PEMake::PELoadFile(const char *lpPath,const char *lpModel)
{
	return ptrPeProtect->PeLoadFile(lpPath,lpModel);
}

void PEMake::PEUnload()
{
	if (ptrPeProtect)
	{
		ptrPeProtect->PeUnload();
	}
}

bool PEMake::CheckPESig()
{
	return ptrPeProtect->CheckPeSig();
}

bool PEMake::Analysis()
{
	return ptrPeProtect->Analysis();
}

void PEMake::SetAnalysised(bool isAnalysised)
{
	ptrPeProtect->isAnalysised=isAnalysised;
}

unsigned int PEMake::RvaToFoa(unsigned int rva)
{
	return ptrPeProtect->RvaToFoa(rva);
}

unsigned int PEMake::FoaToRva(unsigned int foa)
{
	return ptrPeProtect->FoaToRva(foa);
}

STu32 PEMake::SectionAlignmentSize(STu32 size)
{
	return ptrPeProtect->SectionAlignmentSize(size);
}

STu32 PEMake::FileAlignmentSize(STu32 size)
{
	return  ptrPeProtect->FileAlignmentSize(size);
}

bool PEMake::ClsRelocDataDirectory()
{
	return ptrPeProtect->ClsRelocDataDirectory();
}

bool PEMake::AddSectionToEnd(const STu8 *data, const STu32 size,const STu32 chartics)
{
	return ptrPeProtect->AddSectionToEnd(data,size, chartics);
}

bool PEMake::EncryptImportTable()
{
	return ptrPeProtect->EncryptImportTable();
}

bool PEMake::FindCodeByPeFile(const STu8 *pe, const STu32 pesize, ByteBuffer &code)
{
	DosHeader dosHeader;
	CopyMemory(&dosHeader, pe, sizeof(DosHeader));
	if (dosHeader.e_magic == 0x5A4D)
	{
		NtHeader ntHeader;
		CopyMemory(&ntHeader, pe + dosHeader.e_lfanew, sizeof(NtHeader));
		if (ntHeader.Signature == 0x00004550)
		{
			SectionHeader text;
			CopyMemory(&text, pe + dosHeader.e_lfanew + sizeof(NtHeader), sizeof(SectionHeader));

			STu32 oep=ntHeader.OptionalHeader.AddressOfEntryPoint;
			STu32 size = ntHeader.OptionalHeader.SizeOfCode;
			code.append(pe + oep, size);
			return true;
		}
	}
	return false;
}

bool PEMake::AddPatch(const STu8 *pName, const void *pPatch, const unsigned int dwSize, unsigned int mOffset)
{
	return ptrPeProtect->AddPatch(pName, pPatch, dwSize, mOffset);
}

bool PEMake::AddPatchAuto2OEP(const STu8 *pName, const void *pPatch, const unsigned int dwSize)
{
	return ptrPeProtect->AddPatchAuto2OEP(pName, pPatch, dwSize);
}

bool PEMake::Protect1A()
{
	unsigned int mShell_nSize =(DWORD) (&_patch1_ShellCodeEnd_) - (DWORD)(&_patch1_ShellCodeBegin_);
	char *pData=new char[mShell_nSize];
	memset(pData,0,mShell_nSize);
	memcpy(pData,&_patch1_ShellCodeBegin_,mShell_nSize);
	bool bret=ptrPeProtect->AddPatch((STu8*)".PEMake",pData,mShell_nSize,(DWORD)&_patch1_offset_entry_jump-(DWORD)&_patch1_ShellCodeBegin_);
	delete []pData;
	return bret;
}

bool PEMake::Protect1B()
{
	return true;
}

bool PEMake::Protect2A()
{
	unsigned int mShell_nSize =(DWORD) (&_patch2_ShellCodeEnd_) - (DWORD)(&_patch2_ShellCodeBegin_);
	char *pData=new char[mShell_nSize];
	memset(pData,0,mShell_nSize);
	memcpy(pData,&_patch2_ShellCodeBegin_,mShell_nSize);
	bool bret=ptrPeProtect->EncryptOne((STu8*)".PEMake",pData,mShell_nSize,(DWORD)&_patch2_offset_entry_jump-(DWORD)&_patch2_ShellCodeBegin_);
	delete []pData;
	return bret;
}

bool PEMake::Protect3A()
{
	//¿Ç3
	unsigned int mShell_nSize = (DWORD)(&_patch3_ShellCodeEnd_) - (DWORD)(&_patch3_ShellCodeBegin_);
	char *pData = new char[mShell_nSize];
	memset(pData, 0, mShell_nSize);
	memcpy(pData, &_patch3_ShellCodeBegin_, mShell_nSize);
	return ptrPeProtect->EncryptTwo((STu8*)(".peMake"), pData, mShell_nSize, (DWORD)&_patch3_offset_entry_jump - (DWORD)&_patch3_ShellCodeBegin_);
}

bool PEMake::Protect4A()
{
	//¿Ç4
	return ptrPeProtect->EncryptThree((STu8*)".peMake");
}

bool PEMake::WriteCtx2VirMem()
{
	return ptrPeProtect->WriteCtx2VirMem();
}