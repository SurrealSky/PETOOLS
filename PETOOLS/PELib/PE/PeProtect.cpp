#include"../PELib.h"
#include"CryptVar.h"
#include "../PE/PeProtect.h"
#include "../VM/CVMFactory.h"
#include "../VM/CCodeILFactory.h"
#include"../VM/CryptErr.h"
#include"CryptVar.h"
#include"../Patch.h"
#include<time.h>


PeProtect::PeProtect(void)
{
}

PeProtect::PeProtect(pe_ctx_t &_ctx):PeClass(_ctx)
{
}

PeProtect::~PeProtect(void)
{
	ClsCtx(*mBaseCtx);
}

bool PeProtect::CheckifSYS()
{
	if((mBaseCtx->pe.mNtHeader.FileHeader.Characteristics&IMAGE_FILE_SYSTEM)==IMAGE_FILE_SYSTEM)
	{
		return true;
	}
	return false;
}

DWORD PeProtect::CheckifDLL()
{
	if((mBaseCtx->pe.mNtHeader.FileHeader.Characteristics&IMAGE_FILE_DLL)==IMAGE_FILE_DLL)
	{
		DWORD dwDllCharacter=mBaseCtx->pe.mNtHeader.OptionalHeader.DllCharacteristics;
		if((dwDllCharacter&IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE)
			 ==IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE)
		{
			ShowErr(TServernotSupport);
			return(2);
		}
			
		if((dwDllCharacter&IMAGE_DLLCHARACTERISTICS_WDM_DRIVER)
			 ==IMAGE_DLLCHARACTERISTICS_WDM_DRIVER)
		{
			ShowErr(WDMnotSupport);
			return(2);
		}

		if((dwDllCharacter&IMAGE_DLLCHARACTERISTICS_NO_SEH)
			 ==IMAGE_DLLCHARACTERISTICS_NO_SEH)
		{
			ShowErr(NOSEHnotSupport);
			return(2);
		}

		if((dwDllCharacter&IMAGE_DLLCHARACTERISTICS_NO_BIND)
			 ==IMAGE_DLLCHARACTERISTICS_NO_BIND)
		{
			ShowErr(NOBINDnotSupport);
			return(2);
		}
		OCXType=true;
		PROTECTION_FLAGS=PROTECTION_FLAGS|OCX_TYPE_FLAG;
		return(1);
	}
	OCXType=false;
	return(0);
}

bool PeProtect::CheckCOMRuntime()
{
	if(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress!=0)
	{
		return true;
	}
	return false;
}

bool PeProtect::CheckifProtect()
{
	//DWORD SectionName1,SectionName2;
	//int pSec=0;
	//for(int i=0;i<mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections-1;i++)
	//{
	//	CopyMemory(&SectionName1,image_section_header[i].Name,4);
	//	CopyMemory(&SectionName2,image_section_header[i].Name+4,4);
	//	if(((SectionName1==0)&&(SectionName2==0))||
	//	   ((SectionName1=='rsr.')&&(SectionName2=='c')))
	//	{
	//		pSec++;
	//	}
	//}
	//if(pSec==(mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections-1))
	//{
	//	return(TRUE);
	//}
	return(FALSE);
}

bool PeProtect::CheckifSectionName()
{
	//DWORD SectionName1,_SectionName1;
	//int pSec=0;
	//CopyMemory(&_SectionName1,DEPACKER_SECTION_NAME,4);
	//for(int i=0;i<image_nt_headers.FileHeader.NumberOfSections-1;i++)
	//{
	//	CopyMemory(&SectionName1,image_section_header[i].Name,4);
	//	if(SectionName1==_SectionName1)
	//	{
	//		return(TRUE);
	//	}
	//}
	return(FALSE);
}

bool PeProtect::CheckifPEvalid()
{
	//	DWORD SectionName1,SectionName2;
	//int pSec=0;
	//for(int i=0;i<image_nt_headers.FileHeader.NumberOfSections;i++)
	//{
	//	CopyMemory(&SectionName1,image_section_header[i].Name,4);
	//	CopyMemory(&SectionName2,image_section_header[i].Name+4,4);
	//	if ((SectionName1=='cra.')||	//.arch	,Alpha architecture information
	//		(SectionName1=='xet.')||	//.text	,Executable code
	//	    (SectionName1=='EDOC')||	//CODE	,Executable code
	//	    (SectionName1=='tad.')||	//.data	,Initialized data
	//	    (SectionName1=='ATAD')||	//DATA	,Initialized data
	//		(SectionName1=='ssb.')||	//.bss	,Uninitialized data
	//	    (SectionName1=='SSB')||		//BSS	,Uninitialized data
	//		(SectionName1=='ade.')||	//.edata,Export tables
	//		(SectionName1=='adi.')||	//.idata,Import tables
	//		(SectionName1=='adp.')||	//.pdata,Exception information
	//		(SectionName1=='adx.')||	//.xdata,Exception information
	//		(SectionName1=='adr.')||	//.rdata,Read-only
	//		(SectionName1=='ler.')||	//.reloc,Image relocations
	//		(SectionName1=='oler')||	//reloc	,Image relocations
	//		(SectionName1=='did.')||	//.didat
	//		(SectionName1=='slt.')||	//.tls	,Thread-local storage
	//		(SectionName1=='bed.')||	//.debug,Debug information,
	//		(SectionName1=='rsr.'))		//.rsrc	,Resource directory
	//	{
	//		pSec++;
	//	}
	//}
	//if(pSec==image_nt_headers.FileHeader.NumberOfSections)
	//{
	//	return(TRUE);
	//}
	return(TRUE);
}

bool PeProtect::CheckifVCM2()
{
	if((mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress!=0)&&
	   (mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size!=0))
	{
		return true;
	}
	return false;
}

DWORD PeProtect::SectionAlignmentSize(DWORD RawSize)
{
	DWORD result=0;

		DWORD k=RawSize%mBaseCtx->pe.mNtHeader.OptionalHeader.SectionAlignment;
		if(k==0)
		{
			result=RawSize;
		}else
		{
			result =(RawSize/mBaseCtx->pe.mNtHeader.OptionalHeader.SectionAlignment+1)
				*mBaseCtx->pe.mNtHeader.OptionalHeader.SectionAlignment;
		}
	return result;
}

DWORD PeProtect::FileAlignmentSize(DWORD RawSize)
{
	DWORD result=0;

		DWORD k=RawSize%mBaseCtx->pe.mNtHeader.OptionalHeader.FileAlignment;
		if(k==0)
		{
			result=RawSize;
		}else
		{
			result =(RawSize/mBaseCtx->pe.mNtHeader.OptionalHeader.FileAlignment+1)
				*mBaseCtx->pe.mNtHeader.OptionalHeader.FileAlignment;
		}

	return result;
}

bool PeProtect::ClsRelocDataDirectory()
{
	if(mBaseCtx->pe.mRelocsVector.size()==0) return false; //没有重定位表

	//修改PE
	mBaseCtx->pe.mRelocsVector.clear();
	mBaseCtx->pe.mNtHeader.FileHeader.Characteristics|=IMAGE_FILE_RELOCS_STRIPPED;
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress=0;
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size=0;

	//修改影像数据
	WriteCtx2VirMem();
	return true;
}

bool PeProtect::ClsImportDataDirectory()
{
	if(mBaseCtx->pe.mImportsVector.size()==0) return false; //没有导入表

	//修改PE
	mBaseCtx->pe.mImportsVector.clear();
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress=0;
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size=0;

	//修改影像数据
	/*char *pTmp=(char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	((NtHeader*)pTmp)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress=0;
	((NtHeader*)pTmp)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size=0;*/

	//修改影像数据
	WriteCtx2VirMem();
	return true;
}

bool PeProtect::ClsBoundImportDirectory()
{
	if(mBaseCtx->pe.mBoundsVector.size()==0) return false; //没有导入表

	//修改PE
	mBaseCtx->pe.mBoundsVector.clear();
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress=0;
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size=0;

	////修改影像数据
	//char *pTmp=(char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	//((NtHeader*)pTmp)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress=0;
	//((NtHeader*)pTmp)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size=0;

	//修改影像数据
	WriteCtx2VirMem();
	return true;
}

bool PeProtect::EliminateDebug()
{
	if(mBaseCtx->pe.mDebugDirectorysVector.size()==0) return false; //没有重定位表

	//修改PE
	mBaseCtx->pe.mDebugDirectorysVector.clear();
	mBaseCtx->pe.mNtHeader.FileHeader.Characteristics|=IMAGE_FILE_DEBUG_STRIPPED;
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress=0;
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size=0;

	////修改影像数据
	//char *pTmp=(char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	//((NtHeader*)pTmp)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress=0;
	//((NtHeader*)pTmp)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size=0;
	////清除重定位标志
	//((NtHeader*)pTmp)->FileHeader.Characteristics|=IMAGE_DIRECTORY_ENTRY_DEBUG;

	//修改影像数据
	WriteCtx2VirMem();
	return true;
}

bool PeProtect::OptimizeDOSHeader()
{
	//UpdateHeaders(TRUE);
	//image_dos_header.e_cblp		= 0x0092;
	//image_dos_header.e_cp		= 0x0003;
	//image_dos_header.e_crlc		= 0x0000;
	//image_dos_header.e_cparhdr	= 0x0004;
	//image_dos_header.e_minalloc	= 0x0000;
	//image_dos_header.e_lfanew	= 0x000C;
	//image_nt_headers.OptionalHeader.BaseOfData=image_dos_header.e_lfanew;
	//FillMemory(pMem,image_nt_headers.OptionalHeader.SizeOfHeaders,0x00);
	//UpdateHeaders(FALSE);
	return true;
}

bool PeProtect::EliminateDOSHeader()
{
	//	UpdateHeaders(TRUE);
	//image_dos_header.e_cblp		= 0x0040;
	//image_dos_header.e_cp		= 0x0001;
	//image_dos_header.e_crlc		= 0x0000;
	//image_dos_header.e_cparhdr	= 0x0002;
	//image_dos_header.e_minalloc	= 0x0004;
	//image_dos_header.e_maxalloc	= 0xFFFF;
	//image_dos_header.e_ss		= 0x0002;
	//image_dos_header.e_sp		= 0x0040;
	//image_dos_header.e_csum		= 0x0000;
	//image_dos_header.e_ip		= 0x000E;
	//image_dos_header.e_cs		= 0x0000;
	//image_dos_header.e_lfarlc	= 0x001C;
	//image_dos_header.e_ovno		= 0x0000;
	//image_dos_header.e_res[0]	= 0x0000;
	//image_dos_header.e_res[1]	= 0x0000;
	//image_dos_header.e_res[2]	= 0x6957;
	//image_dos_header.e_res[3]	= 0x336E;
	//image_dos_header.e_oemid	= 0x2032;
	//image_dos_header.e_oeminfo	= 0x6E6F;
	//image_dos_header.e_res2[0]	= 0x796C;
	//image_dos_header.e_res2[1]	= 0x0D21;
	//image_dos_header.e_res2[2]	= 0x240A;
	//image_dos_header.e_res2[3]	= 0xB40E;
	//image_dos_header.e_res2[4]	= 0xBA09;
	//image_dos_header.e_res2[5]	= 0x0000;
	//image_dos_header.e_res2[6]	= 0xCD1F;
	//image_dos_header.e_res2[7]	= 0xB821;
	//image_dos_header.e_res2[8]	= 0x4C01;
	//image_dos_header.e_res2[9]	= 0x21CD;
	//image_dos_header.e_lfanew	= 0x40;
	//FillMemory(pMem,image_nt_headers.OptionalHeader.SizeOfHeaders,0x00);
	//UpdateHeaders(FALSE);
	return true;
}

bool PeProtect::RebuiltSections()
{
	DWORD dwFileSize=0;
	for(int i=0;i<mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections;i++)
	{
		if(i==0)
		{
			//额外增加头部大小
			dwFileSize+=mBaseCtx->pe.mSectionsVector[i].PointerToRawData;
		}
		dwFileSize+=FileAlignmentSize(mBaseCtx->pe.mSectionsVector[i].SizeOfRawData);
	}
	STu8 *filebuffer= MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc,dwFileSize);
	FillMemory(filebuffer,dwFileSize,0);

	char *pTmp=(char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	pTmp+=sizeof(NtHeader);
	for(int i=0;i<mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections;i++)
	{
		//修正VirtualSize和SizeOfRawData
		DWORD dwVirtualSize=mBaseCtx->pe.mSectionsVector[i].Misc.VirtualSize;
		DWORD dwSizeOfRawData=mBaseCtx->pe.mSectionsVector[i].SizeOfRawData;
		mBaseCtx->pe.mSectionsVector[i].Misc.VirtualSize=SectionAlignmentSize(dwVirtualSize);
		mBaseCtx->pe.mSectionsVector[i].SizeOfRawData=FileAlignmentSize(dwSizeOfRawData);

		((SectionHeader*)pTmp)->Misc.VirtualSize=mBaseCtx->pe.mSectionsVector[i].Misc.VirtualSize;
		((SectionHeader*)pTmp)->SizeOfRawData=mBaseCtx->pe.mSectionsVector[i].SizeOfRawData;

		//修正PointerToRawData数据并拷贝区段数据
		DWORD oldPointerToRawData=mBaseCtx->pe.mSectionsVector[i].PointerToRawData;
		if(i!=0)
		{
			mBaseCtx->pe.mSectionsVector[i].PointerToRawData=mBaseCtx->pe.mSectionsVector[i-1].PointerToRawData+
				mBaseCtx->pe.mSectionsVector[i-1].SizeOfRawData;
			((SectionHeader*)pTmp)->PointerToRawData=mBaseCtx->pe.mSectionsVector[i].PointerToRawData;
		}
		CopyMemory(filebuffer+mBaseCtx->pe.mSectionsVector[i].PointerToRawData,mBaseCtx->pVirMem+oldPointerToRawData,
				mBaseCtx->pe.mSectionsVector[i].SizeOfRawData);
		pTmp+=sizeof(SectionHeader);
	}
	//修正SizeOfImage
	mBaseCtx->pe.mNtHeader.OptionalHeader.SizeOfImage=SectionAlignmentSize(mBaseCtx->pe.mSectionsVector.back().VirtualAddress
		+mBaseCtx->pe.mSectionsVector.back().Misc.VirtualSize);
	pTmp=(char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	((NtHeader*)pTmp)->OptionalHeader.SizeOfImage=mBaseCtx->pe.mNtHeader.OptionalHeader.SizeOfImage;
	//拷贝PE头
	CopyMemory(filebuffer,mBaseCtx->pVirMem,
		mBaseCtx->pe.mSectionsVector[0].PointerToRawData);
		pTmp+=sizeof(SectionHeader);

		MemMgr::GetInstance().CommonDeallocate(TypeSGIVirtualAllocTAlloc,mBaseCtx->pVirMem,mBaseCtx->size);
		mBaseCtx->pVirMem=filebuffer;
		mBaseCtx->size=dwFileSize;

	return true;
}

bool PeProtect::AddOverlay(PeClass *p,size_t size)
{
	DWORD dwAlignment=mBaseCtx->pe.mNtHeader.OptionalHeader.FileAlignment;
	//判断size是否为文件对齐粒度的整数倍
	if(size%dwAlignment!=0) return false;

	STu8 *pTmp= MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc, mBaseCtx->size+size);
	if(pTmp==NULL) return false;
	memcpy(pTmp,mBaseCtx->pVirMem,mBaseCtx->size);
	memset(pTmp+mBaseCtx->size,0x78,size);
	MemMgr::GetInstance().CommonDeallocate(TypeSGIVirtualAllocTAlloc,mBaseCtx->pVirMem,mBaseCtx->size);
	mBaseCtx->pVirMem=pTmp;
	pTmp=NULL;
	mBaseCtx->size+=size;
	return true;
}

DWORD PeProtect::GetNewSection()
{
	DWORD SectionNum = mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections;//得到节数
	return SectionAlignmentSize( mBaseCtx->pe.mSectionsVector[SectionNum-1].VirtualAddress + mBaseCtx->pe.mSectionsVector[SectionNum-1].Misc.VirtualSize);
}

//判断是否可添加一个区段
bool PeProtect::IsEnableAddNewSection()
{
	bool isEnable = true;

	//首先计算区段后数据是否够存储IMAGE_SIZEOF_SECTION_HEADER大小
	if (mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections>96)
	{
		isEnable = false;
	}
	//判断overlay
	if (mBaseCtx->pe.mOverlay.isExist)
	{
		//存在overlay，如果overlay后移的话，程序引用overlay中的数据可能出错了，
		//如果添加到overlay之后的话，那么无法判断是否存在overlay了
		isEnable = false;
	}
	//判断添加位置
	DWORD dwAlignment = mBaseCtx->pe.mNtHeader.OptionalHeader.FileAlignment;
	DWORD dwOffset = mBaseCtx->pe.mDosHeader.e_lfanew + sizeof(mBaseCtx->pe.mNtHeader) +
		mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections*IMAGE_SIZEOF_SECTION_HEADER;

	//这里我们假设的是节区数据是从文件对齐大小位置开始的
	if (FileAlignmentSize(dwOffset) - dwOffset<IMAGE_SIZEOF_SECTION_HEADER * 2)
	{
		//节区表头空间不足，可考虑扩大最后一个区段空间，将补丁代码添加进去
		isEnable = false;
	}

	//当节区数据不是从文件对齐大小开始时，需要根据数据目录中的表的文件对齐位置判断
	//(如windows notepad.exe,calc.exe)
	for (int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
	{
		if (mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[i].VirtualAddress != 0)
		{
			DWORD foa = RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[i].VirtualAddress);
			if (dwOffset - foa < IMAGE_SIZEOF_SECTION_HEADER * 2)
				isEnable = false;
		}
	}
	return isEnable;
}

/*
*参数一：区段名
*参数二：添加补丁大小
*参数三：返回添加的区域起始RVA
*/
bool PeProtect::AddSectionData(const STu8 *pName,const size_t size,DWORD &mRetAddr)
{
	if(!IsEnableAddNewSection())
	{
		//节区表头空间不足，可考虑扩大最后一个区段空间，将补丁代码添加进去
		return ExpandLastSection(size,mRetAddr);
	}
	if(AddSectionToEnd(pName,size, IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE))
	{
		mRetAddr=mBaseCtx->pe.mSectionsVector.back().VirtualAddress;
		return true;
	}
	return false;
}

bool PeProtect::AddSectionToEnd(const STu8 *pName,const size_t size, STu32 chartics)
{
	if (!IsEnableAddNewSection()) return false;

	SectionHeader mSectionHeader={0};
	if(strlen((char*)pName)<=IMAGE_SIZEOF_SHORT_NAME)
		memcpy_s(mSectionHeader.Name, IMAGE_SIZEOF_SHORT_NAME, pName, strlen((char*)pName));
	else
		memcpy_s(mSectionHeader.Name,IMAGE_SIZEOF_SHORT_NAME,pName,IMAGE_SIZEOF_SHORT_NAME);
	mSectionHeader.Misc.VirtualSize=size;   //节数据在没有对齐前真实尺寸
	mSectionHeader.VirtualAddress=SectionAlignmentSize(mBaseCtx->pe.mSectionsVector.back().VirtualAddress+
		mBaseCtx->pe.mSectionsVector.back().SizeOfRawData);//节区RVA地址（SectionAlignment粒度）
	mSectionHeader.PointerToRawData=mBaseCtx->pe.mSectionsVector.back().PointerToRawData+
		mBaseCtx->pe.mSectionsVector.back().SizeOfRawData;//节区数据在文件中的偏移
	mSectionHeader.SizeOfRawData=FileAlignmentSize(size);    //节在文件中对齐后的尺寸
	mSectionHeader.NumberOfRelocations=0;
	mSectionHeader.PointerToRelocations=0;
	mSectionHeader.NumberOfLinenumbers=0;
	mSectionHeader.PointerToLinenumbers=0;
	mSectionHeader.Characteristics= chartics;
	
	//尾部添加节区数据
	STu8 *pTmp=NULL;
	pTmp= MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc,mBaseCtx->size+FileAlignmentSize(size));
	if(pTmp==NULL) return false;
	memcpy(pTmp,mBaseCtx->pVirMem,mBaseCtx->size);
	MemMgr::GetInstance().CommonDeallocate(TypeSGIVirtualAllocTAlloc,mBaseCtx->pVirMem,mBaseCtx->size);
	mBaseCtx->size+=FileAlignmentSize(size);
	mBaseCtx->pVirMem=pTmp;
	pTmp=NULL;

	//修正ctx数据结构
	mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections++;
	mBaseCtx->pe.mNtHeader.OptionalHeader.SizeOfImage=SectionAlignmentSize(mSectionHeader.VirtualAddress+mSectionHeader.SizeOfRawData);
	mBaseCtx->pe.mSectionsVector.push_back(mSectionHeader);

	//修正影像PE数据
	WriteCtx2VirMem();
	return true;
}

bool PeProtect::ExpandLastSection(const size_t size,DWORD &iRetAddrRva)
{
	//取最后一个节区
	iRetAddrRva=mBaseCtx->pe.mSectionsVector.back().VirtualAddress+mBaseCtx->pe.mSectionsVector.back().SizeOfRawData;

	//修正影像数据
	STu8 *pTmp=NULL;
	pTmp= MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc, mBaseCtx->size+FileAlignmentSize(size));
	if(pTmp==NULL) return false;
	memcpy(pTmp,mBaseCtx->pVirMem,mBaseCtx->size);
	MemMgr::GetInstance().CommonDeallocate(TypeSGIVirtualAllocTAlloc,mBaseCtx->pVirMem,mBaseCtx->size);
	mBaseCtx->size+=FileAlignmentSize(size);
	mBaseCtx->pVirMem=pTmp;
	pTmp=NULL;

	//修正pe数据结构
	mBaseCtx->pe.mSectionsVector.back().SizeOfRawData+=FileAlignmentSize(size);
	mBaseCtx->pe.mNtHeader.OptionalHeader.SizeOfImage=SectionAlignmentSize(mBaseCtx->pe.mSectionsVector.back().VirtualAddress+
		mBaseCtx->pe.mSectionsVector.back().SizeOfRawData);
	mBaseCtx->pe.mSectionsVector.back().Misc.VirtualSize=mBaseCtx->pe.mSectionsVector.back().SizeOfRawData;
	mBaseCtx->pe.mSectionsVector.back().Characteristics|=IMAGE_SCN_CNT_INITIALIZED_DATA|IMAGE_SCN_CNT_CODE|IMAGE_SCN_MEM_EXECUTE|IMAGE_SCN_MEM_READ|IMAGE_SCN_MEM_WRITE;
	
	//修正影像PE数据
	pTmp=mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	((NtHeader*)pTmp)->OptionalHeader.SizeOfImage=SectionAlignmentSize(mBaseCtx->pe.mSectionsVector.back().VirtualAddress+
		mBaseCtx->pe.mSectionsVector.back().SizeOfRawData);
	pTmp=pTmp+(((NtHeader*)pTmp)->FileHeader.NumberOfSections-1)*sizeof(SectionHeader)+sizeof(NtHeader);//定位最后一个区段
	//定位最后一个区段
	((SectionHeader*)pTmp)->Misc=mBaseCtx->pe.mSectionsVector.back().Misc;
	((SectionHeader*)pTmp)->Characteristics=mBaseCtx->pe.mSectionsVector.back().Characteristics;
	((SectionHeader*)pTmp)->SizeOfRawData=mBaseCtx->pe.mSectionsVector.back().SizeOfRawData;

	return true;
}

//处理导入表方法一
bool PeProtect::EncryptImportTable()
{
	if(mBaseCtx->pe.mImportsVector.size()==0) return false;

	bool isPE32=true;         //32位/64位标志
#ifdef PE_MODEL
	isPE32 = true;
#else
	isPE32 = false;
#endif // PE_MODEL

	STu32 offset1 = 0;	//dllname偏移
	STu32 offset2 = 0;	//INT:thunkdata
	STu32 offset3 = 0;	//IAT:thunkdata
	STu32 offset4 = 0;	//ImportByName偏移
	STu32 offset5 = 0;	//总大小

	//offset1：计算ImportDescriptor空间大小
	offset1=(mBaseCtx->pe.mImportsVector.size()+1)*sizeof(ImportDescriptor); //包含末尾一个全0
	offset2=offset1;
	
	//offset2：计算dllname空间大小
	for (int i = 0; i < mBaseCtx->pe.mImportsVector.size(); i++)
	{
		offset2 = offset2 + mBaseCtx->pe.mImportsVector[i].strDllName.size() + 1/*结尾\0*/;
	}
	offset3 = offset2;
	
	//offset3：计算INT:ThunkData大小
	for(int i=0;i< mBaseCtx->pe.mImportsVector.size();i++)
	{
		offset3 = offset3 + sizeof(ThunkData)*(mBaseCtx->pe.mImportsVector[i].mThunksVector.size() + 1);//包含末尾全一个0
	}
	offset4 = offset3;

	//offset4：计算IAT:ThunkData大小
	for (int i = 0; i< mBaseCtx->pe.mImportsVector.size(); i++)
	{
		offset4 = offset4 + sizeof(ThunkData)*(mBaseCtx->pe.mImportsVector[i].mThunksVector.size() + 1);//包含末尾全一个0
	}
	offset5 = offset4;

	//offset5：计算ImportByName大小
	for(int i=0;i<mBaseCtx->pe.mImportsVector.size();i++)
	{
		for (int j = 0; j < mBaseCtx->pe.mImportsVector[i].mThunksVector.size(); j++)
		{
			//是不是要考虑是否是符号导入
			if (mBaseCtx->pe.mImportsVector[i].mThunksVector[j].strFuncName.size() == 0) continue;
			offset5 += sizeof(ImportByName::Hint);
			offset5 += (mBaseCtx->pe.mImportsVector[i].mThunksVector[j].strFuncName.size() + 1);
		}
	}

	//计算对齐后的总大小
	STu32 sectionSize = FileAlignmentSize(offset5);

	unsigned int sum = 0, offset = 0;

	//采用末尾增加区段存储导入表
	STu8 name[] = ".baby";
	AddSectionToEnd(name, sectionSize, IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE);
	STu64 virtualaddr = mBaseCtx->pe.mSectionsVector.back().VirtualAddress;

	//申请空间
	STu8 *pRam=(STu8*)malloc(sectionSize);
	if(pRam==NULL)
	{
		return false;
	}
	memset(pRam,0, sectionSize);
	//开始写入IMAGE_IMPORT_DESCRIPTOR
	for(int i=0;i<mBaseCtx->pe.mImportsVector.size();i++)
	{
		memcpy_s((ImportDescriptor*)pRam+i,sizeof(ImportDescriptor), &(mBaseCtx->pe.mImportsVector[i].mDescriptor),sizeof(ImportDescriptor));
	}
	//开始写入dllname
	sum=0;offset=0;
	for(int i=0;i<mBaseCtx->pe.mImportsVector.size();i++)
	{
		sum = mBaseCtx->pe.mImportsVector[i].strDllName.size() + 1;
		CopyMemory((unsigned char *)pRam + offset1 + offset, mBaseCtx->pe.mImportsVector[i].strDllName.c_str(), sum - 1);
		//修正descriptor name指针
		((ImportDescriptor*)pRam+i)->Name= virtualaddr + offset1 + offset;
		offset+=sum;
	}
	//开始写入thunk date,首先写入function name后写入thunkdata
	sum=0;
	for(int i=0,k=0;i<mBaseCtx->pe.mImportsVector.size();i++)
	{
		//修正桥1 INT
		((ImportDescriptor*)pRam+i)->OriginalFirstThunk=virtualaddr + offset2 + k * sizeof(ThunkData);
		//修正桥2 IAT
		((ImportDescriptor*)pRam+i)->FirstThunk=virtualaddr + offset3 + k * sizeof(ThunkData);
		
		for (int j = 0; j < mBaseCtx->pe.mImportsVector[i].mThunksVector.size(); j++)
		{
			if (mBaseCtx->pe.mImportsVector[i].mThunksVector[j].strFuncName.size()==0)
			{
				//相等，代表是以序列引入,最高位要置1
				//INT
				((ThunkData*)(pRam + offset2) + k)->u1.Ordinal = mBaseCtx->pe.mImportsVector[i].mThunksVector[j].Ordinal | OrdinalFlag;
				//IAT
				((ThunkData*)(pRam + offset3) + k)->u1.Ordinal = mBaseCtx->pe.mImportsVector[i].mThunksVector[j].Ordinal | OrdinalFlag;
				k++;//用于函数个数计算
			}
			else
			{
				//以函数名方式引入
				((ThunkData*)(pRam + offset2) + k)->u1.Function = virtualaddr + offset4 + sum;
				((ThunkData*)(pRam + offset3) + k)->u1.Function = virtualaddr + offset4 + sum;

				CopyMemory(pRam + offset4 + sum, &mBaseCtx->pe.mImportsVector[i].mThunksVector[j].Ordinal, sizeof(ImportByName::Hint));
				sum += sizeof(ImportByName::Hint);
				STu32 len = mBaseCtx->pe.mImportsVector[i].mThunksVector[j].strFuncName.size() + 1;
				CopyMemory(pRam + offset4 + sum, mBaseCtx->pe.mImportsVector[i].mThunksVector[j].strFuncName.c_str(), len);
				sum += len;
				k++;
			}
		}
		k++;//用于空出其中的全0结构
	}
	//写入完毕，开始修改导入表地址
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress=virtualaddr;
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size= offset1;
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress=virtualaddr+offset3;  //需要修正
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size=offset4-offset3;

	//复制进内存
	WriteCtx2VirMem();
	memcpy(mBaseCtx->pVirMem+RvaToFoa(virtualaddr), pRam, sectionSize);

	free(pRam);
	return true;
}

/*
*加密方式一:第一类壳：PE文件添加补丁代码
*参数一：区段名
*参数二：补丁数据
*参数三：补丁数据大小
*参数四：(E9)XX XX XX XX指令相对补丁起始偏移
*/
bool PeProtect::AddPatch(const STu8 *pName,const void *pPatch,const unsigned int dwSize,const unsigned int mOffset,const unsigned int nopbytes)
{
	//增加区段
	DWORD mRetAddr=0;
	if(!AddSectionData(pName, nopbytes + dwSize,mRetAddr)) return false;
	
	//填充滑板指令(默认为NOP=0x90)
	DWORD dwOffset = RvaToFoa(mRetAddr);
	memset(mBaseCtx->pVirMem + dwOffset, 0x90, nopbytes);

	//复制补丁数据
	memcpy(mBaseCtx->pVirMem + dwOffset + nopbytes,pPatch,dwSize);
	
	DWORD _rva_oldOEP=mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;  //记录原始OEP
	mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint= mRetAddr;//默认不跳过滑板指令
	
	WriteCtx2VirMem();

	//修正JMP XX XX XX XX
	DWORD _rva_newOEP = mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;
	DWORD _foa_newOEP=RvaToFoa(_rva_newOEP);
	*(int*)(mBaseCtx->pVirMem + _foa_newOEP + nopbytes + mOffset)=_rva_oldOEP-_rva_newOEP - nopbytes -mOffset-4;
	return true;
}

/*
*加密方式一:第一类壳：PE文件添加补丁代码(自动添加E9 XX XX XX XX指令)
*参数一：区段名
*参数二：补丁数据
*参数三：补丁数据大小
*/
bool PeProtect::AddPatchAuto2OEP(const STu8 *pName, const void *pPatch, const unsigned int dwSize, const unsigned int nopbytes)
{
	//增加区段
	DWORD mRetAddr = 0;
	if (!AddSectionData(pName, nopbytes + dwSize + 5, mRetAddr)) return false;

	//填充滑板指令(默认为NOP=0x90)
	DWORD dwOffset = RvaToFoa(mRetAddr);
	memset(mBaseCtx->pVirMem + dwOffset, 0x90, nopbytes);

	//复制补丁数据
	memcpy(mBaseCtx->pVirMem + dwOffset + nopbytes, pPatch, dwSize);
	*(mBaseCtx->pVirMem + dwOffset + nopbytes + dwSize) = 0xe9;	//jmp

	DWORD _rva_oldOEP = mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;  //记录原始OEP
	mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint = mRetAddr;
	
	WriteCtx2VirMem();

	//修正JMP XX XX XX XX
	DWORD _rva_newOEP = mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;
	DWORD _foa_newOEP = RvaToFoa(_rva_newOEP);
	*(int*)(mBaseCtx->pVirMem + _foa_newOEP + nopbytes + dwSize + 1) = _rva_oldOEP - _rva_newOEP - nopbytes- dwSize - 5;
	return true;
}

/*
*加密方式二:第二类壳A
*参数一：区段名
*参数二：补丁数据
*参数三：补丁数据大小
*参数四：补丁修正原始OPE地址的偏移
*/
bool PeProtect::EncryptOne(const STu8 *pName,const void *pPatch,const unsigned int dwSize,const unsigned int mOffset)
{
	//增加区段
	DWORD iRetRvaAddr=0;
	if(!AddSectionData(pName,dwSize,iRetRvaAddr)) return false;
	//复制补丁数据
	DWORD dwOffset=RvaToFoa(iRetRvaAddr);
	CopyMemory(mBaseCtx->pVirMem+dwOffset,pPatch,dwSize);
	//首先将DataDirectory复制到补丁
	STu8* pTmp=mBaseCtx->pVirMem+dwOffset+0x5;//跳过补丁头部jmp start
	CopyMemory(pTmp,mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory,sizeof(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory));
	//数据目录表清0
	memset(&(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory),0,sizeof(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory));
	//保存加密基表
	pTmp=pTmp+sizeof(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory);
	STu8 encrypt_table[256]={0};
	for(int i=0;i<sizeof(encrypt_table);i++)
	{
		encrypt_table[i]=i;
	}
	//打乱加密基表
	int count=sizeof(encrypt_table);
    srand(time(NULL));  
    for(int i=0; i<count; i++)  
    {  
        unsigned int index=rand()%(count-i)+i;     
        if(index!=i)  
        {  
            STu8 tmp=encrypt_table[i];  
            encrypt_table[i]=encrypt_table[index];  
            encrypt_table[index]=tmp;  
        }  
    }  
	memcpy(pTmp,encrypt_table,sizeof(encrypt_table));
	//加密节区数据(此处若存在.txtbss段数据，则失败)
	STu8 *_offset_stop=mBaseCtx->pVirMem + RvaToFoa(iRetRvaAddr);
	for(int i=0;i<mBaseCtx->pe.mSectionsVector.size();i++)
	{
		//当地址大于iRetRvaAddr补丁地址，不进行加密
		pTmp= mBaseCtx->pVirMem + mBaseCtx->pe.mSectionsVector[i].PointerToRawData;
		STu32 j=mBaseCtx->pe.mSectionsVector[i].SizeOfRawData;

		for(int k=0;k<j;k++)
		{
			if(pTmp+k>=(unsigned char*)_offset_stop) break;
			unsigned char c=pTmp[k];
			pTmp[k]=encrypt_table[c];
		}
	}
	//填充一字节0数据
	pTmp=mBaseCtx->pVirMem + dwOffset + 0x5 + sizeof(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory)
		+ sizeof(encrypt_table);
	*(pTmp++)=0;
	//保存最后一节原始大小
	*(STu32*)pTmp=dwOffset-mBaseCtx->pe.mSectionsVector.back().PointerToRawData;

	//清除重定位标志
	ClsRelocDataDirectory();

	//修正OEP
	DWORD _rva_oldOEP=mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;  //记录原始OEP
	mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint=iRetRvaAddr;	
	DWORD _rva_newOEP=mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;

	WriteCtx2VirMem();

	//尝试使用变量重定位方式
	DWORD _foa_newOEP=RvaToFoa(_rva_newOEP);
	*(int*)(mBaseCtx->pVirMem+_foa_newOEP+mOffset)=_rva_oldOEP-_rva_newOEP-mOffset-4;
	return true;
}

/*
*加密方式一:第三类壳A-yoda 1.02
*参数一：区段名
*参数二：补丁数据
*参数三：补丁数据大小
*参数四：补丁修正原始OPE地址的偏移
*/
bool PeProtect::EncryptTwo(const STu8 *pName,const void *pPatch,const unsigned int dwSize,const unsigned int mOffset)
{
	//check MZ
	if(mBaseCtx->pe.mDosHeader.e_magic!=IMAGE_DOS_SIGNATURE)
	{
		ShowErr(PEErr);
		return false;
	}
	// PE00
	if(mBaseCtx->pe.mNtHeader.Signature!=IMAGE_NT_SIGNATURE)
	{
		ShowErr(PEErr);
		return false;
	}
	if(CheckifSYS())
	{
		ShowErr(SYSnotSupport);
		return false;
	}
	if(CheckifDLL()==2)
	{
		return false;
	}
	if(CheckCOMRuntime())
	{
		ShowErr(PEisCOMRuntime);
		return false;
	}
	if(CheckifProtect())
	{
		ShowErr(FileISProtect);
		return false;
	}
	if(CheckifSectionName())
	{
		ShowErr(PackSectionName);
		return false;
	}
	if(!CheckifPEvalid())
	{
		return false;
	}
	if(CheckifVCM2())
	{
		//PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress=0;
		//PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size=0;
	}
	DWORD dwOrgITRVA=mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	if(mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections > 20)
	{
		ShowErr(SecNumErr);
		return false;
	}
	dwOrgEntryPoint=mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;
	dwImageBase=mBaseCtx->pe.mNtHeader.OptionalHeader.ImageBase;
	//----- DELETE Bound Import & IAT DIRECTORIES -----
	// Update local IMAGE_NT_HEADERS variable
	ClsBoundImportDirectory();
	ClsImportDataDirectory();

	//----- ENCRYPT DLL/API NAMES & SAVE IT & DESTROY IID's -----
	DWORD dwOrgITRO=RvaToFoa(dwOrgITRVA);
	if(!CheckifForwarderChain(mBaseCtx->pVirMem,dwOrgITRO))
	{
		PROTECTION_FLAGS&= ~API_REDIRECT_FLAG;	
	}

	if(ProcessOrgIT(mBaseCtx->pVirMem,dwOrgITRO)==0)
	{
		return false;
	}

	//------ ELIMINATE RELOC -----
	// Redirect Relocation Directory
	RelocRVA=mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
	RelocSize=mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;
	RlocBackup.VirtualAddress=0x00;
	RlocBackup.SizeOfBlock=0x08;
	if(true)
	{
		//去除重定位表
		RelocRVA=0;
		RelocSize=0;
		ClsRelocDataDirectory();
	}
	
	EliminateDebug();
	
	OptimizeDOSHeader();
	
	EliminateDOSHeader();

	//----- ADD THE PACKER SECTION -----
	DWORD mRetAddr=0;
	AddSectionData(pName,IT_SIZE+dwSize,mRetAddr);

	//调整section属性
	adjustSectionCharacteristics();

	//copy patch to section
	CopyMemory(mBaseCtx->pVirMem+RvaToFoa(mRetAddr)+IT_SIZE,pPatch,dwSize);

	//获取一些偏移并加密其中的0xCCCCCCCC
	GetOepJumpCodeRO(mBaseCtx->pVirMem+RvaToFoa(mRetAddr)+IT_SIZE);
	GetEncryptRO(mBaseCtx->pVirMem+RvaToFoa(mRetAddr)+IT_SIZE);

	//----- CREATE PACKER IMPORT TABLE -----
	AssembleIT(mBaseCtx->pVirMem,RvaToFoa(mRetAddr),mRetAddr);

	//---- REPLACE TLS TABLE -----
	ProcessTlsTable(mBaseCtx->pVirMem,mRetAddr);

	// encrypt !
	CompressPE();

	CryptPE();

	RemoveSectionNames();

	// UPDATE ImportTable RVA ...
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress=mRetAddr;
	mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size=IT_SIZE;
	unsigned char *pTmp=(unsigned char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	((NtHeader*)pTmp)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress=mRetAddr;
	((NtHeader*)pTmp)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size=IT_SIZE;

	DWORD dwPreVarSize=PreAllocateVariable(mBaseCtx->pVirMem+RvaToFoa(mRetAddr)+IT_SIZE);
	PosAllocateVariable(mBaseCtx->pVirMem+RvaToFoa(mRetAddr)+IT_SIZE,(DWORD)&_patch3_PRE_VARIABLE_START_-
		(DWORD)&_patch3_ShellCodeBegin_);

	CrypterPackerwithCall(mBaseCtx->pVirMem+RvaToFoa(mRetAddr)+IT_SIZE,DEPACKER_CODE_SIZE);//some crazy work

	//----- ENCRYPT OEP JUMP CODE -----
	DWORD dwEncOffset=(DWORD)&_patch3_LABEL_OEP_JUMP_CODE_START_-(DWORD)&_patch3_ShellCodeBegin_;
	DWORD dwEncSize=(DWORD)&_patch3_LABEL_OEP_JUMP_CODE_END_-(DWORD)&_patch3_LABEL_OEP_JUMP_CODE_START_;
	mPer.MyEasyEncrypt(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwEncOffset,dwEncSize);
	DWORD dwDecOffset=(DWORD)&_patch3_LABEL_OepJumpDecryptLoop-(DWORD)&_patch3_ShellCodeBegin_;
	STu8 *SecDecryptBuff=new STu8[OEP_PER_SIZE];
	mPer.MyMakePER(SecDecryptBuff,OEP_PER_SIZE);
	CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff,OEP_PER_SIZE);
	delete []SecDecryptBuff;
	SecDecryptBuff=0;
	//---------------------------------

	//----- ENCRYPT SectionInfo -----
	dwEncOffset=(DWORD)&_patch3_LABEL_RO_SectionNames_START_-(DWORD)&_patch3_ShellCodeBegin_;
	dwEncSize=(DWORD)&_patch3_LABEL_RO_EXPLORER_EXE_END_-(DWORD)&_patch3_LABEL_RO_SectionNames_START_;
	mPer.MyEasyEncrypt(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwEncOffset,dwEncSize);
	dwDecOffset=(DWORD)&_patch3_LABEL_DecryptSectionsInfoLoop-(DWORD)&_patch3_ShellCodeBegin_;
	SecDecryptBuff=new STu8[SEC_PER_SIZE];
	mPer.MyMakePER(SecDecryptBuff,SEC_PER_SIZE);
	CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff,SEC_PER_SIZE);
	delete []SecDecryptBuff;
	SecDecryptBuff=0;
	//---------------------------------

	//-------- ENCRYPT LOADER ---------
	// generate PER
	//---------------------------------
	dwEncOffset=(DWORD)&_patch3_LABEL_VARIABLE_CRYPT_START_-(DWORD)&_patch3_ShellCodeBegin_;
	dwEncSize=(DWORD)&_patch3_LABEL_VARIABLE_CRYPT_END_-(DWORD)&_patch3_LABEL_VARIABLE_CRYPT_START_;
	mPer.MyEasyEncrypt(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwEncOffset,dwEncSize);
	dwDecOffset=(DWORD)&_patch3_LABEL_VariableDecryptLoop-(DWORD)&_patch3_ShellCodeBegin_;
	SecDecryptBuff=new STu8[VAR_PER_SIZE];
	mPer.MyMakePER(SecDecryptBuff,VAR_PER_SIZE);
	CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff,VAR_PER_SIZE);
	delete []SecDecryptBuff;
	SecDecryptBuff=0;
	//---------------------------------

	//---------------------------------
	dwEncOffset=(DWORD)&_patch3_PackEncrypt_START_-(DWORD)&_patch3_ShellCodeBegin_;
	dwEncSize=(DWORD)&_patch3_PackEncrypt_END_-(DWORD)&_patch3_PackEncrypt_START_;
	mPer.MyEasyEncrypt(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwEncOffset,dwEncSize);
	dwDecOffset=(DWORD)&_patch3_LABEL_PackDecryptLoop-(DWORD)&_patch3_ShellCodeBegin_;
	SecDecryptBuff=new STu8[PACK_PER_SIZE];
	mPer.MyMakePER(SecDecryptBuff, PACK_PER_SIZE);
	CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff, PACK_PER_SIZE);
	delete []SecDecryptBuff;
	SecDecryptBuff=0;
	//---------------------------------

	//修正OEP
	DWORD _rva_oldOEP=mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;  //记录原始OEP
	mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint=mRetAddr+IT_SIZE+dwPreVarSize;
	//修正影像OEP
	pTmp=(unsigned char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	((NtHeader*)pTmp)->OptionalHeader.AddressOfEntryPoint=mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;


	//----- CALCULATE CHECKSUM -----
	DWORD dwPackEncryptSize=(DWORD)&_patch3_LABEL_OEP_JUMP_CODE_START_-(DWORD)&_patch3_ShellCodeBegin_;
	dwOrgChecksumSize=RvaToFoa(mRetAddr);
	dwOrgChecksumSize+=IT_SIZE;
	dwOrgChecksumSize+=dwPackEncryptSize;
	dwOrgChecksum=GetChecksum(mBaseCtx->pVirMem,dwOrgChecksumSize);

	//----- PASTE CHECKSUMSIZE ------
	DWORD dwOrgChecksumSizeOffset=(DWORD)&_patch3_RO_dwOrgChecksumSize-(DWORD)&_patch3_ShellCodeBegin_;
	CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwOrgChecksumSizeOffset,&dwOrgChecksumSize,4);

	//----- PASTE CHECKSUM ------
	DWORD dwOrgChecksumOffset=(DWORD)&_patch3_RO_dwOrgChecksum-(DWORD)&_patch3_ShellCodeBegin_;
	CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwOrgChecksumOffset,&dwOrgChecksum,4);
	
	return true;
}

/*
*虚拟机壳
*/
bool PeProtect::EncryptThree(const STu8 *strSectionName)
{
	DWORD pStartAddr=0;
	DWORD size=0;
	DWORD mode=0;

	pStartAddr=mBaseCtx->pe.mNtHeader.OptionalHeader.BaseOfCode;
	size=mBaseCtx->pe.mNtHeader.OptionalHeader.SizeOfCode;

	//判断机器位数
#ifdef PE_MODEL
	mode=32;
#else
	mode=64;//暂不支持
#endif

	char *pCode = (char *)mBaseCtx->pVirMem+RvaToFoa(pStartAddr);
	pStartAddr+=mBaseCtx->pe.mNtHeader.OptionalHeader.ImageBase;


	CCodeILFactory codefactory;
	AVL<CodeNode,ulong> AVLTree;
	list<AddrNode*> AddrNodes;
	codefactory.Init(mBaseCtx->pe.mNtHeader.OptionalHeader.ImageBase+GetNewSection(),size);
	codefactory.DisasmCodes(&AVLTree,&AddrNodes,pCode,size,pStartAddr);

	AVLNode<CodeNode,ulong> *pBeginNode=AVLTree.FindMin(AVLTree.Root());
	AVLNode<CodeNode,ulong> *pEndNode=AVLTree.FindMax(AVLTree.Root());

	int asmlen = pEndNode->data.disasm.ip+pEndNode->data.disasm.codelen - pBeginNode->data.disasm.ip;
	codefactory.VMFactory.CompileEnterStubCode(pCode,pBeginNode->data.disasm.ip,asmlen);
	char errtext[255] = {0};
	codefactory.BuildCode(pCode,&AVLTree,&AddrNodes,errtext);

	int len = codefactory.m_JumpTable.m_addrlen + codefactory.m_CodeEngine.m_addrlen +
				codefactory.m_EnterStub.m_addrlen + codefactory.m_VMEnterStubCode.m_addrlen + 
				codefactory.m_VMCode.m_addrlen;
	char *newdata = new char[len];
	char *p = newdata;
	memcpy( p,codefactory.m_JumpTable.m_BaseAddr,codefactory.m_JumpTable.m_addrlen );
	p += codefactory.m_JumpTable.m_addrlen;
	memcpy( p,codefactory.m_CodeEngine.m_BaseAddr,codefactory.m_CodeEngine.m_addrlen );
	p += codefactory.m_CodeEngine.m_addrlen;
	memcpy( p,codefactory.m_EnterStub.m_BaseAddr,codefactory.m_EnterStub.m_addrlen );
	p += codefactory.m_EnterStub.m_addrlen;
	memcpy( p,codefactory.m_VMEnterStubCode.m_BaseAddr,codefactory.m_VMEnterStubCode.m_addrlen );
	p += codefactory.m_VMEnterStubCode.m_addrlen;
	memcpy( p,codefactory.m_VMCode.m_BaseAddr,codefactory.m_VMCode.m_addrlen );
	p += codefactory.m_VMCode.m_addrlen;
	p=NULL;
	//增加区段
	DWORD mRetAddr=0;
	AddSectionData(strSectionName,len,mRetAddr);
	//复制补丁数据
	DWORD dwOffset=mBaseCtx->pe.mSectionsVector.back().PointerToRawData; //最后一节的偏移
	DWORD mSizeOfRawData=mBaseCtx->pe.mSectionsVector.back().SizeOfRawData; //最后一节数据大小
	memcpy(mBaseCtx->pVirMem+dwOffset,newdata,len);
	delete []newdata;
	newdata=NULL;

	//擦出重定位表
	ClsRelocDataDirectory();

	//修正OEP
	mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint=mBaseCtx->pe.mNtHeader.OptionalHeader.BaseOfCode;
	//修正影像OEP
	char *pTmp=(char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	((NtHeader*)pTmp)->OptionalHeader.AddressOfEntryPoint=mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;
	return true;
}

/*
*使用map加载函数加密
*/
bool PeProtect::MapEncrypt(const STu8 *strSectionName,MapStructrue* stu)
{
	//CCodeILFactory codefactory;
	////CLink CodeList;
	//list<CodeNode*> CodeList;
	//list<AddrNode*> AddrNodes;
	//codefactory.Init(mBaseCtx->pe.mNtHeader.OptionalHeader.ImageBase+GetNewSection());

	//char * Base_Addr=mBaseCtx->pVirMem+mBaseCtx->pe.mSectionsVector[stu->Segment-1].PointerToRawData+stu->Offset;
	//codefactory.DisasmFunction(&CodeList,Base_Addr,stu->VirtualAddress);
	//list<CodeNode*>::iterator itr;
	//itr = CodeList.begin();
	//CodeNode* code = *itr;
	//itr = CodeList.end();
	//itr--;
	//CodeNode* endcode = *itr;
	//int asmlen = endcode->disasm.ip+endcode->disasm.codelen - code->disasm.ip;
	//codefactory.VMFactory.CompileEnterStubCode(Base_Addr,code->disasm.ip,asmlen);

	//char errtext[255] = {0};
	//codefactory.BuildCode(Base_Addr,&CodeList,&AddrNodes,errtext);

	//int len = codefactory.m_JumpTable.m_addrlen + codefactory.m_CodeEngine.m_addrlen +
	//			codefactory.m_EnterStub.m_addrlen + codefactory.m_VMEnterStubCode.m_addrlen + 
	//			codefactory.m_VMCode.m_addrlen;
	//char *newdata = new char[len];
	//char *p = newdata;
	//memcpy( p,codefactory.m_JumpTable.m_BaseAddr,codefactory.m_JumpTable.m_addrlen );
	//p += codefactory.m_JumpTable.m_addrlen;
	//memcpy( p,codefactory.m_CodeEngine.m_BaseAddr,codefactory.m_CodeEngine.m_addrlen );
	//p += codefactory.m_CodeEngine.m_addrlen;
	//memcpy( p,codefactory.m_EnterStub.m_BaseAddr,codefactory.m_EnterStub.m_addrlen );
	//p += codefactory.m_EnterStub.m_addrlen;
	//memcpy( p,codefactory.m_VMEnterStubCode.m_BaseAddr,codefactory.m_VMEnterStubCode.m_addrlen );
	//p += codefactory.m_VMEnterStubCode.m_addrlen;
	//memcpy( p,codefactory.m_VMCode.m_BaseAddr,codefactory.m_VMCode.m_addrlen );
	//p += codefactory.m_VMCode.m_addrlen;
	//p=NULL;
	////增加区段
	//DWORD mRetAddr=0;
	//AddSectionData(strSectionName,len,mRetAddr);
	////复制补丁数据
	//DWORD dwOffset=mBaseCtx->pe.mSectionsVector.back().PointerToRawData; //最后一节的偏移
	//DWORD mSizeOfRawData=mBaseCtx->pe.mSectionsVector.back().SizeOfRawData; //最后一节数据大小
	//memcpy(mBaseCtx->pVirMem+dwOffset,newdata,len);
	//delete []newdata;
	//newdata=NULL;

	////擦出重定位表
	//ClsRelocDataDirectory();
	return true;
}

/*
*转发器
*/
bool PeProtect::CheckifForwarderChain(STu8* pFileImage,DWORD pITBaseRO)
{
	ImportDescriptor import_descriptor;// -> IID
	CopyMemory(&import_descriptor,
			   pFileImage+pITBaseRO,
			   sizeof(ImportDescriptor));
	if(import_descriptor.ForwarderChain==0xFFFFFFFF)return(FALSE);
	return(TRUE);
}

/*
*OCX类型
*/
bool PeProtect::ITMaker(STu8* pFileImage,DWORD pITBaseRO)
{
	return true;
}

//----------------------------------------------------------------
// This function encrypts the dll name strings, saves the ImageImportDescriptors to the loader data 
// and destroys them.
// return values:
// 1 - success
// 0 - too much IID's !
DWORD PeProtect::EnDeCryptString(STu8* Base,DWORD dwRO)
{
	UCHAR _temp;
	for(int i=0;i<255;i++)//DllCryptLoop
	{
		CopyMemory(&_temp,Base+dwRO+i,1);
		__asm ROR _temp,4;
		CopyMemory(Base+dwRO+i,&_temp,1);
		if(_temp==0x00) break;
	}
	return(1);
}

//----------------------------------------------------------------
// This function encrypts the dll name strings, saves the ImageImportDescriptors to the loader data 
// and destroys them.
// return values:
// 1 - success
// 0 - too much IID's !
DWORD PeProtect::ProcessOrgIT(STu8* pFileImage,DWORD pITBaseRO)
{
	DWORD stupid_num;
	DWORD dwIIDNum;
	FillMemory(IIDInfo,sizeof(IIDInfo),0x00);
	stupid_num=GetTickCount();// get a random number
	stupid_num=stupid_num ^ 'ashk';// EDX -> stupid number :)
	// start
	IMAGE_IMPORT_DESCRIPTOR import_descriptor;// -> IID
	dwIIDNum=0;
	CopyMemory(&import_descriptor,
			   pFileImage+pITBaseRO+dwIIDNum*sizeof(IMAGE_IMPORT_DESCRIPTOR),
			   sizeof(IMAGE_IMPORT_DESCRIPTOR));
	while(import_descriptor.Name)
	{
	   	dwIIDNum++;
		if(dwIIDNum == (MAX_IID_NUM))// too much IID's ?
		{
			return 0;
		}	   
		// save IID Infos -> Loader IT data array
		IIDInfo[dwIIDNum-1].DllNameRVA=import_descriptor.Name;
		IIDInfo[dwIIDNum-1].OrgFirstThunk=import_descriptor.OriginalFirstThunk;
		IIDInfo[dwIIDNum-1].FirstThunk=import_descriptor.FirstThunk;
		//-> get dll pointer
		DWORD dllpoint=RvaToFoa(import_descriptor.Name);
		EnDeCryptString(pFileImage,dllpoint);//-> crypt string   
		//--- CRYPT API name strings ---
  		DWORD dllfileRef=import_descriptor.OriginalFirstThunk;
  		if(!dllfileRef)
		{
			dllfileRef=import_descriptor.FirstThunk;
		}
		dllfileRef=RvaToFoa(dllfileRef);
		DWORD _dllfileRef=dllfileRef;
		DWORD dllfilePoint;
		CopyMemory(&dllfilePoint,pFileImage+_dllfileRef,4);
  		while( dllfilePoint!=0)// ESI -> Thunk pointer
		{			
			if((_dllfileRef&IMAGE_ORDINAL_FLAG32)==0)// is it an Ordinal Import ?
			{
				dllfilePoint=RvaToFoa(dllfilePoint);
  				if(dllfilePoint!=0)
				{
					EnDeCryptString(pFileImage,dllfilePoint+2);//-> crypt string; skip the HINT
				}
			}	      
			_dllfileRef=_dllfileRef+4;
			CopyMemory(&dllfilePoint,pFileImage+_dllfileRef,4);
		}		
  		// destroy Original IID*/
		import_descriptor.Name=stupid_num;
		import_descriptor.OriginalFirstThunk=stupid_num;
		import_descriptor.FirstThunk=stupid_num;
		import_descriptor.TimeDateStamp=stupid_num;
		import_descriptor.ForwarderChain=stupid_num;
		CopyMemory(pFileImage+pITBaseRO+(dwIIDNum-1)*sizeof(IMAGE_IMPORT_DESCRIPTOR),
				   &import_descriptor,
			       sizeof(IMAGE_IMPORT_DESCRIPTOR));
		CopyMemory(&import_descriptor,
			       pFileImage+pITBaseRO+dwIIDNum*sizeof(IMAGE_IMPORT_DESCRIPTOR),
			       sizeof(IMAGE_IMPORT_DESCRIPTOR));//-> point to next IID
	}
	return 1;
}

//----------------------------------------------------------------
// This function assembles Import Table for new section
void PeProtect::AssembleIT(STu8* Base,DWORD dwNewSectionRO,DWORD dwNewSectionRVA)
{
	STu8* pAddress4IT=Base+dwNewSectionRO;//-> base of the new IT		
	// Zero the memory for the new IT
	FillMemory(Base+dwNewSectionRO,IT_SIZE,0x00);
	// build a new,nice ImportTable :)
	IMAGE_IMPORT_DESCRIPTOR import_descriptor;//assume esi:ptr IMAGE_IMPORT_DESCRIPTOR
	CopyMemory(&import_descriptor,
			   pAddress4IT,
			   sizeof(IMAGE_IMPORT_DESCRIPTOR));
	// make ebx point after the terminating IID	
	DWORD dwRO=dwNewSectionRO+2*sizeof(IMAGE_IMPORT_DESCRIPTOR);
	import_descriptor.Name=dwNewSectionRVA+2*sizeof(IMAGE_IMPORT_DESCRIPTOR);// process the IID Name
	CopyMemory(Base+dwRO
			  ,_szKernel32,strlen(_szKernel32));
	dwRO=dwRO+strlen(_szKernel32)+1;
	// process the FirstThunk pointers
    import_descriptor.FirstThunk=dwRO-dwNewSectionRO+dwNewSectionRVA;
	DWORD dwRO_,dwRO1;
	dwRO1=dwRO+10;
	dwRO_=dwRO1-dwNewSectionRO+dwNewSectionRVA;
	CopyMemory(Base+dwRO,&dwRO_,4);
	dwRO1=dwRO1+2;
	CopyMemory(Base+dwRO1,_szLoadLibrary,strlen(_szLoadLibrary));

	dwRO1=dwRO1+strlen(_szLoadLibrary);
	dwRO=dwRO+4;
	dwRO_=dwRO1-dwNewSectionRO+dwNewSectionRVA;
	CopyMemory(Base+dwRO,&dwRO_,4);
	dwRO1=dwRO1+2;
	CopyMemory(Base+dwRO1,_szGetProcAddress,strlen(_szGetProcAddress));

	CopyMemory(Base+dwNewSectionRO,
			   &import_descriptor,
			   sizeof(IMAGE_IMPORT_DESCRIPTOR));
}


//----------------------------------------------------------------
// This function relocates the Thread Local Storage (TLS) Table
// in different place
void PeProtect::ProcessTlsTable(STu8* Base,DWORD dwCryptSectionRVA)
{
	//DWORD TlsDirAddr;
	//// check whether there's a tls table
	//TlsDirAddr=PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress;
	//DWORD dwRO;
	//if(TlsDirAddr!=0)// check if no tls section
	//{
	//	// get a RAW pointer to the tls table
	//	dwRO=RVA2Offset(Base,TlsDirAddr);//-> pointer to tls tables
	//	if(dwRO!=0)
	//	{
	//		dwRO_TlsBackup =DEPACKER_CODE_SIZE-(EXTRA_END_SIZE+sizeof(IMAGE_TLS_DIRECTORY32));;
	//		// copy the whole TLS table into the loader data part
	//		CopyMemory(&TlsBackup,Base+dwRO,sizeof(IMAGE_TLS_DIRECTORY32));			
	//		// fix the TLS DIRECTORY VA
	//		PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress
	//			=dwCryptSectionRVA+IT_SIZE+dwRO_TlsBackup;
	//		FillMemory(Base+dwRO,sizeof(IMAGE_TLS_DIRECTORY32),0x00);
	//	}
	//}
}

//----------------------------------------------------------------
// Base   = pointer to file memory
// dwMode: 0 - RawCrypt mode
//         1 - VirtualCrypt mode
void PeProtect::CryptPE()
{
	DWORD SectionName1,SectionName2;
	DWORD CryptStart;
	DWORD CryptSize;
	DWORD dwDecOffset;
	DWORD mRetAddr=mBaseCtx->pe.mSectionsVector.back().VirtualAddress;
	STu8 *SecDecryptBuff=new STu8[SEC_PER_SIZE];
	FillMemory(SecDecryptBuff,SEC_PER_SIZE,0x90);
	for(int i=0;i<mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections;i++)
	{
		// -> do some special sections !
		CopyMemory(&SectionName1,mBaseCtx->pe.mSectionsVector[i].Name,4);
		CopyMemory(&SectionName2,mBaseCtx->pe.mSectionsVector[i].Name+4,4);
		if((  (SectionName1=='xet.')||				//.text
		      (SectionName1=='EDOC')||				//CODE
		      (SectionName1=='tad.')||				//.data
		      (SectionName1=='ATAD')||				//DATA
		      (SectionName1=='SSB' )||				//BSS
			  (SectionName1=='adr.')||				//.rdata
			 ((SectionName1=='ade.')&&(!OCXType))||	//.edata
			  (SectionName1=='adi.')||				//.idata
			//(SectionName1=='slt.')||				//.tls
			 ((SectionName1=='rsr.')&&(!OCXType))//.rsrc
			)&&
		   (mBaseCtx->pe.mSectionsVector[i].PointerToRawData!=0)&&
		   (mBaseCtx->pe.mSectionsVector[i].SizeOfRawData!=0))//-> skip also some other sections
		{
			switch(SectionName1)
			{
			case 'xet.':
			case 'EDOC':
				mPer.MyMakePER(SecDecryptBuff,SEC_PER_SIZE);
				dwDecOffset=(DWORD)&_patch3_CODEDecryptLoop-(DWORD)&_patch3_ShellCodeBegin_;
				CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff,SEC_PER_SIZE);
				break;
			case 'tad.':
			case 'ATAD':
				mPer.MyMakePER(SecDecryptBuff,SEC_PER_SIZE);
				dwDecOffset=(DWORD)&_patch3_DATADecryptLoop-(DWORD)&_patch3_ShellCodeBegin_;
				CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff,SEC_PER_SIZE);
				break;
			case 'adi.':
				mPer.MyMakePER(SecDecryptBuff,SEC_PER_SIZE);
				dwDecOffset=(DWORD)&_patch3_IDATADecryptLoop-(DWORD)&_patch3_ShellCodeBegin_;
				CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff,SEC_PER_SIZE);
				break;
			case 'ade.':
				mPer.MyMakePER(SecDecryptBuff,SEC_PER_SIZE);
				dwDecOffset=(DWORD)&_patch3_EDATADecryptLoop-(DWORD)&_patch3_ShellCodeBegin_;
				CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff,SEC_PER_SIZE);
				break;
			case 'rsr.':
				mPer.MyMakePER(SecDecryptBuff,RSRC_PER_SIZE);
				dwDecOffset=(DWORD)&_patch3_RSRCDecryptLoop-(DWORD)&_patch3_ShellCodeBegin_;
				CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff,RSRC_PER_SIZE);
				break;
			default:
				mPer.MyMakePER(SecDecryptBuff,SEC_PER_SIZE);
				dwDecOffset=(DWORD)&_patch3_SectionDecryptLoop-(DWORD)&_patch3_ShellCodeBegin_;
				CopyMemory(mBaseCtx->pVirMem+IT_SIZE+RvaToFoa(mRetAddr)+dwDecOffset,SecDecryptBuff,SEC_PER_SIZE);
				break;
			}
			//-> en-/decrypt it
			CryptSize=mBaseCtx->pe.mSectionsVector[i].SizeOfRawData;
			CryptStart=mBaseCtx->pe.mSectionsVector[i].PointerToRawData;
			if(SectionName1!='rsr.')
			{
				mPer.MyEasyEncrypt(mBaseCtx->pVirMem+CryptStart,CryptSize);
			}
			else
			{
				CryptResourceDirectory(mBaseCtx->pVirMem+CryptStart,mBaseCtx->pe.mSectionsVector[i].VirtualAddress,0);
			}
		} 	
	}
}

//----------------------------------------------------------------
// Base   = pointer to file memory
// dwMode: 0 - RawCrypt mode
//         1 - VirtualCrypt mode
void PeProtect::CompressPE()
{
	UCHAR *pIn		= NULL;
	UCHAR *pOut		= NULL;
	UCHAR *wrkmem	= NULL;
	DWORD		dwFsizeIn	= 0;
	DWORD		dwFsizeOut= 0;
	DWORD SectionName1,SectionName2;					
	DWORD SizeVirtualAllocate;
	DWORD dwDepackCodeVirtualSize=0;
	//修正头部
	char *pTmp=(char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	pTmp+=sizeof(NtHeader);
	for(int i=0;i<mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections;i++)
	{
		// -> do some special sections !
		CopyMemory(&SectionName1,mBaseCtx->pe.mSectionsVector[i].Name,4);
		CopyMemory(&SectionName2,mBaseCtx->pe.mSectionsVector[i].Name+4,4);
		if(((SectionName1=='xet.')||				//.text
		    (SectionName1=='EDOC')||				//CODE
		    (SectionName1=='tad.')||				//.data
		    (SectionName1=='ATAD')||				//DATA*/
		    (SectionName1=='SSB' )||				//BSS
			(SectionName1=='adr.')||				//.rdata
		   ((SectionName1=='ade.')&&(!OCXType))||	//.edata
			(SectionName1=='adi.')					//.idata
			//(SectionName1=='slt.')||				//.tls
			//(SectionName1=='rsr.')				//.rsrc
			)&&	
		   (mBaseCtx->pe.mSectionsVector[i].PointerToRawData!=0)&&
		   (mBaseCtx->pe.mSectionsVector[i].SizeOfRawData!=0))//-> skip also some other sections
		{
			//-> compress it
			if(SectionName1!='rsr.')
			{
				dwFsizeIn=mBaseCtx->pe.mSectionsVector[i].SizeOfRawData;
				switch(dwCompressType)
				{
				case 0:
				case 1:
					pIn=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn);
					pOut=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,aP_max_packed_size(dwFsizeIn));
					wrkmem=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,aP_workmem_size(dwFsizeIn));
					CopyMemory(pIn,mBaseCtx->pVirMem+mBaseCtx->pe.mSectionsVector[i].PointerToRawData,dwFsizeIn);
					if((pIn == NULL)||(pOut == NULL)||(wrkmem == NULL))
					{
						//return 0;
					}
					dwFsizeOut = aPsafe_pack(pIn, pOut, dwFsizeIn, wrkmem, 0);
					FillMemory(mBaseCtx->pVirMem+mBaseCtx->pe.mSectionsVector[i].PointerToRawData,dwFsizeIn,0x00);
					CopyMemory(mBaseCtx->pVirMem+mBaseCtx->pe.mSectionsVector[i].PointerToRawData,pOut,dwFsizeOut);
					break;
				}
				GlobalFree(wrkmem);
				GlobalFree(pOut);
				GlobalFree(pIn);   
			}
			else
			{
				dwFsizeOut=dwFsizeIn;
				CompressResourceDirectory(mBaseCtx->pVirMem+mBaseCtx->pe.mSectionsVector[i].PointerToRawData,
					mBaseCtx->pe.mSectionsVector[i].VirtualAddress,0);
			}
			/*if((SectionName1=='xet.')||	//.text
			   (SectionName1=='EDOC'))	//CODE
			{
				CODE_Size=dwFsizeIn;
			}
			if((SectionName1=='tad.')||	//.data
			   (SectionName1=='ATAD'))	//DATA
			{
				DATA_Size=dwFsizeIn;
			}
		    if(SectionName1=='SSB')		//BSS
			{
				BSS_Size=dwFsizeIn;
			}
			if(SectionName1=='adr.')//.rdata
			{
				RDATA_Size=dwFsizeIn;
			}
			if(SectionName1=='adi.')//.idata
			{
				IDATA_Size=dwFsizeIn;
			}
			if(SectionName1=='ade.')//.edata
			{
				EDATA_Size=dwFsizeIn;
			}
			if(SectionName1=='slt.')//.tls
			{
				TLS_Size=dwFsizeIn;
			}
		    if(SectionName1=='rsr.')	//.rsrc
			{
				RSRC_Size=dwFsizeIn;
			}*/
			//修正SizeOfRawData并记录最大的区块大小
			mBaseCtx->pe.mSectionsVector[i].SizeOfRawData=
			FileAlignmentSize(dwFsizeOut+4);
			SizeVirtualAllocate = mBaseCtx->pe.mSectionsVector[i].SizeOfRawData;
			SizeVirtualAllocate = SectionAlignmentSize(SizeVirtualAllocate + SizeVirtualAllocate / 64 + 16 + 3  + 4);
			if(dwDepackCodeVirtualSize<SizeVirtualAllocate) dwDepackCodeVirtualSize=SizeVirtualAllocate;
			((SectionHeader*)(pTmp))->SizeOfRawData=mBaseCtx->pe.mSectionsVector[i].SizeOfRawData;
		}
		pTmp+=sizeof(SectionHeader);
	}
	//修正最后一节大小
	mBaseCtx->pe.mSectionsVector.back().Misc.VirtualSize+=dwDepackCodeVirtualSize;
	mBaseCtx->pe.mSectionsVector.back().SizeOfRawData=SectionAlignmentSize(mBaseCtx->pe.mSectionsVector.back().Misc.VirtualSize);
	
	RebuiltSections();
	
}

void PeProtect::CryptResourceDirectory(STu8* Base,DWORD dwBaseRVA,DWORD dwRVA)
{
	DWORD i,dwOffSet;
	IMAGE_RESOURCE_DIRECTORY		directory;
	IMAGE_RESOURCE_DIRECTORY_ENTRY	directory_entries;
	IMAGE_RESOURCE_DATA_ENTRY		data_entry;
	CopyMemory(&directory,
		       Base+dwRVA,
			   sizeof(IMAGE_RESOURCE_DIRECTORY));

	for (i=0;i<directory.NumberOfIdEntries;i++)
	{
		CopyMemory(&directory_entries,
			       Base+dwRVA+sizeof(IMAGE_RESOURCE_DIRECTORY)+i*8,
				   sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));
		if(directory_entries.DataIsDirectory)
		{
			if((MAKEINTRESOURCE(directory_entries.Id)==RT_CURSOR		)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_BITMAP		)||
			   //(MAKEINTRESOURCE(directory_entries.Id)==RT_ICON		)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_MENU		)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_DIALOG		)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_STRING		)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_FONTDIR		)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_FONT		)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_ACCELERATOR	)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_RCDATA		)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_MESSAGETABLE)||
			   (MAKEINTRESOURCE(directory_entries.Id)==RT_GROUP_CURSOR)||
			   //(directory_entries.Id==RT_GROUP_ICON)||
			   //(directory_entries.Id==RT_VERSION		)||
			   (directory_entries.Id>32))
			{
				CryptResourceDirectory(Base,dwBaseRVA,directory_entries.OffsetToDirectory);
			}
		}
		else
		{
			CopyMemory(&data_entry,
						Base+directory_entries.OffsetToData,
						sizeof(IMAGE_RESOURCE_DATA_ENTRY));
			dwOffSet=data_entry.OffsetToData-dwBaseRVA;
			mPer.MyEasyEncrypt(Base+dwOffSet,data_entry.Size);
		}
	}
}
//----------------------------------------------------------------
void PeProtect::CompressResourceDirectory(STu8* Base,DWORD dwBaseRVA,DWORD dwRVA)
{
	//UCHAR *pIn		= NULL;
	//UCHAR *pOut		= NULL;
	//UCHAR *wrkmem	= NULL;
	//DWORD		dwFsizeIn	= 0;
	//DWORD 		dwFsizeOut	= 0;

	//DWORD i,dwOffSet;
	//IMAGE_RESOURCE_DIRECTORY		directory;
	//IMAGE_RESOURCE_DIRECTORY_ENTRY	directory_entries;
	//IMAGE_RESOURCE_DATA_ENTRY		data_entry;
	//CopyMemory(&directory,
	//	       Base+dwRVA,
	//		   sizeof(IMAGE_RESOURCE_DIRECTORY));

	//for (i=0;i<directory.NumberOfIdEntries;i++)
	//{
	//	CopyMemory(&directory_entries,
	//		       Base+dwRVA+sizeof(IMAGE_RESOURCE_DIRECTORY)+i*8,
	//			   sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));
	//	if(directory_entries.DataIsDirectory)
	//	{
	//		if((directory_entries.Id==ID_RT_CURSOR		)||
	//		   (directory_entries.Id==ID_RT_BITMAP		)||
	//		   //(directory_entries.Id==ID_RT_ICON		)||
	//		   (directory_entries.Id==ID_RT_MENU		)||
	//		   (directory_entries.Id==ID_RT_DIALOG		)||
	//		   (directory_entries.Id==ID_RT_STRING		)||
	//		   (directory_entries.Id==ID_RT_FONTDIR		)||
	//		   (directory_entries.Id==ID_RT_FONT		)||
	//		   (directory_entries.Id==ID_RT_ACCELERATOR	)||
	//		   (directory_entries.Id==ID_RT_RCDATA		)||
	//		   (directory_entries.Id==ID_RT_MESSAGETABLE)||
	//		   (directory_entries.Id==ID_RT_GROUP_CURSOR)||
	//		   //(directory_entries.Id==ID_RT_GROUP_ICON)||
	//		   //(directory_entries.Id==ID_RT_VERSION		)||
	//		   (directory_entries.Id>32))
	//		{
	//			CompressResourceDirectory(Base,dwBaseRVA,directory_entries.OffsetToDirectory);
	//		}
	//	}
	//	else
	//	{
	//		CopyMemory(&data_entry,
	//					Base+directory_entries.OffsetToData,
	//					sizeof(IMAGE_RESOURCE_DATA_ENTRY));
	//		dwOffSet=data_entry.OffsetToData-dwBaseRVA;
	//		//EncryptBuff(Base,dwOffSet,data_entry.Size);
	//		/*for(j=0;j<data_entry.Size;j++)
	//		{
	//			UCHAR tmp;
	//			
	//			CopyMemory(&tmp,Base+dwOffSet+j,1);
	//			tmp=tmp^0x55;
	//			CopyMemory(Base+dwOffSet+j,&tmp,1);
	//		}*/
	//		dwFsizeIn=data_entry.Size;
	//			switch(dwCompressType)
	//			{
	//			case 0:
	//				pIn=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn);
	//				pOut=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn + dwFsizeIn / 64 + 16 + 3  + 4);
	//				wrkmem=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,LZO1X_999_MEM_COMPRESS);
	//				CopyMemory(pIn,image_section[i],dwFsizeIn);
	//				if((pIn == NULL)||(pOut == NULL)||(wrkmem == NULL))
	//				{
	//					//return 0;
	//				}
	//				lzo_err = lzo1x_999_compress_level(
	//									 pIn,dwFsizeIn,
	//									 pOut,(lzo_uint*)&dwFsizeOut,wrkmem,
	//							         dict, dict_len, 0, lzo_level);
	//				FillMemory(image_section[i],dwFsizeIn,0x00);
	//				CopyMemory(image_section[i],pOut,dwFsizeOut);
	//				break;

	//			case 1:
	//				dwFsizeIn=image_section_header[i].SizeOfRawData;
	//				pIn=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn);
	//				pOut=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,aP_max_packed_size(dwFsizeIn));
	//				wrkmem=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,aP_workmem_size(dwFsizeIn));
	//				CopyMemory(pIn,image_section[i],dwFsizeIn);
	//				if((pIn == NULL)||(pOut == NULL)||(wrkmem == NULL))
	//				{
	//					//return 0;
	//				}
	//				dwFsizeOut = aPsafe_pack(pIn, pOut, dwFsizeIn, wrkmem, callback);
	//				FillMemory(image_section[i],dwFsizeIn,0x00);
	//				CopyMemory(image_section[i],pOut,dwFsizeOut);
	//				break;
	//			}
	//		GlobalFree(wrkmem);
	//		GlobalFree(pOut);
	//		GlobalFree(pIn);   
	//	}
	//}
}

void PeProtect::adjustSectionCharacteristics()
{
	char *pTmp=(char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	pTmp+=sizeof(NtHeader);
	for(int i=0;i<mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections;i++)
	{
		mBaseCtx->pe.mSectionsVector[i].Characteristics|=(IMAGE_SCN_CNT_INITIALIZED_DATA|IMAGE_SCN_CNT_CODE|IMAGE_SCN_MEM_EXECUTE|IMAGE_SCN_MEM_READ|IMAGE_SCN_MEM_WRITE);
		((SectionHeader*)(pTmp))->Characteristics=mBaseCtx->pe.mSectionsVector[i].Characteristics;
		pTmp+=sizeof(SectionHeader);
	}
}

void PeProtect::RemoveSectionNames()
{
	char szName[9];
	int i;
	szName[8]=0;
	for(i=0;i<mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections;i++)
	{
		CopyMemory(&SectionNames[i],mBaseCtx->pe.mSectionsVector[i].Name,8);
	}
	char *pTmp=(char*)mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew;
	pTmp+=sizeof(NtHeader);
	for(i=0;i<mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections-1;i++)
	{
		CopyMemory(szName,mBaseCtx->pe.mSectionsVector[i].Name,8);
		if(strcmp(szName,".rsrc")!=0)
		{
			FillMemory(mBaseCtx->pe.mSectionsVector[i].Name,8,0x00);
			FillMemory(pTmp,8,0x00);
		}
		pTmp+=sizeof(SectionHeader);
	}
}

DWORD PeProtect::PreAllocateVariable(STu8* Base)
{
	DWORD l;
	//----- PRE LOADER VARIABLES -----
	DWORD dwRO = 0;

	//szKernel32					DB "Kernel32.dll",0
	l=DWORD(strlen(szKernel32))+1;
	dwRO_szKernel32=dwRO;
	CopyMemory(Base+dwRO,szKernel32,l);
	dwRO = dwRO + l;

	//szGetModuleHandle				DB "GetModuleHandleA",0
	l=DWORD(strlen(szGetModuleHandle))+1;
	dwRO_szGetModuleHandle=dwRO;
	CopyMemory(Base+dwRO,szGetModuleHandle,l);
	dwRO = dwRO + l;

	//szVirtualProtect				DB "VirtualProtect",0
	l=DWORD(strlen(szVirtualProtect))+1;
	dwRO_szVirtualProtect=dwRO;
	CopyMemory(Base+dwRO,szVirtualProtect,l);
	dwRO = dwRO + l;

	//szGetModuleFileName			DB "GetModuleFileNameA",0
	l=DWORD(strlen(szGetModuleFileName))+1;
	dwRO_szGetModuleFileName=dwRO;
	CopyMemory(Base+dwRO,szGetModuleFileName,l);
	dwRO = dwRO + l;

	//szCreateFile					DB "CreateFileA",0
	l=DWORD(strlen(szCreateFile))+1;
	dwRO_szCreateFile=dwRO;
	CopyMemory(Base+dwRO,szCreateFile,l);
	dwRO = dwRO + l;

	//szGlobalAlloc					DB "GlobalAlloc",0
	l=DWORD(strlen(szGlobalAlloc))+1;
	dwRO_szGlobalAlloc=dwRO;
	CopyMemory(Base+dwRO,szGlobalAlloc,l);
	dwRO = dwRO + l;

	//szGlobalFree					DB "GlobalFree",0
	l=DWORD(strlen(szGlobalFree))+1;
	dwRO_szGlobalFree=dwRO;
	CopyMemory(Base+dwRO,szGlobalFree,l);	
	dwRO = dwRO + l;

	//szReadFile					DB "ReadFile",0
	l=DWORD(strlen(szReadFile))+1;
	dwRO_szReadFile=dwRO;
	CopyMemory(Base+dwRO,szReadFile,l);
	dwRO = dwRO + l;

	//szGetFileSize					DB "GetFileSize",0
	l=DWORD(strlen(szGetFileSize))+1;
	dwRO_szGetFileSize=dwRO;
	CopyMemory(Base+dwRO,szGetFileSize,l);
	dwRO = dwRO + l;

	//szCloseHandle					DB "CloseHandle",0
	l=DWORD(strlen(szCloseHandle))+1;
	dwRO_szCloseHandle=dwRO;
	CopyMemory(Base+dwRO,szCloseHandle,l);
	dwRO = dwRO + l;

	//szIsDebuggerPresent			DB "IsDebuggerPresent",0
	l=DWORD(strlen(szIsDebuggerPresent))+1;
	dwRO_szIsDebuggerPresent=dwRO;
	CopyMemory(Base+dwRO,szIsDebuggerPresent,l);
	dwRO = dwRO + l;

	//szCreateToolhelp32Snapshot	DB "CreateToolhelp32Snapshot",0
	l=DWORD(strlen(szCreateToolhelp32Snapshot))+1;
	dwRO_szCreateToolhelp32Snapshot=dwRO;
	CopyMemory(Base+dwRO,szCreateToolhelp32Snapshot,l);
	dwRO = dwRO + l;

	//szGetCurrentProcessId			DB "GetCurrentProcessId",0
	l=DWORD(strlen(szGetCurrentProcessId))+1;
	dwRO_szGetCurrentProcessId=dwRO;
	CopyMemory(Base+dwRO,szGetCurrentProcessId,l);
	dwRO = dwRO + l;

	//szProcess32First				DB "Process32First",0
	l=DWORD(strlen(szProcess32First))+1;
	dwRO_szProcess32First=dwRO;
	CopyMemory(Base+dwRO,szProcess32First,l);
	dwRO = dwRO + l;

	//szProcess32Next				DB "Process32Next",0
	l=DWORD(strlen(szProcess32Next))+1;
	dwRO_szProcess32Next=dwRO;
	CopyMemory(Base+dwRO,szProcess32Next,l);
	dwRO = dwRO + l;

	//szModule32First				DB "Module32First",0
	l=DWORD(strlen(szModule32First))+1;
	dwRO_szModule32First=dwRO;
	CopyMemory(Base+dwRO,szModule32First,l);
	dwRO = dwRO + l;

	//szModule32Next				DB "Module32Next",0
	l=DWORD(strlen(szModule32Next))+1;
	dwRO_szModule32Next=dwRO;
	CopyMemory(Base+dwRO,szModule32Next,l);
	dwRO = dwRO + l;

	//szOpenProcess					DB "OpenProcess",0
	l=DWORD(strlen(szOpenProcess))+1;
	dwRO_szOpenProcess=dwRO;
	CopyMemory(Base+dwRO,szOpenProcess,l);
	dwRO = dwRO + l;

	//szTerminateProcess			DB "TerminateProcess",0
	l=DWORD(strlen(szTerminateProcess))+1;
	dwRO_szTerminateProcess=dwRO;
	CopyMemory(Base+dwRO,szTerminateProcess,l);
	dwRO = dwRO + l;

	//szExitThread					DB "ExitThread",0
	l=DWORD(strlen(szExitThread))+1;
	dwRO_szExitThread=dwRO;
	CopyMemory(Base+dwRO,szExitThread,l);
	dwRO = dwRO + l;

	//szExitProcess					DB "ExitProcess",0
	l=DWORD(strlen(szExitProcess))+1;
	dwRO_szExitProcess=dwRO;
	CopyMemory(Base+dwRO,szExitProcess,l);
	dwRO = dwRO + l;

	//szGetWindowsDirectory		DB "GetWindowsDirectoryA",0
	l=DWORD(strlen(szGetWindowsDirectory))+1;
	dwRO_szGetWindowsDirectory=dwRO;
	CopyMemory(Base+dwRO,szGetWindowsDirectory,l);
	dwRO = dwRO + l;

	//szCreateWindow		DB "CreateWindowA",0
	l=DWORD(strlen(szCreateWindow))+1;
	dwRO_szCreateWindow=dwRO;
	CopyMemory(Base+dwRO,szCreateWindow,l);
	dwRO = dwRO + l;

	//szGetCurrentThread	DB "GetCurrentThread",0
	l=DWORD(strlen(szGetCurrentThread))+1;
	dwRO_szGetCurrentThread=dwRO;
	CopyMemory(Base+dwRO,szGetCurrentThread,l);
	dwRO = dwRO + l;

	//szSetThreadPriority	DB "SetThreadPriority",0
	l=DWORD(strlen(szSetThreadPriority))+1;
	dwRO_szSetThreadPriority=dwRO;
	CopyMemory(Base+dwRO,szSetThreadPriority,l);
	dwRO = dwRO + l;

	//szSuspendThread	DB "SuspendThread",0
	l=DWORD(strlen(szSuspendThread))+1;
	dwRO_szSuspendThread=dwRO;
	CopyMemory(Base+dwRO,szSuspendThread,l);
	dwRO = dwRO + l;

	//szResumeThread		DB "ResumeThread	",0
	l=DWORD(strlen(szResumeThread))+1;
	dwRO_szResumeThread=dwRO;
	CopyMemory(Base+dwRO,szResumeThread,l);
	dwRO = dwRO + l;

	//szUser32				DB "User32.dll",0
	l=DWORD(strlen(szUser32))+1;
	dwRO_szUser32=dwRO;
	CopyMemory(Base+dwRO,szUser32,l);
	dwRO = dwRO + l;

	//szWaitForInputIdle	DB "WaitForInputIdle",0
	l=DWORD(strlen(szWaitForInputIdle))+1;
	dwRO_szWaitForInputIdle=dwRO;
	CopyMemory(Base+dwRO,szWaitForInputIdle,l);
	dwRO = dwRO + l;

	//dwRO = dwRO + 5;
	//_LoadLibrary					DD 0
	dwRO_LoadLibrary		= dwRO;
	CopyMemory(Base+dwRO,&_LoadLibrary,4);
	dwRO = dwRO + 4;

	//_GetProcAddress				DD 0
	dwRO_GetProcAddress	= dwRO;
	CopyMemory(Base+dwRO,&_GetProcAddress,4);
	dwRO = dwRO + 4;

	//dwKernelBase					DD 0
	dwRO_dwKernelBase=dwRO;
	CopyMemory(Base+dwRO,&dwKernelBase ,4);
	dwRO = dwRO + 4;

	//_GetModuleHandle				DD 0
	dwRO_GetModuleHandle=dwRO;
	CopyMemory(Base+dwRO,&_GetModuleHandle,4);
	dwRO = dwRO + 4;

	//_VirtualProtect				DD 0
	dwRO_VirtualProtect=dwRO;
	CopyMemory(Base+dwRO,&_VirtualProtect,4);
	dwRO = dwRO + 4;

	//dwOrgEntryPoint_Shade			DD 0
	dwRO_dwOrgEntryPoint_Shade=dwRO;
	CopyMemory(Base+dwRO,&dwOrgEntryPoint_Shade,4);
	dwRO = dwRO + 4;

	//_GetModuleFileName			DD 0
	dwRO_GetModuleFileName=dwRO;
	CopyMemory(Base+dwRO,&_GetModuleFileName,4);
	dwRO = dwRO + 4;

	//_CreateFile					DD 0
	dwRO_CreateFile=dwRO;
	CopyMemory(Base+dwRO,&_CreateFile,4);
	dwRO = dwRO + 4;

	//_GlobalAlloc					DD 0
	dwRO_GlobalAlloc=dwRO;
	CopyMemory(Base+dwRO,&_GlobalAlloc,4);
	dwRO = dwRO + 4;

	//_GlobalFree					DD 0
	dwRO_GlobalFree=dwRO;
	CopyMemory(Base+dwRO,&_GlobalFree,4);
	dwRO = dwRO + 4;

	//_ReadFile						DD 0
	dwRO_ReadFile=dwRO;
	CopyMemory(Base+dwRO,&_ReadFile,4);
	dwRO = dwRO + 4;

	//_GetFileSize					DD 0
	dwRO_GetFileSize=dwRO;
	CopyMemory(Base+dwRO,&_GetFileSize,4);
	dwRO = dwRO + 4;

	//_CloseHandle					DD 0
	dwRO_CloseHandle=dwRO;
	CopyMemory(Base+dwRO,&_CloseHandle,4);
	dwRO = dwRO + 4;

	//_IsDebuggerPresent			DD 0
	dwRO_IsDebuggerPresent=dwRO;
	CopyMemory(Base+dwRO,&_IsDebuggerPresent,4);
	dwRO = dwRO + 4;

	//_CreateToolhelp32Snapshot		DD 0
	dwRO_CreateToolhelp32Snapshot=dwRO;
	CopyMemory(Base+dwRO,&_CreateToolhelp32Snapshot,4);
	dwRO = dwRO + 4;

	//_GetCurrentProcessId			DD 0
	dwRO_GetCurrentProcessId=dwRO;
	CopyMemory(Base+dwRO,&_GetCurrentProcessId,4);
	dwRO = dwRO + 4;

	//_Process32First				DD 0
	dwRO_Process32First=dwRO;
	CopyMemory(Base+dwRO,&_Process32First,4);
	dwRO = dwRO + 4;

	//_Process32Next				DD 0
	dwRO_Process32Next=dwRO;
	CopyMemory(Base+dwRO,&_Process32Next,4);
	dwRO = dwRO + 4;

	//_Module32First				DD 0
	dwRO_Module32First=dwRO;
	CopyMemory(Base+dwRO,&_Module32First,4);
	dwRO = dwRO + 4;

	//_Module32Next					DD 0
	dwRO_Module32Next=dwRO;
	CopyMemory(Base+dwRO,&_Module32Next,4);
	dwRO = dwRO + 4;

	//_OpenProcess					DD 0
	dwRO_OpenProcess=dwRO;
	CopyMemory(Base+dwRO,&_OpenProcess,4);
	dwRO = dwRO + 4;

	//_TerminateProcess				DD 0
	dwRO_TerminateProcess=dwRO;
	CopyMemory(Base+dwRO,&_TerminateProcess,4);
	dwRO = dwRO + 4;

	//_ExitThread					DD 0
	dwRO_ExitThread=dwRO;
	CopyMemory(Base+dwRO,&_ExitThread,4);
	dwRO = dwRO + 4;

	//_ExitProcess					DD 0
	dwRO_ExitProcess=dwRO;
	CopyMemory(Base+dwRO,&_ExitProcess,4);
	dwRO = dwRO + 4;

	//_GetWindowsDirectory			DD 0
	dwRO_GetWindowsDirectory=dwRO;
	CopyMemory(Base+dwRO,&_GetWindowsDirectory,4);
	dwRO = dwRO + 4;

	//_CreateWindow					DD 0
	dwRO_CreateWindow=dwRO;
	CopyMemory(Base+dwRO,&_CreateWindow,4);
	dwRO = dwRO + 4;

	//_GetCurrentThread				DD 0
	dwRO_GetCurrentThread=dwRO;
	CopyMemory(Base+dwRO,&_GetCurrentThread,4);
	dwRO = dwRO + 4;

	//_SetThreadPriority			DD 0
	dwRO_SetThreadPriority=dwRO;
	CopyMemory(Base+dwRO,&_SetThreadPriority,4);
	dwRO = dwRO + 4;

	//_SuspendThread				DD 0
	dwRO_SuspendThread=dwRO;
	CopyMemory(Base+dwRO,&_SuspendThread,4);
	dwRO = dwRO + 4;

	//_ResumeThread					DD 0
	dwRO_ResumeThread=dwRO;
	CopyMemory(Base+dwRO,&_ResumeThread,4);
	dwRO = dwRO + 4;

	//_WaitForInputIdle			DD 0
	dwRO_WaitForInputIdle=dwRO;
	CopyMemory(Base+dwRO,&_WaitForInputIdle,4);
	dwRO = dwRO + 4;

	return(dwRO);
}

void PeProtect::PosAllocateVariable(STu8* Base,DWORD mOffset)
{
	//----- POST LOADER VARIABLES -----
	DWORD dwRO=mOffset;
		
	//dwRO_dwCompressType			DB 0
	dwRO_dwCompressType= dwRO;
	CopyMemory(Base+dwRO,&dwCompressType,4);

	//dwDEPACKER_SECTION_NAME		DB'Cy'
	dwRO = dwRO + 4;
	dwRO_dwDEPACKER_SECTION_NAME= dwRO;
	CopyMemory(Base+dwRO,&dwDEPACKER_SECTION_NAME,4);

	//dwImageBase					DD 0
	dwRO = dwRO + 4;
	dwRO_dwImageBase		= dwRO;
	CopyMemory(Base+dwRO,&dwImageBase,4);

	//dwCalcedCRC					DD 0
	dwRO = dwRO + 4;
	dwRO_dwCalcedCRC		= dwRO;
	CopyMemory(Base+dwRO,&dwCalcedCRC,4);

	//dwParentProcess				DD 0
	dwRO = dwRO + 4;
	dwRO_dwParentProcess	= dwRO;
	CopyMemory(Base+dwRO,&dwParentProcess,4);

	//IIDInfo  db (SIZEOF sItInfo * MAX_IID_NUM) dup (0)
	dwRO = dwRO + 4;
	dwRO_IIDInfo			= dwRO;
	CopyMemory(Base+dwRO,&IIDInfo,sizeof(IIDInfo));

	//SEH							sSEH <0>
	dwRO = dwRO +sizeof(IIDInfo);
	dwRO_SEH			= dwRO;
	CopyMemory(Base+dwRO,&SEH,sizeof(sSEH));

	//PROTECTION_FLAGS				DD 0
	dwRO = dwRO +sizeof(sSEH);
	dwRO_PROTECTION_FLAGS	= dwRO;
	CopyMemory(Base+dwRO,&PROTECTION_FLAGS,4);

	//dwLoaderCRC					DD 0
	dwRO = dwRO + 4;
	dwRO_dwLoaderCRC		= dwRO;
	CopyMemory(Base+dwRO,&dwLoaderCRC,4);

	//bNT							DD 0
	dwRO = dwRO + 4;
	dwRO_bNT				= dwRO;
	CopyMemory(Base+dwRO,&bNT,4);

	//SectionName[MAX_SECTION_NUM]	DB <0>
	dwRO = dwRO +4;
	dwRO_SectionNames		= dwRO;
	CopyMemory(Base+dwRO,&SectionNames,sizeof(SectionNames));

	//dwOrgEntryPoint				DD 0
	dwRO = dwRO + sizeof(SectionNames);
	dwRO_dwOrgEntryPoint	= dwRO;
	dwOrgEntryPoint=dwOrgEntryPoint^'dane';
	PER::_ror(&dwOrgEntryPoint,0x10);
	CopyMemory(Base+dwRO,&dwOrgEntryPoint,4);

	//CODE_Size						DD 0	
	dwRO = dwRO + 4;
	dwRO_CODE_Size =dwRO;
	CopyMemory(Base+dwRO,&CODE_Size,4);

	//DATA_Size						DD 0
	dwRO = dwRO + 4;
	dwRO_DATA_Size =dwRO;
	CopyMemory(Base+dwRO,&DATA_Size,4);

	//BSS_Size						DD 0
	dwRO = dwRO + 4;
	dwRO_BSS_Size =dwRO;
	CopyMemory(Base+dwRO,&BSS_Size,4);

	//RDATA_Size					DD 0
	dwRO = dwRO + 4;
	dwRO_RDATA_Size =dwRO;
	CopyMemory(Base+dwRO,&RDATA_Size,4);

	//IDATA_Size					DD 0
	dwRO = dwRO + 4;
	dwRO_IDATA_Size =dwRO;
	CopyMemory(Base+dwRO,&IDATA_Size,4);

	//EDATA_Size					DD 0
	dwRO = dwRO + 4;
	dwRO_EDATA_Size =dwRO;
	CopyMemory(Base+dwRO,&EDATA_Size,4);
	
	//TLS_Size						DD 0
	dwRO = dwRO + 4;
	dwRO_TLS_Size =dwRO;
	CopyMemory(Base+dwRO,&TLS_Size,4);

	//RSRC_Size						DD 0
	dwRO = dwRO + 4;
	dwRO_RSRC_Size =dwRO;
	CopyMemory(Base+dwRO,&RSRC_Size,4);

	//dwRO_RelocRVA					DD 0
	dwRO = dwRO + 4;
	dwRO_RelocRVA =dwRO;
	CopyMemory(Base+dwRO,&RelocRVA,4);

	//dwRO_RelocRVA					DD 0
	dwRO = dwRO + 4;
	dwRO_RelocSize =dwRO;
	CopyMemory(Base+dwRO,&RelocSize,4);

	//EXPLORER_EXE					DB "EXPLORER.EXE",0
	dwRO = dwRO + 4;
	dwRO_EXPLORER_EXE=dwRO;
	CopyMemory(Base+dwRO,EXPLORER_EXE,DWORD(strlen(EXPLORER_EXE))+1);

	//szSoftICE95					DB "\\\\.\\SICE",0
	dwRO = dwRO + DWORD(strlen(EXPLORER_EXE))+1;
	dwRO_szSoftICE95=dwRO;
	CopyMemory(Base+dwRO,szSoftICE95,DWORD(strlen(szSoftICE95))+1);

	//szSoftICENT					DB "\\\\.\\NTICE",0
	dwRO = dwRO + DWORD(strlen(szSoftICE95))+1;
	dwRO_szSoftICENT=dwRO;
	CopyMemory(Base+dwRO,szSoftICENT,DWORD(strlen(szSoftICENT))+1);

	//TlsBackup						IMAGE_TLS_DIRECTORY32 <0>
	dwRO = dwRO + DWORD(strlen(szSoftICENT))+1;
	dwRO_TlsBackup =dwRO;
	CopyMemory(Base+dwRO,&TlsBackup,sizeof(IMAGE_TLS_DIRECTORY32));

	//RlocBackup					IMAGE_BASE_RELOCATION <0>
	dwRO = dwRO + sizeof(IMAGE_TLS_DIRECTORY32);
	dwRO_RlocBackup =dwRO;
	CopyMemory(Base+dwRO,&RlocBackup,sizeof(IMAGE_BASE_RELOCATION));

	//dwOrgChecksumSize				DD 0
	dwRO = dwRO +sizeof(IMAGE_BASE_RELOCATION);
	dwRO_dwOrgChecksum =dwRO;
	CopyMemory(Base+dwRO,&dwOrgChecksumSize,4);

	//dwOrgChecksum					DD 0
	dwRO = dwRO + 4;
	dwRO_dwOrgChecksum =dwRO;
	CopyMemory(Base+dwRO,&dwOrgChecksum,4);

	//Temp1							DD 0
	dwRO = dwRO + 4;
	dwRO_Temp1 =dwRO;
	FillMemory(Base+dwRO,4,0x00);

	//Temp2							DD 0
	dwRO = dwRO + 4;
	dwRO_Temp2 =dwRO;
	FillMemory(Base+dwRO,4,0x00);

	//BuffSize						DD 0	
	dwRO = dwRO + 4;
	dwRO_BuffSize =dwRO;
	CopyMemory(Base+dwRO,&BuffSize,4);

	//Buff							DB 0	
	dwRO = dwRO + 4;
	dwRO_Buff =dwRO;
	FillMemory(Base+dwRO,4,0x00);
}

DWORD PeProtect::GetCallOpCodeRandom()
{
	DWORD dwRandom=mPer.random(9);
	switch(dwRandom)
	{
	case 0:return(0xE801EB);break;// Self modifing
	case 1:return(0xE901EB);break;// Self modifing
	case 2:return(0xC201EB);break;// Self modifing

	case 3:return(0xE801EB);break;// Self modifing
	case 4:return(0xE901EB);break;// Self modifing
	case 5:return(0xC201EB);break;// Self modifing

	case 6:return(0xE801EB);break;// Self modifing
	case 7:return(0xE901EB);break;// Self modifing
	case 8:return(0xC201EB);break;// Self modifing

	case 9:return(0xE801EB);break;// Self modifing
	}
	return(0x909090);
}

//----- CONST ----
// all opcodes are in reverse order
struct sShitStruct{
	DWORD dwSize;
	DWORD dwShitOpCode;
}; 
//----- EQUs -----
#define ShitItems	12
const sShitStruct ShitTable[ShitItems]={
	{0x01,
	 0x90},		// NOP		   

	{0x01,
	 0xF9},		// STC
	   
	{0x01,
	 0xF8},		// CLC

	{0x03,
	 0xE801EB},	// Self modifing
	   
	{0x03,
	 0xE901EB},	// Self modifing
	   
	{0x03,
	 0xC201EB},	// Self modifing

	{0x03,
	 0xE801EB},	// Self modifing
   
	{0x03,
	 0xE901EB},	// Self modifing
		   
	{0x03,
	 0xC201EB},	// Self modifing

	{0x03,
	 0xE801EB},	// Self modifing
	   
	{0x03,
	 0xE901EB},	// Self modifing	   

	{0x03,
	 0xC201EB}	// Self modifing
};

//----------------------------------------------------------------
void PeProtect::FillWithShit(STu8* Base,DWORD dwSize)
{
	DWORD dwRandom;
	DWORD _dwSize=dwSize;
	sShitStruct shittable;
	DWORD dwPos=0;
	do
	{
		// get a random Shit Item
		dwRandom=mPer.random(ShitItems);
		shittable=ShitTable[dwRandom];
		if(shittable.dwSize<=_dwSize)// check if this item is too big
		{
			//---- past the Opcode ----
			CopyMemory(Base+dwPos,&shittable.dwShitOpCode,shittable.dwSize);
			dwPos= dwPos + shittable.dwSize;
			_dwSize=_dwSize-shittable.dwSize;
		}
	}while(_dwSize!=0);
}

void PeProtect::CrypterPackerwithCall(STu8* pFuncBody,DWORD dwSize)
{
#ifndef DebugMode
	DWORD l=0;
	DWORD64 tmp,tmp1;
	do
	{
		CopyMemory(&tmp,pFuncBody+l,8);
		if(tmp==0x9090909090909090)
		{
			tmp=0x00000003E8;
			tmp1=GetCallOpCodeRandom();
			tmp1=tmp1<<40;
			tmp=tmp|tmp1;
			CopyMemory(pFuncBody+l,&tmp,8);
			l += 8;
		}
		else
			l++;
	}while(l<=dwSize);
#endif
}

DWORD PeProtect::GetChecksum(STu8* Base,DWORD FileSize)
{
	DWORD	checksum,dwhold,dwdata;
	DWORD64 dwtemp64;
	UCHAR	_temp;
	checksum=dwhold=0;
	for(DWORD i=0;i<FileSize;i++)
	{
		CopyMemory(&_temp,Base+i,1);
		dwtemp64=_temp*dwhold;
		dwdata=DWORD(dwtemp64);
		dwtemp64=dwtemp64>>32;
		dwhold=DWORD(dwtemp64);
		checksum=checksum+dwdata;
		dwhold++;
	}
	return(checksum);
}

//return Raw Data address of Loader Crypter Codes
void PeProtect::GetEncryptRO(STu8* pFuncBody)
{
}

//return Raw Data address of OEP JUMP Codes
void PeProtect::GetOepJumpCodeRO(STu8* pFuncBody)
{
}

// This functin encryptes the OEP JUMP Codes
void PeProtect::OepJumpEncrypt(STu8* Base)
{
	//DWORD i;
	//UCHAR _temp=0;
	//UCHAR _tempC=UCHAR(OEP_JUMP_CODE_SIZE);
	//for(i=dwRO_OEP_JUMP_CODE_START;i<=dwRO_OEP_JUMP_CODE_END;i++)
	//{
	//	CopyMemory(&_temp,Base+i,1);
	//	_asm
	//	{
	//		MOV AL,_temp
 //  			ROR  AL, 2
 //  			ADD  AL, _tempC
 //  			XOR  AL, OEP_JUMP_ENCRYPT_NUM	
	//		MOV _temp,AL
	//		DEC _tempC
	//	}
	//	CopyMemory(Base+i,&_temp,1);
	//}
}


//test dis
bool PeProtect::TestDis()
{
	DWORD dwOEPVirAddress=0;
	DWORD dwBaseCodeVirAddress=0;
	DWORD dwCodeSize=0;
	DWORD dwMode=0;

	dwOEPVirAddress=mBaseCtx->pe.mNtHeader.OptionalHeader.AddressOfEntryPoint;
	dwBaseCodeVirAddress=mBaseCtx->pe.mNtHeader.OptionalHeader.BaseOfCode;
	dwCodeSize=mBaseCtx->pe.mNtHeader.OptionalHeader.SizeOfCode;

	//判断机器位数
#ifdef PE_MODEL
	dwMode=32;
#else
	dwMode=64;//暂不支持
#endif

	char *pCode = (char *)mBaseCtx->pVirMem+RvaToFoa(dwOEPVirAddress);
	dwOEPVirAddress+=mBaseCtx->pe.mNtHeader.OptionalHeader.ImageBase;
	dwBaseCodeVirAddress+=mBaseCtx->pe.mNtHeader.OptionalHeader.ImageBase;

	CCodeILFactory codefactory;
	map<DWORD,CFunctionCode*> mFuncMap;
	codefactory.Init(mBaseCtx->pe.mNtHeader.OptionalHeader.ImageBase+GetNewSection(),dwCodeSize);
	codefactory.RecursiveScanFunctionDisasmCodes(mFuncMap,pCode,dwCodeSize,dwOEPVirAddress,dwBaseCodeVirAddress);
	pCode=(char *)mBaseCtx->pVirMem+RvaToFoa(dwBaseCodeVirAddress-mBaseCtx->pe.mNtHeader.OptionalHeader.ImageBase);
	codefactory.SeqScanByFuncCharacteristicDisasmCodes(mFuncMap,pCode,dwCodeSize,dwBaseCodeVirAddress);
	return true;
}