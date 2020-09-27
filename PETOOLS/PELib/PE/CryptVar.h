#pragma once
#include<Windows.h>

//crypt IT
extern const char	*_szKernel32;
extern const char	*_szLoadLibrary;
extern const char	*_szGetProcAddress;
extern const char	*_szGetModuleHandle;

extern const char	*_szUser32;
extern const char	*_szGetKeyboardType;
extern const char	*_szWindowFromPoint;

extern const char	*_szAdvApi32;
extern const char	*_szRegQueryValueEx;
extern const char	*_szRegSetValueEx;
extern const char	*_szStartService;


extern const char	*_szOleAut32;
extern const char	*_szSysFreeString;
extern const char	*_szCreateErrorInfo;
extern const char	*_szSafeArrayPtrOfIndex;

extern const char	*_szGdi32;
extern const char	*_szUnrealizeObject;

extern const char	*_szOle32;
extern const char	*_szCreateStreamOnHGlobal;
extern const char	*_szIsEqualGUID;

extern const char	*_szComCtl32;
extern const char	*_szImageList_SetIconSize;


//---------- PROTECTION MASK ----------
#define CHECK_SI_FLAG			0x0001
#define ERASE_HEADER_FLAG		0x0002
#define DESTROY_IMPORT_FLAG		0x0004
#define CHECK_HEADER_CRC		0x0008
#define ANTI_DUMP_FLAG			0x0010
#define API_REDIRECT_FLAG		0x0020
#define COMPRESS_RSRC_FLAG		0x40
#define OCX_TYPE_FLAG			0x0080
#define NET_TYPE_FLAG			0x0100

//---------- ADVANCED MASK ----------

#define REMOVE_RELOC			0x0001
#define REMOVE_DEBUG			0x0002
#define REMOVE_DOS_HEADER		0x0004
#define OPTIMIZED_DOS_HEADER	0x0008
#define CREATE_BACKUP			0x0010
#define AUTO_RUN				0x0020
#define EXIT_WHEN_DONE			0x0040

//------ DEFINITIONS -------
#define EXTRA_END_SIZE			0x1D//0x15
#define MAX_SECTION_COMPRESS	10
#define MAX_SECTION_NUM         20
#define MAX_IID_NUM             60
#define OEP_JUMP_ENCRYPT_NUM    'y'
#define VAR_PER_SIZE            0x60
#define SEC_PER_SIZE            0x30
#define RSRC_PER_SIZE			0x12
#define OEP_PER_SIZE            0x30
#define PACK_PER_SIZE			0x30


//extern char		*pDepackerCode;
extern DWORD	DEPACKER_CODE_SIZE;
extern DWORD	IT_SIZE;
extern DWORD	TLS_SIZE;

//----- LOADER STRUCTS -----
struct sItInfo
{
	DWORD DllNameRVA;
	DWORD FirstThunk;
	DWORD OrgFirstThunk;
};

struct sSEH
{
	DWORD OrgEsp;
	DWORD OrgEbp;
	DWORD SaveEip;
};

struct sReThunkInfo
{
	DWORD ApiStubMemAddr;
	DWORD pNextStub;
};

struct sApiStub // UNUSED !
{
	UCHAR JumpOpc;
	DWORD JumpAddr;
};

//----- PRE LOADER VARIABLES -----
// some API stuff
extern const char	*szKernel32;
extern const char	*szGetModuleHandle;
extern const char	*szVirtualProtect;
extern const char	*szGetModuleFileName;
extern const char	*szCreateFile;
extern const char	*szGlobalAlloc;
extern const char	*szGlobalFree;
extern const char	*szReadFile;
extern const char	*szGetFileSize;
extern const char	*szCloseHandle;
extern const char	*szIsDebuggerPresent;
extern const char	*szCreateToolhelp32Snapshot;
extern const char	*szGetCurrentProcessId;
extern const char	*szProcess32First;
extern const char	*szProcess32Next;
extern const char	*szModule32First;
extern const char	*szModule32Next;
extern const char	*szOpenProcess;
extern const char	*szTerminateProcess;
extern const char	*szExitThread;
extern const char	*szExitProcess;
extern const char	*szGetWindowsDirectory;
extern const char	*szCreateWindow;
extern const char	*szGetCurrentThread;
extern const char	*szSetThreadPriority;
extern const char	*szSuspendThread;
extern const char	*szResumeThread;
extern const char	*szUser32;
extern const char	*szWaitForInputIdle;
extern DWORD		_LoadLibrary;
extern DWORD		_GetProcAddress;
extern DWORD		dwKernelBase;
extern DWORD		_GetModuleHandle;
extern DWORD		_VirtualProtect;
extern DWORD		dwOrgEntryPoint_Shade;
extern DWORD		_GetModuleFileName;
extern DWORD		_CreateFile;
extern DWORD		_GlobalAlloc;
extern DWORD		_GlobalFree;
extern DWORD		_ReadFile;
extern DWORD		_GetFileSize;
extern DWORD		_CloseHandle;
extern DWORD		_IsDebuggerPresent;
extern DWORD		_CreateToolhelp32Snapshot;
extern DWORD		_GetCurrentProcessId;
extern DWORD		_Process32First;
extern DWORD		_Process32Next;
extern DWORD		_Module32First;
extern DWORD		_Module32Next;
extern DWORD		_OpenProcess;
extern DWORD		_TerminateProcess;
extern DWORD		_ExitThread;
extern DWORD		_ExitProcess;
extern DWORD		_GetWindowsDirectory;
extern DWORD		_CreateWindow;
extern DWORD		_GetCurrentThread;
extern DWORD		_SetThreadPriority;
extern DWORD		_SuspendThread;
extern DWORD		_ResumeThread;
extern DWORD		_WaitForInputIdle;


//----- POS LOADER VARIABLES -----
extern DWORD		dwCompressType;
extern DWORD		dwDEPACKER_SECTION_NAME;
extern DWORD		dwImageBase;
extern DWORD		dwCalcedCRC;
extern DWORD		dwParentProcess;

extern sItInfo		IIDInfo[MAX_IID_NUM];
extern sSEH	SEH;

extern DWORD		PROTECTION_FLAGS;
extern DWORD		dwLoaderCRC;
extern DWORD		bNT;

extern char			SectionNames[MAX_SECTION_NUM][8];
extern DWORD		dwOrgEntryPoint;
extern DWORD		CODE_Size;	//.text/CODE 
extern DWORD		DATA_Size;	//.data/DATA/
extern DWORD		BSS_Size;	//BSS  
extern DWORD		RDATA_Size;	//.rdata
extern DWORD		IDATA_Size;	//.idata
extern DWORD		EDATA_Size;	//.edata
extern DWORD		TLS_Size;	//.tls
extern DWORD		RSRC_Size;	//.rsrc
extern DWORD		RelocRVA;
extern DWORD		RelocSize;
extern const char	*EXPLORER_EXE;
extern const char	*szSoftICE95;
extern const char	*szSoftICENT;

// This variables won't be crypted:
extern IMAGE_TLS_DIRECTORY32	TlsBackup;
extern IMAGE_BASE_RELOCATION	RlocBackup;
extern DWORD		dwOrgChecksumSize;
extern DWORD		dwOrgChecksum;
extern DWORD		Temp1;
extern DWORD		Temp2;
extern DWORD		BuffSize;
extern char			*Buff;
// buffer for some stuff, its size: 2000h(VS) - DEPACKER_CODE_SIZE
//----------------------------------------------------------------

//----- PRE LOADER VARIABLES -----
// some API stuff
extern DWORD	dwRO_szKernel32;
extern DWORD	dwRO_szGetModuleHandle;
extern DWORD	dwRO_dwKernelBase;
extern DWORD	dwRO_szVirtualProtect;
extern DWORD	dwRO_szGetModuleFileName;
extern DWORD	dwRO_szCreateFile;
extern DWORD	dwRO_szGlobalAlloc;
extern DWORD	dwRO_szGlobalFree;
extern DWORD	dwRO_szReadFile;
extern DWORD	dwRO_szGetFileSize;
extern DWORD	dwRO_szCloseHandle;
extern DWORD	dwRO_szIsDebuggerPresent;
extern DWORD	dwRO_szCreateToolhelp32Snapshot;
extern DWORD	dwRO_szGetCurrentProcessId;
extern DWORD	dwRO_szProcess32First;
extern DWORD	dwRO_szProcess32Next;
extern DWORD	dwRO_szModule32First;
extern DWORD	dwRO_szModule32Next;
extern DWORD	dwRO_szOpenProcess;
extern DWORD	dwRO_szTerminateProcess;
extern DWORD	dwRO_szExitThread;
extern DWORD	dwRO_szExitProcess;
extern DWORD	dwRO_szGetWindowsDirectory;
extern DWORD	dwRO_szCreateWindow;
extern DWORD	dwRO_szGetCurrentThread;
extern DWORD	dwRO_szSetThreadPriority;
extern DWORD	dwRO_szSuspendThread;
extern DWORD	dwRO_szResumeThread;
extern DWORD	dwRO_szUser32;
extern DWORD	dwRO_szWaitForInputIdle;

extern DWORD	dwRO_LoadLibrary;
extern DWORD	dwRO_GetProcAddress;
extern DWORD	dwRO_GetModuleHandle;
extern DWORD	dwRO_VirtualProtect;
extern DWORD	dwRO_dwOrgEntryPoint_Shade;
extern DWORD	dwRO_GetModuleFileName;
extern DWORD	dwRO_CreateFile;
extern DWORD	dwRO_GlobalAlloc;
extern DWORD	dwRO_GlobalFree;
extern DWORD	dwRO_ReadFile;
extern DWORD	dwRO_GetFileSize;
extern DWORD	dwRO_CloseHandle;
extern DWORD	dwRO_IsDebuggerPresent;
extern DWORD	dwRO_CreateToolhelp32Snapshot;
extern DWORD	dwRO_GetCurrentProcessId;
extern DWORD	dwRO_Process32First;
extern DWORD	dwRO_Process32Next;
extern DWORD	dwRO_Module32First;
extern DWORD	dwRO_Module32Next;
extern DWORD	dwRO_OpenProcess;
extern DWORD	dwRO_TerminateProcess;
extern DWORD	dwRO_ExitThread;
extern DWORD	dwRO_ExitProcess;
extern DWORD	dwRO_GetWindowsDirectory;
extern DWORD	dwRO_CreateWindow;
extern DWORD	dwRO_GetCurrentThread;
extern DWORD	dwRO_SetThreadPriority;
extern DWORD	dwRO_SuspendThread;
extern DWORD	dwRO_ResumeThread;
extern DWORD	dwRO_WaitForInputIdle;
//----------------------------------------------------------------

//----- POS LOADER VARIABLES -----
extern DWORD	dwRO_dwCompressType;
extern DWORD	dwRO_dwDEPACKER_SECTION_NAME;
extern DWORD	dwRO_dwImageBase;
extern DWORD	dwRO_dwCalcedCRC;
extern DWORD	dwRO_dwParentProcess;

extern DWORD	dwRO_IIDInfo;
extern DWORD	dwRO_dwOrgEntryPoint;
extern DWORD	dwRO_SEH;

extern DWORD	dwRO_PROTECTION_FLAGS;
extern DWORD	dwRO_dwLoaderCRC;
extern DWORD	dwRO_bNT;

extern DWORD	dwRO_SectionNames;

extern DWORD	dwRO_CODE_Size;	//.text/CODE 
extern DWORD	dwRO_DATA_Size;	//.data/DATA/
extern DWORD	dwRO_BSS_Size;	//BSS  
extern DWORD	dwRO_RDATA_Size;//.rdata
extern DWORD	dwRO_IDATA_Size;//.idata
extern DWORD	dwRO_EDATA_Size;//.edata
extern DWORD	dwRO_TLS_Size;	//.tls
extern DWORD	dwRO_RSRC_Size;	//.rsrc
extern DWORD	dwRO_RelocRVA;
extern DWORD	dwRO_RelocSize;
extern DWORD	dwRO_EXPLORER_EXE;//"EXPLORER.EXE"
extern DWORD	dwRO_szSoftICE95;//"\\\\.\\SICE"
extern DWORD	dwRO_szSoftICENT;//"\\\\.\\NTICE"

// This variables won't be crypted:
extern DWORD	dwRO_TlsBackup;
extern DWORD	dwRO_RlocBackup;
extern DWORD	dwRO_dwOrgChecksum;
extern DWORD	dwRO_Temp1;
extern DWORD	dwRO_Temp2;
extern DWORD	dwRO_BuffSize;
extern DWORD	dwRO_Buff;