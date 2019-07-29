#include"../PELib.h"
#include "PeClass.h"
#include"../VM/CryptErr.h"
#include"../mem.h"
#include<vector>

PeClass::PeClass(void)
{
	isAnalysised=false;
	InitCtx(*mBaseCtx);
}
PeClass::PeClass(pe_ctx_t &_ctx)
{
	mBaseCtx=&_ctx;
	isAnalysised=false;
	InitCtx(*mBaseCtx);
}
PeClass::~PeClass(void)
{
	ClsCtx(*mBaseCtx);
}

void PeClass::InitCtx(pe_ctx_t& mC)
{
	mC.pVirMem=0;
	mC.size=0;
	mC.path.clear();
}

void PeClass::ClsCtx(pe_ctx_t& mC)
{
	if (mC.pVirMem)
	{
		WZHMem::SGIVirtualDeallocate(mC.pVirMem, mC.size);
		mC.pVirMem = 0;
		mC.size = 0;
		mC.path.clear();
		mC.pe.mDosHeader;
		mC.pe.mNtHeader;
		mC.pe.wMagic;
		mC.pe.mSectionsVector.clear();
		mC.pe.mExport;
		mC.pe.mImportsVector.clear();
		mC.pe.mRelocsVector.clear();
		mC.pe.mResourcesVector.clear();
		mC.pe.mDelaysVector.clear();
		mC.pe.mTlsDirrctory;
		mC.pe.mLoadConfigDirctory;
		mC.pe.mBoundsVector.clear();
		mC.pe.mDebugDirectorysVector.clear();
		mC.pe.mOverlay;
	}
}

void PeClass::CopyPeCtx(pe_ctx_t & mNewCtx,const pe_ctx_t& mOldCtx)
{
	ClsCtx(mNewCtx);
	mNewCtx.path=mOldCtx.path;
	mNewCtx.size=mOldCtx.size;
	mNewCtx.pVirMem=WZHMem::SGIVirtualAlloc(mOldCtx.size);
	CopyMemory(mNewCtx.pVirMem,mOldCtx.pVirMem,mOldCtx.size);
	mNewCtx.pe=mOldCtx.pe;//(浅拷贝可能出现问题)
}

bool PeClass::PeLoadFile(const char *path,const char *model)
{
	if(!PathFileExists(path))
	{
		ShowErr(FileErr);
		return false;
	}
	mBaseCtx->path = path;
	HANDLE mHandle=CreateFile(mBaseCtx->path.c_str(),GENERIC_READ,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(INVALID_HANDLE_VALUE==mHandle)
	{
		ShowErr(FileErr);
		return false;
	}

	DWORD dwSizeHigh =0,dwSizeLow =0;
	dwSizeLow=GetFileSize(mHandle,&dwSizeHigh);
	if(dwSizeLow==INVALID_FILE_SIZE||dwSizeHigh!=0)
	{
		CloseHandle(mHandle);
		ShowErr(FsizeErr);
		return false;
	}

	mBaseCtx->size=dwSizeLow;

	mBaseCtx->pVirMem=WZHMem::SGIVirtualAlloc(mBaseCtx->size);
	if(mBaseCtx->pVirMem==NULL) 
	{
		CloseHandle(mHandle);
		ShowErr(MemErr);
		return false;
	}

	DWORD readsize;
	if(!ReadFile(mHandle,mBaseCtx->pVirMem,mBaseCtx->size,&readsize,NULL))
	{
		CloseHandle(mHandle);
		return false;
	}
	CloseHandle(mHandle);
	//读取基本PE头
	CopyMemory(&mBaseCtx->pe.mDosHeader,mBaseCtx->pVirMem,sizeof(DosHeader));

	//判断CPU字长
	DWORD dwVirtualAddress=mBaseCtx->pe.mDosHeader.e_lfanew;
	dwVirtualAddress+=sizeof(DWORD)+sizeof(IMAGE_FILE_HEADER);
	CopyMemory(&mBaseCtx->pe.wMagic,mBaseCtx->pVirMem+dwVirtualAddress,sizeof(WORD));
	if(mBaseCtx->pe.wMagic==IMAGE_NT_OPTIONAL_HDR64_MAGIC) return false;         //64位暂不支持
	CopyMemory(&mBaseCtx->pe.mNtHeader,
		       mBaseCtx->pVirMem+mBaseCtx->pe.mDosHeader.e_lfanew,
			   sizeof(NtHeader));
	return true;
}

bool PeClass::PeUnload()
{
	ClsCtx(*mBaseCtx);
	isAnalysised=false;
	return true;
}

void PeClass::LoadMap(char* pmapfilename) 
{
	if( !pmapfilename )
		return;
	FILE* mapfile = NULL;
	mapfile = fopen(pmapfilename,"r+"); //打开MAP FILE处理
	if( !mapfile )
		return;

	FreeMapVector();

	char linestr[512] = {0};            //行数据
	int  readcnt = 0;                   //读的行数
	BOOL bBegin = FALSE;                //开始
	while(!feof(mapfile))
	{
		memset(linestr,0,512);
		if(fgets(linestr,512,mapfile) == NULL) //读一行，最多读512个字节
		{
			break;
		}
		readcnt++; //计算读了多少行
		if( strstr(linestr,"entry point at") != NULL )
		{
			continue;
		}
		if( strstr(linestr,"Line numbers for") != NULL )//行号就不看了
		{
			break;
		}
		if( ( strstr(linestr,"Publics by Value") != NULL && strstr(linestr,"Rva+Base") != NULL ) ||
			( strstr(linestr,"Static symbols") != NULL ) )//开始搜索符号
		{
			bBegin = TRUE;
			continue;
		}
		char StrLine[512] = {0};
		if( !Trim(linestr,StrLine) )//是空行读下一行
		{
			continue;
		}
		if( bBegin )//开始处理
		{
			char StrAddress[16] = {0};//段:偏移
			char StrSymbol[512] = {0};//符号名
			char StrVirtualAddr[16] = {0};//线性地址
			char StrLibObject[512] = {0};//输入文件名
			int Segment = 0;
			int FileOffset = 0;

			memcpy(StrAddress,StrLine,13);
			int nstrlen = strlen(StrLine);
			memmove(StrLine,StrLine+13,nstrlen - 13 + 1);//跳过段偏移

			GetFileAddr(StrAddress,&Segment,&FileOffset);//得到段和偏移
			if( Segment == 0 )//段为0不算
				continue;

			Trim(StrLine,StrLine);
			strcpy_s(StrSymbol,512,StrLine);
			*strchr(StrSymbol,' ') = '\0';                          
			int nlen = strlen(StrSymbol);
			nstrlen = strlen(StrLine);
			memmove(StrLine,StrLine+nlen,strlen(StrLine)-nlen+1);//跳过符号名

			Trim(StrLine,StrLine);

			memcpy(StrVirtualAddr,StrLine,strchr(StrLine,' ')-StrLine);

			nstrlen = strlen(StrLine);
			memmove(StrLine,StrLine+8,nstrlen-8+1);//跳过VirtualAddress

			nstrlen = strlen(StrLine);
			memmove(StrLine,StrLine+5,nstrlen-5+1);//跳过f i ...
			strcpy(StrLibObject,StrLine);
			MapStructrue *mapstruct = new MapStructrue;
			mapstruct->Segment = Segment;                            //段
			mapstruct->Offset = FileOffset;                          //偏移
			strcpy(mapstruct->SymbleName,StrSymbol);                 //符号名
			mapstruct->VirtualAddress = StringToHex(StrVirtualAddr); //线性地址
			strcpy(mapstruct->LibObject,StrLibObject);               //输入文件名

			MapVector.push_back(mapstruct);
		}
	}

	fclose(mapfile);
	mapfile = NULL;

	for( std::vector<MapStructrue*>::iterator itr = MapVector.begin(); itr != MapVector.end(); itr++ )
	{
		MapStructrue *stu = *itr;
		int a = stu->Segment;
		int b = stu->Offset;
		int nlen = strlen("__ehhandler$");
		if( strstr(stu->SymbleName,"__ehhandler$") )//去掉标记
			memmove(stu->SymbleName,stu->SymbleName+nlen,strlen(stu->SymbleName) - nlen + 1);

		if (!UnDecorateSymbolName(stu->SymbleName, stu->SymbleName, 512, 0xFFF))//no UNDNAME_COMPLETE
		{
			// UnDecorateSymbolName failed
			DWORD error = GetLastError();
			char strerr[255] = {0};
			sprintf(strerr,"解析符号名时出现错误 %d\n", error);
			MsgBox(strerr,MB_ICONERROR);
			break;
		}
		//OutPutStr("%04X:%08X %s %08X %s\n",stu->Segment,stu->Offset,stu->SymbleName,stu->VirtualAddress,stu->LibObject);
		OutPutStr("%s %08X %s\n",stu->SymbleName,stu->VirtualAddress,stu->LibObject);
	}
}

MapStructrue* PeClass::GetMap(char* funcname)
{
	for( std::vector<MapStructrue*>::iterator itr = MapVector.begin(); itr != MapVector.end(); itr++ )
	{
		MapStructrue *stu = *itr;
		if( _stricmp(stu->SymbleName,funcname) == 0)
			return stu;
	}
	return NULL;
}

void PeClass::FreeMapVector()
{
	for( std::vector<MapStructrue*>::iterator itr = MapVector.begin(); itr != MapVector.end(); itr++ )
	{
		MapStructrue* stu = *itr;
		if( stu )
		{
			delete stu;
		}
	}
	MapVector.clear();
}

//分割得到段和偏移
BOOL PeClass::GetFileAddr(char* StrAddress,int* Segment,int* FileOffset)
{
	if( !StrAddress || !Segment || !FileOffset )
		return FALSE;
	char StrSegment[4+1] = {0};
	char StrOffset[8+1] = {0};
	memcpy(StrSegment,StrAddress,4);
	memcpy(StrOffset,StrAddress+5,8);
	*Segment = StringToHex(StrSegment);
	*FileOffset = StringToHex(StrOffset);
	return TRUE;
}

// ----- check the PE Signature and get some needed values -----
bool PeClass::CheckPeSig()
{
	if(mBaseCtx->pe.mDosHeader.e_magic!=IMAGE_DOS_SIGNATURE)// MZ
	{
		return false;
	}
	if(mBaseCtx->pe.mNtHeader.Signature!=IMAGE_NT_SIGNATURE)// PE00
	{
		return false;
	}
	return true;
}

bool PeClass::Analysis()
{
	DWORD dwVirtualAddress=0;     //偏移
	dwVirtualAddress=mBaseCtx->pe.mDosHeader.e_lfanew;
	dwVirtualAddress+=sizeof(NtHeader);

	for(int i=0;i<mBaseCtx->pe.mNtHeader.FileHeader.NumberOfSections;i++)
	{
		SectionHeader	mSectionHeader;
		memcpy_s(&mSectionHeader,sizeof(mSectionHeader),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(SectionHeader));
		dwVirtualAddress+=sizeof(SectionHeader);
		mBaseCtx->pe.mSectionsVector.push_back(mSectionHeader);
	}

	//根据最后一个节表判断当前是否有附加数据
	size_t mRawSize=mBaseCtx->pe.mSectionsVector.back().PointerToRawData+
		mBaseCtx->pe.mSectionsVector.back().SizeOfRawData;

	if(mBaseCtx->size>mRawSize)
	{
		//存在附加数据
		mBaseCtx->pe.mOverlay.isExist=true;
		mBaseCtx->pe.mOverlay.dwOffset=mRawSize;		//FOA
		mBaseCtx->pe.mOverlay.dwSize=mBaseCtx->size-mRawSize;
	}else
	{
		//不存在附加数据
		mBaseCtx->pe.mOverlay.isExist=false;
	}

	//导出表分析
	dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	if(dwVirtualAddress!=0)
	{
		memcpy_s(&mBaseCtx->pe.mExport.mDirectorys,sizeof(mBaseCtx->pe.mExport.mDirectorys),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(ExportDirectory));

		dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mExport.mDirectorys.Name);
		char name_buffer[MAX_PATH]={0};				//以\0结尾
		memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(name_buffer));
		mBaseCtx->pe.mExport.strDllName=name_buffer;
		dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mExport.mDirectorys.AddressOfFunctions);
		//取出函数地址
		for(unsigned int i=0;i<mBaseCtx->pe.mExport.mDirectorys.NumberOfFunctions;i++)
		{
			OrdinalFuncs mOrdinalFuncs;
			memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(mOrdinalFuncs.Func));
#ifdef PE_MODEL
			mOrdinalFuncs.Func=*(DWORD*)name_buffer;
#else
			mOrdinalFuncs.Func=*(ULONGULONG*)name_buffer;
#endif
			mBaseCtx->pe.mExport.mOrdinalFuncsVector.push_back(mOrdinalFuncs);
			dwVirtualAddress+=sizeof(DWORD);
		}
		//根据索引取出函数名并填充函数对应函数名
		dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mExport.mDirectorys.AddressOfNameOrdinals);
		std::map<WORD,std::string> name;
		for(int i=0;i<mBaseCtx->pe.mExport.mDirectorys.NumberOfNames;i++)
		{
			memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(WORD));
			WORD mIndex=*(WORD*)name_buffer;
			dwVirtualAddress+=sizeof(WORD);
			//开始取出函数名
			DWORD mRvaOffset=RvaToFoa(mBaseCtx->pe.mExport.mDirectorys.AddressOfNames);
			memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+mRvaOffset+i*sizeof(DWORD),sizeof(DWORD));
			mRvaOffset=RvaToFoa(*((DWORD *)name_buffer));
			memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+mRvaOffset,sizeof(name_buffer));
			mBaseCtx->pe.mExport.mOrdinalFuncsVector[mIndex].strFuncName=name_buffer;
		}
	}

	//导入表分析
	dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	if(dwVirtualAddress!=0)
	{
		char name_buffer[MAX_PATH]={0};				//以\0结尾
		do
		{
			ImportItem mImport;
			memcpy_s(&mImport.mDescriptor,sizeof(mImport.mDescriptor),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(IMAGE_IMPORT_DESCRIPTOR));
			if(mImport.mDescriptor.Name==0) break;

			//解析导入库名
			DWORD mRvaOffset=RvaToFoa(mImport.mDescriptor.Name);
			memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+mRvaOffset,sizeof(name_buffer));
			mImport.strDllName=name_buffer;
			
			//解析OriginalFirstThunk结构(有可能为单桥结构，这里只解析FirstThunk)
			mRvaOffset=RvaToFoa(mImport.mDescriptor.OriginalFirstThunk);
			do
			{
				ThunkData mThunkData;
				ThunkItem mThunkItem;
				memcpy_s(&mThunkData,sizeof(mThunkData),mBaseCtx->pVirMem+mRvaOffset,sizeof(ThunkData));
				if(mThunkData.u1.AddressOfData==0) break;
				mThunkItem.ThunkFOA = mRvaOffset;
				mThunkItem.ThunkRVA = FoaToRva(mRvaOffset);
				if(SnapByOrdinal(mThunkData.u1.Ordinal))
				{
					//最高位为1,以序号方式导入
					mThunkItem.Ordinal=mThunkData.u1.Ordinal&0x0000FFFF;
				}else
				{
					//最高位为0，以函数名方式导入
					memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+RvaToFoa(mThunkData.u1.AddressOfData),sizeof(name_buffer));
					mThunkItem.Ordinal=*(WORD*)(&name_buffer[0]);
					mThunkItem.strFuncName=&name_buffer[2];
				}
				mRvaOffset+=sizeof(ThunkData);
				mThunkItem.AddrFunc = mThunkData.u1.Function;
				mImport.mThunksVector.push_back(mThunkItem);
			}while(true);
			mBaseCtx->pe.mImportsVector.push_back(mImport);
			dwVirtualAddress+=sizeof(IMAGE_IMPORT_DESCRIPTOR);
		}while(true);
	}
	//重定位表分析
	dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
	if(dwVirtualAddress!=0)
	{
		do
		{
			RelocItem mRelocItem={0};
			memcpy_s(&mRelocItem.mBaseRelocation,sizeof(mRelocItem.mBaseRelocation),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(BaseRelocation));
			if(mRelocItem.mBaseRelocation.VirtualAddress==0) break;

			dwVirtualAddress+=sizeof(BaseRelocation);
			for(int i=0;i<(mRelocItem.mBaseRelocation.SizeOfBlock-sizeof(IMAGE_BASE_RELOCATION))/sizeof(WORD);i++)
			{
				ElementItem mValue;
				WORD *p=(WORD*)(mBaseCtx->pVirMem+dwVirtualAddress);
				mValue.cType=(*p)>>0xC;
				mValue.wValue=(*p)&0x0FFF;
				mRelocItem.mSnVector.push_back(mValue);
				dwVirtualAddress+=sizeof(WORD);
			}
			mBaseCtx->pe.mRelocsVector.push_back(mRelocItem);
		}while(true);
	}

	//开始解析资源表
	dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress);
	if(dwVirtualAddress!=0)
	{
		ResourceAnalysis(mBaseCtx->pVirMem+dwVirtualAddress,mBaseCtx->pVirMem+dwVirtualAddress,1);
	}

	//开始解析延迟载入表	
	dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress);
	if(dwVirtualAddress!=0)
	{
		char name_buffer[MAX_PATH]={0};				//以\0结尾
		do
		{
			DelayItem mDelayItem;
			memcpy_s(&mDelayItem.mDescriptor,sizeof(mDelayItem.mDescriptor),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(ImgDelayDescr));
			if(mDelayItem.mDescriptor.rvaDLLName==0) break;

			//解析导入库名
			DWORD mRvaOffset1=RvaToFoa(mDelayItem.mDescriptor.rvaDLLName);
			memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+mRvaOffset1,sizeof(name_buffer));
			mDelayItem.strDllName=name_buffer;
			
			//解析OriginalFirstThunk结构
			mRvaOffset1=RvaToFoa(mDelayItem.mDescriptor.rvaINT);
			DWORD mRvaOffset2=RvaToFoa(mDelayItem.mDescriptor.rvaIAT);
			do
			{
				ThunkData mThunkData;
				ThunkItem mThunkItem;
				memcpy_s(&mThunkData,sizeof(mThunkData),mBaseCtx->pVirMem+mRvaOffset1,sizeof(ThunkData));
				if(mThunkData.u1.AddressOfData==0) break;
				if(SnapByOrdinal(mThunkData.u1.Ordinal))
				{
					//最高位为1
					mThunkItem.Ordinal=mThunkData.u1.Ordinal&0x0000FFFF;
				}else
				{
					//最高位为0
					memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+RvaToFoa(mThunkData.u1.AddressOfData),sizeof(name_buffer));
					mThunkItem.Ordinal=*(WORD*)(&name_buffer[0]);
					mThunkItem.strFuncName=&name_buffer[2];
				}
				mRvaOffset1+=sizeof(ThunkData);
				//解析FirstThunk结构
				memcpy_s(&mThunkItem.AddrFunc,sizeof(mThunkItem.AddrFunc),mBaseCtx->pVirMem+mRvaOffset2,sizeof(mThunkItem.AddrFunc));
				mRvaOffset2+=sizeof(DWORD);
				mDelayItem.mThunksVector.push_back(mThunkItem);
			}while(true);
			mBaseCtx->pe.mDelaysVector.push_back(mDelayItem);
			dwVirtualAddress+=sizeof(ImgDelayDescr);
		}while(true);
	}

	//线程局部存储表分析
	dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
	if(dwVirtualAddress!=0)
	{
		memcpy_s(&mBaseCtx->pe.mTlsDirrctory,sizeof(mBaseCtx->pe.mTlsDirrctory),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(TlsDirectory));
	}

	//开始分析载入配置表
	dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress);
	if(dwVirtualAddress!=0)
	{
		memcpy_s(&mBaseCtx->pe.mLoadConfigDirctory,sizeof(mBaseCtx->pe.mLoadConfigDirctory),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(LoadConfigDirctory));
	}

	//开始分析绑定导入数据表
	dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress);
	if(dwVirtualAddress!=0)
	{
		DWORD	mRvaOffset=dwVirtualAddress;
		char name_buffer[MAX_PATH]={0};				//以\0结尾
		do
		{
			BoundItem mBoundItem;
			memcpy_s(&mBoundItem.mBoundImportDescriptor,sizeof(mBoundItem.mBoundImportDescriptor),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(BoundImportDescriptor));
			if(mBoundItem.mBoundImportDescriptor.TimeDateStamp==0) break;

			//解析导入库名
			memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+mRvaOffset+mBoundItem.mBoundImportDescriptor.OffsetModuleName,sizeof(name_buffer));
			mBoundItem.strDllName=name_buffer;

			dwVirtualAddress+=sizeof(BoundImportDescriptor);
			for(int i=0;i<mBoundItem.mBoundImportDescriptor.NumberOfModuleForwarderRefs;i++)
			{
				BoundForwarderRefItem mBoundForwarderRefItem;
				memcpy_s(&mBoundForwarderRefItem.mBoundForwarderRef,sizeof(mBoundForwarderRefItem.mBoundForwarderRef),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(BoundForwarderRef));
				
				memcpy_s(name_buffer,sizeof(name_buffer),mBaseCtx->pVirMem+mRvaOffset+mBoundForwarderRefItem.mBoundForwarderRef.OffsetModuleName,sizeof(name_buffer));
				mBoundForwarderRefItem.strDllName=name_buffer;
				
				mBoundItem.mBoundForwarderRefsVector.push_back(mBoundForwarderRefItem);
				dwVirtualAddress+=sizeof(BoundForwarderRef);
			}
			mBaseCtx->pe.mBoundsVector.push_back(mBoundItem);
		}while(true);
	}

	//开始分析调试目录表结构
	dwVirtualAddress=RvaToFoa(mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress);
	if(dwVirtualAddress!=0)
	{
		DWORD dwSize=mBaseCtx->pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size;
		for(int i=0;i<dwSize/sizeof(DebugDirectoryItem);i++)
		{
			DebugDirectoryItem	mDebugDirectoryItem;
			memcpy_s(&mDebugDirectoryItem,sizeof(mDebugDirectoryItem),mBaseCtx->pVirMem+dwVirtualAddress,sizeof(DebugDirectoryItem));
			mBaseCtx->pe.mDebugDirectorysVector.push_back(mDebugDirectoryItem);
			dwVirtualAddress+=sizeof(DebugDirectoryItem);
		}
	}
	return TRUE;
	
}

void PeClass::ResourceAnalysis(const char *lpRes,const char *lpResDir,const int dwLevel)
{
		ResourceDirectory mResourceDirectory={0};
		memcpy_s(&mResourceDirectory,sizeof(mResourceDirectory),lpResDir,sizeof(IMAGE_RESOURCE_DIRECTORY));
		lpResDir+=sizeof(IMAGE_RESOURCE_DIRECTORY);

		for(int i=0;i<mResourceDirectory.NumberOfIdEntries+mResourceDirectory.NumberOfNamedEntries;i++)
		{
			ResourceDirectoryEntry mResourceDirectoryEntry;
			memcpy_s(&mResourceDirectoryEntry,sizeof(mResourceDirectoryEntry),lpResDir,sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));
			if(1==dwLevel)
			{
				ResourceItem	mResourceItem;
				if(mResourceDirectoryEntry.NameIsString)
				{
					mResourceItem.dwType=0;
					mResourceItem.wstrType=L"test1";
				}else
				{
					mResourceItem.dwType=mResourceDirectoryEntry.Id;
					mResourceItem.wstrType.clear();
				}
				mBaseCtx->pe.mResourcesVector.push_back(mResourceItem);
				if(mResourceDirectoryEntry.DataIsDirectory)
				{
					ResourceAnalysis(lpRes,lpRes+mResourceDirectoryEntry.OffsetToDirectory,2);
				}else
				{
					throw(-1);
				}
			}
			if(2==dwLevel)
			{
				EntryDataItem mEntryDataItem;
				if(mResourceDirectoryEntry.NameIsString)
				{
					mEntryDataItem.wId=0;
					mEntryDataItem.wstrId=L"test2";
				}else
				{
					mEntryDataItem.wId=mResourceDirectoryEntry.Id;
					mEntryDataItem.wstrId.clear();
				}
				mBaseCtx->pe.mResourcesVector.back().mEntryDatasVector.push_back(mEntryDataItem);
				if(mResourceDirectoryEntry.DataIsDirectory)
				{
					ResourceAnalysis(lpRes,lpRes+mResourceDirectoryEntry.OffsetToDirectory,3);
				}else
				{
					throw(-1);
				}
			}
			if(3==dwLevel)
			{
				if(mResourceDirectoryEntry.NameIsString)
				{
					mBaseCtx->pe.mResourcesVector.back().mEntryDatasVector.back().wLua=0;
					mBaseCtx->pe.mResourcesVector.back().mEntryDatasVector.back().wstrLua=L"test3";
				}else
				{
					mBaseCtx->pe.mResourcesVector.back().mEntryDatasVector.back().wLua=mResourceDirectoryEntry.Id;
					mBaseCtx->pe.mResourcesVector.back().mEntryDatasVector.back().wstrLua.clear();
				}
				if(mResourceDirectoryEntry.DataIsDirectory)
				{
					throw(-1);
				}else
				{
					memcpy_s(&mBaseCtx->pe.mResourcesVector.back().mEntryDatasVector.back().mDataEntry,sizeof(ResourceDataEntry),
						lpRes+mResourceDirectoryEntry.OffsetToDirectory,sizeof(IMAGE_RESOURCE_DATA_ENTRY));
				}
			}
			lpResDir+=sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY);
		}
		//	ResourceDirectoryEntry mResourceDirectoryEntry;
		//	memcpy_s(&mResourceDirectoryEntry,sizeof(mResourceDirectoryEntry),mBaseCtx->pVirMem+lpResDir,sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));

		//	DWORD mRvaOffset2=0;
		//	ResourceItem	mResourceItem;
		//	//第一层
		//	if(mResourceDirectoryEntry.NameIsString)
		//	{
		//		mResourceItem.dwType=0;
		//		mResourceItem.wstrType=L"test1";
		//	}else
		//	{
		//		mResourceItem.dwType=mResourceDirectoryEntry.Id;
		//		mResourceItem.wstrType.clear();
		//	}
		//	if(mResourceDirectoryEntry.DataIsDirectory)
		//	{
		//		mRvaOffset2=mResourceDirectoryEntry.OffsetToDirectory+mRvaOffset1;
		//	}else
		//	{
		//		throw(-1);
		//	}

		//	//第二层
		//	EntryDataItem mEntryDataItem;
		//	memcpy_s(&mResourceDirectoryEntry,sizeof(mResourceDirectoryEntry),mBaseCtx->pVirMem+mRvaOffset2,sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));

		//	if(mResourceDirectoryEntry.NameIsString)
		//	{
		//		mEntryDataItem.wId=0;
		//		mEntryDataItem.wstrId=L"test2";
		//	}else
		//	{
		//		mEntryDataItem.wId=mResourceDirectoryEntry.Id;
		//		mEntryDataItem.wstrId.clear();
		//	}
		//	if(mResourceDirectoryEntry.DataIsDirectory)
		//	{
		//		mRvaOffset2=mResourceDirectoryEntry.OffsetToDirectory+mRvaOffset1;
		//	}else
		//	{
		//		throw(-1);
		//	}
		//	//第三层
		//	memcpy_s(&mResourceDirectoryEntry,sizeof(mResourceDirectoryEntry),mBaseCtx->pVirMem+mRvaOffset2,sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));

		//	if(mResourceDirectoryEntry.NameIsString)
		//	{
		//		mEntryDataItem.wLua=0;
		//		mEntryDataItem.wstrLua=L"test3";
		//	}else
		//	{
		//		mEntryDataItem.wLua=mResourceDirectoryEntry.Id;
		//		mEntryDataItem.wstrLua.clear();
		//	}
		//	if(mResourceDirectoryEntry.DataIsDirectory)
		//	{
		//		throw(-1);
		//	}else
		//	{
		//		mRvaOffset2=mResourceDirectoryEntry.OffsetToDirectory+mRvaOffset1;
		//		memcpy_s(&mEntryDataItem.mDataEntry,sizeof(ResourceDataEntry),mBaseCtx->pVirMem+mRvaOffset2,sizeof(IMAGE_RESOURCE_DATA_ENTRY));
		//	}

		//	mResourceItem.mEntryDatasVector.push_back(mEntryDataItem);
		//	mBaseCtx->pe.mResourcesVector.push_back(mResourceItem);
		//	dwVirtualAddress+=sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY);
		//}
}

const DWORD PeClass::RvaToFoa(DWORD Rva) const
{
	//不在节区中,在DOS头，PE头，节表头，或与第一个节区间隙
	if(Rva<mBaseCtx->pe.mSectionsVector[0].VirtualAddress)
	{
		return Rva;
	}

	//数据在节区中
	DWORD mSectionAlignment=mBaseCtx->pe.mNtHeader.OptionalHeader.FileAlignment;
	for(int i=0;i<mBaseCtx->pe.mSectionsVector.size();i++)
	{
		if(Rva>=mBaseCtx->pe.mSectionsVector[i].VirtualAddress&&Rva<((mBaseCtx->pe.mSectionsVector[i].VirtualAddress+mBaseCtx->pe.mSectionsVector[i].SizeOfRawData)/mSectionAlignment+1)*mSectionAlignment)
		{

			return Rva-mBaseCtx->pe.mSectionsVector[i].VirtualAddress+mBaseCtx->pe.mSectionsVector[i].PointerToRawData;
		}
	}
	return 0;
}

const	DWORD	PeClass::FoaToRva(DWORD foa) const
{
	//不在节区中
	if (foa<mBaseCtx->pe.mSectionsVector[0].PointerToRawData)
	{
		return foa;
	}
	//数据在节区中
	for (int i = 0; i<mBaseCtx->pe.mSectionsVector.size(); i++)
	{
		if (foa >= mBaseCtx->pe.mSectionsVector[i].PointerToRawData&&foa<(mBaseCtx->pe.mSectionsVector[i].PointerToRawData + mBaseCtx->pe.mSectionsVector[i].SizeOfRawData))
		{

			return foa - mBaseCtx->pe.mSectionsVector[i].PointerToRawData + mBaseCtx->pe.mSectionsVector[i].VirtualAddress;
		}
	}
	return 0;
}

const DWORD PeClass::SectionAlignmentSize(DWORD RawSize) const
{
	DWORD result=0;
	if(isAnalysised)
	{
		DWORD k=RawSize%mBaseCtx->pe.mNtHeader.OptionalHeader.SectionAlignment;
		if(k==0)
		{
			result=RawSize;
		}else
		{
			result =(RawSize/mBaseCtx->pe.mNtHeader.OptionalHeader.SectionAlignment+1)
				*mBaseCtx->pe.mNtHeader.OptionalHeader.SectionAlignment;
		}
	}
	return result;
}

const DWORD PeClass::FileAlignmentSize(DWORD RawSize) const
{
	DWORD result=0;
	if(isAnalysised)
	{
		DWORD k=RawSize%mBaseCtx->pe.mNtHeader.OptionalHeader.FileAlignment;
		if(k==0)
		{
			result=RawSize;
		}else
		{
			result =(RawSize/mBaseCtx->pe.mNtHeader.OptionalHeader.FileAlignment+1)
				*mBaseCtx->pe.mNtHeader.OptionalHeader.FileAlignment;
		}
	}
	return result;
}

