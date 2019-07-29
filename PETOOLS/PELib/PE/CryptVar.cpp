#include "CryptVar.h"
#include"../Patch.h"

//crypt IT
const char	*_szKernel32 		="Kernel32.dll";
const char	*_szLoadLibrary		="LoadLibraryA";
const char	*_szGetProcAddress	="GetProcAddress";
const char	*_szGetModuleHandle ="GetModuleHandleA";

const char	*_szUser32			="User32.dll";
const char	*_szGetKeyboardType	="GetKeyboardType";
const char	*_szWindowFromPoint	="WindowFromPoint";

const char	*_szAdvApi32		="AdvApi32.dll";
const char	*_szRegQueryValueEx ="RegQueryValueExA";
const char	*_szRegSetValueEx 	="RegSetValueExA";
const char	*_szStartService 	="StartServiceA";


const char	*_szOleAut32		="Oleaut32.dll";
const char	*_szSysFreeString	="SysFreeString";
const char	*_szCreateErrorInfo	="CreateErrorInfo";
const char	*_szSafeArrayPtrOfIndex="SafeArrayPtrOfIndex";

const char	*_szGdi32			="Gdi32.dll";
const char	*_szUnrealizeObject	="UnrealizeObject";

const char	*_szOle32			="Ole32.dll";
const char	*_szCreateStreamOnHGlobal="CreateStreamOnHGlobal";
const char	*_szIsEqualGUID		="IsEqualGUID";

const char	*_szComCtl32			="ComCtl32.dll";
const char	*_szImageList_SetIconSize="ImageList_SetIconSize";

//char	*pDepackerCode;
DWORD	DEPACKER_CODE_SIZE=(DWORD)&_patch2_ShellCodeEnd_-(DWORD)&_patch2_ShellCodeBegin_;
DWORD	IT_SIZE=0x60;
DWORD	TLS_SIZE=0x1000;


//----- PRE LOADER VARIABLES -----
// some API stuff
const char	*szKernel32					= "Kernel32.dll";
const char	*szGetModuleHandle			= "GetModuleHandleA";
const char	*szVirtualProtect			= "VirtualProtect";
const char	*szGetModuleFileName		= "GetModuleFileNameA";
const char	*szCreateFile				= "CreateFileA";
const char	*szGlobalAlloc				= "GlobalAlloc";
const char	*szGlobalFree				= "GlobalFree";
const char	*szReadFile					= "ReadFile";
const char	*szGetFileSize				= "GetFileSize";
const char	*szCloseHandle				= "CloseHandle";
const char	*szIsDebuggerPresent		= "IsDebuggerPresent";
const char	*szCreateToolhelp32Snapshot	= "CreateToolhelp32Snapshot";
const char	*szGetCurrentProcessId		= "GetCurrentProcessId";
const char	*szProcess32First			= "Process32First";
const char	*szProcess32Next			= "Process32Next";
const char	*szModule32First			= "Module32First";
const char	*szModule32Next				= "Module32Next";
const char	*szOpenProcess				= "OpenProcess";
const char	*szTerminateProcess			= "TerminateProcess";
const char	*szExitThread				= "ExitThread";
const char	*szExitProcess				= "ExitProcess";
const char	*szGetWindowsDirectory		= "GetWindowsDirectoryA";
const char	*szCreateWindow				= "CreateWindowA";
const char	*szGetCurrentThread			= "GetCurrentThread";
const char	*szSetThreadPriority		= "SetThreadPriority";
const char	*szSuspendThread			= "SuspendThread";
const char	*szResumeThread				= "ResumeThread";
const char	*szUser32					= "User32.dll";
const char	*szWaitForInputIdle			= "WaitForInputIdle";
DWORD		_LoadLibrary				= 0;
DWORD		_GetProcAddress				= 0;
DWORD		dwKernelBase				= 0;
DWORD		_GetModuleHandle			= 0;
DWORD		_VirtualProtect				= 0;
DWORD		dwOrgEntryPoint_Shade		= 0;
DWORD		_GetModuleFileName			= 0;
DWORD		_CreateFile					= 0;
DWORD		_GlobalAlloc				= 0;
DWORD		_GlobalFree					= 0;
DWORD		_ReadFile					= 0;
DWORD		_GetFileSize				= 0;
DWORD		_CloseHandle				= 0;
DWORD		_IsDebuggerPresent			= 0;
DWORD		_CreateToolhelp32Snapshot	= 0;
DWORD		_GetCurrentProcessId		= 0;
DWORD		_Process32First				= 0;
DWORD		_Process32Next				= 0;
DWORD		_Module32First				= 0;
DWORD		_Module32Next				= 0;
DWORD		_OpenProcess				= 0;
DWORD		_TerminateProcess			= 0;
DWORD		_ExitThread					= 0;
DWORD		_ExitProcess				= 0;
DWORD		_GetWindowsDirectory		= 0;
DWORD		_CreateWindow				= 0;
DWORD		_GetCurrentThread			= 0;
DWORD		_SetThreadPriority			= 0;
DWORD		_SuspendThread				= 0;
DWORD		_ResumeThread				= 0;
DWORD		_WaitForInputIdle			= 0;


//----- POS LOADER VARIABLES -----
DWORD		dwCompressType				= 1;
DWORD		dwDEPACKER_SECTION_NAME		='Cy';
DWORD		dwImageBase					= 0;
DWORD		dwCalcedCRC					= 0;
DWORD		dwParentProcess				= 0;

sItInfo		IIDInfo[MAX_IID_NUM];
sSEH		SEH;

DWORD		PROTECTION_FLAGS			= CHECK_SI_FLAG|ANTI_DUMP_FLAG|CHECK_HEADER_CRC;
DWORD		dwLoaderCRC					= 0;
DWORD		bNT							= 0;

char		SectionNames[MAX_SECTION_NUM][8];
DWORD		dwOrgEntryPoint				= 0;
DWORD		CODE_Size					= 0;//.text/CODE 
DWORD		DATA_Size					= 0;//.data/DATA/
DWORD		BSS_Size					= 0;//BSS  
DWORD		RDATA_Size					= 0;//.rdata
DWORD		IDATA_Size					= 0;//.idata
DWORD		EDATA_Size					= 0;//.edata
DWORD		TLS_Size					= 0;//.tls
DWORD		RSRC_Size					= 0;//.rsrc
DWORD		RelocRVA					= 0;
DWORD		RelocSize					= 0;
const char	*EXPLORER_EXE				= "EXPLORER.EXE";
const char	*szSoftICE95				= "\\\\.\\SICE";
const char	*szSoftICENT				= "\\\\.\\NTICE";

// This variables won't be crypted:
IMAGE_TLS_DIRECTORY32	TlsBackup;
IMAGE_BASE_RELOCATION	RlocBackup;
DWORD		dwOrgChecksumSize			= 0;
DWORD		dwOrgChecksum				= 0;
DWORD		Temp1						= 0;
DWORD		Temp2						= 0;
DWORD		BuffSize					= 0;
char		*Buff						= NULL;
// buffer for some stuff, its size: 2000h(VS) - DEPACKER_CODE_SIZE
//----------------------------------------------------------------

//----- PRE LOADER VARIABLES -----
// some API stuff
DWORD	dwRO_szKernel32;
DWORD	dwRO_szGetModuleHandle;
DWORD	dwRO_dwKernelBase;
DWORD	dwRO_szVirtualProtect;
DWORD	dwRO_szGetModuleFileName;
DWORD	dwRO_szCreateFile;
DWORD	dwRO_szGlobalAlloc;
DWORD	dwRO_szGlobalFree;
DWORD	dwRO_szReadFile;
DWORD	dwRO_szGetFileSize;
DWORD	dwRO_szCloseHandle;
DWORD	dwRO_szIsDebuggerPresent;
DWORD	dwRO_szCreateToolhelp32Snapshot;
DWORD	dwRO_szGetCurrentProcessId;
DWORD	dwRO_szProcess32First;
DWORD	dwRO_szProcess32Next;
DWORD	dwRO_szModule32First;
DWORD	dwRO_szModule32Next;
DWORD	dwRO_szOpenProcess;
DWORD	dwRO_szTerminateProcess;
DWORD	dwRO_szExitThread;
DWORD	dwRO_szExitProcess;
DWORD	dwRO_szGetWindowsDirectory;
DWORD	dwRO_szCreateWindow;
DWORD	dwRO_szGetCurrentThread;
DWORD	dwRO_szSetThreadPriority;
DWORD	dwRO_szSuspendThread;
DWORD	dwRO_szResumeThread;
DWORD	dwRO_szUser32;
DWORD	dwRO_szWaitForInputIdle;

DWORD	dwRO_LoadLibrary;
DWORD	dwRO_GetProcAddress;
DWORD	dwRO_GetModuleHandle;
DWORD	dwRO_VirtualProtect;
DWORD	dwRO_dwOrgEntryPoint_Shade;
DWORD	dwRO_GetModuleFileName;
DWORD	dwRO_CreateFile;
DWORD	dwRO_GlobalAlloc;
DWORD	dwRO_GlobalFree;
DWORD	dwRO_ReadFile;
DWORD	dwRO_GetFileSize;
DWORD	dwRO_CloseHandle;
DWORD	dwRO_IsDebuggerPresent;
DWORD	dwRO_CreateToolhelp32Snapshot;
DWORD	dwRO_GetCurrentProcessId;
DWORD	dwRO_Process32First;
DWORD	dwRO_Process32Next;
DWORD	dwRO_Module32First;
DWORD	dwRO_Module32Next;
DWORD	dwRO_OpenProcess;
DWORD	dwRO_TerminateProcess;
DWORD	dwRO_ExitThread;
DWORD	dwRO_ExitProcess;
DWORD	dwRO_GetWindowsDirectory;
DWORD   dwRO_CreateWindow;
DWORD	dwRO_GetCurrentThread;
DWORD	dwRO_SetThreadPriority;
DWORD	dwRO_SuspendThread;
DWORD	dwRO_ResumeThread;
DWORD	dwRO_WaitForInputIdle;
//----------------------------------------------------------------

//----- POS LOADER VARIABLES -----
DWORD	dwRO_dwCompressType;
DWORD	dwRO_dwDEPACKER_SECTION_NAME;
DWORD	dwRO_dwImageBase;
DWORD	dwRO_dwCalcedCRC;
DWORD	dwRO_dwParentProcess;

DWORD	dwRO_IIDInfo;
DWORD	dwRO_SEH;

DWORD	dwRO_PROTECTION_FLAGS;
DWORD	dwRO_dwLoaderCRC;
DWORD	dwRO_bNT;

DWORD	dwRO_SectionNames;
DWORD	dwRO_dwOrgEntryPoint;
DWORD	dwRO_CODE_Size;	//.text/CODE 
DWORD	dwRO_DATA_Size;	//.data/DATA/
DWORD   dwRO_BSS_Size;	//BSS  
DWORD	dwRO_RDATA_Size;//.rdata
DWORD	dwRO_IDATA_Size;//.idata
DWORD	dwRO_EDATA_Size;//.edata
DWORD	dwRO_TLS_Size;	//.tls
DWORD	dwRO_RSRC_Size;	//.rsrc
DWORD	dwRO_RelocRVA;
DWORD	dwRO_RelocSize;
DWORD	dwRO_EXPLORER_EXE;//"EXPLORER.EXE"
DWORD	dwRO_szSoftICE95;//"\\\\.\\SICE"
DWORD	dwRO_szSoftICENT;//"\\\\.\\NTICE"

// This variables won't be crypted:
DWORD	dwRO_TlsBackup;
DWORD	dwRO_RlocBackup;
DWORD	dwRO_dwOrgChecksum;
DWORD	dwRO_Temp1;
DWORD	dwRO_Temp2;
DWORD	dwRO_BuffSize;
DWORD	dwRO_Buff;