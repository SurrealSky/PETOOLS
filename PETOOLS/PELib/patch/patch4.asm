 .386
    .model flat,stdcall
    option casemap:none

include    c:\masm32\include\windows.inc

PUBLIC				_patch3_ShellCodeBegin_

PUBLIC				_patch3_LABEL_OEP_JUMP_CODE_START_
PUBLIC				_patch3_LABEL_OEP_JUMP_CODE_END_
PUBLIC				_patch3_LABEL_OepJumpDecryptLoop

PUBLIC				_patch3_LABEL_RO_SectionNames_START_
PUBLIC				_patch3_LABEL_RO_EXPLORER_EXE_END_
PUBLIC				_patch3_LABEL_DecryptSectionsInfoLoop

PUBLIC				_patch3_LABEL_VARIABLE_CRYPT_START_
PUBLIC				_patch3_LABEL_VARIABLE_CRYPT_END_
PUBLIC				_patch3_LABEL_VariableDecryptLoop

PUBLIC				_patch3_PackEncrypt_START_
PUBLIC				_patch3_PackEncrypt_END_
PUBLIC				_patch3_LABEL_PackDecryptLoop

PUBLIC				_patch3_PRE_VARIABLE_START_

PUBLIC				_patch3_CODEDecryptLoop
PUBLIC				_patch3_DATADecryptLoop
PUBLIC				_patch3_EDATADecryptLoop
PUBLIC				_patch3_IDATADecryptLoop
PUBLIC				_patch3_RSRCDecryptLoop
PUBLIC				_patch3_SectionDecryptLoop

PUBLIC				_patch3_RO_dwOrgChecksumSize;
PUBLIC				_patch3_RO_dwOrgChecksum

PUBLIC				_patch3_ShellCodeEnd_
PUBLIC				_patch3_offset_entry_jump

	;---------- PROTECTION MASK ----------
	CHECK_SI_FLAG=0001H
	ERASE_HEADER_FLAG=0002H
	DESTROY_IMPORT_FLAG=0004H
	CHECK_HEADER_CRC=0008H
	ANTI_DUMP_FLAG=0010H
	API_REDIRECT_FLAG=0020H
	;COMPRESS_RSRC_FLAG	DW	40H
	OCX_TYPE_FLAG=0080H
	NET_TYPE_FLAG=0100H

;---------- ADVANCED MASK ----------
	REMOVE_RELOC	=		0001H
	REMOVE_DEBUG	=		0002H
	REMOVE_DOS_HEADER	=	0004H
	OPTIMIZED_DOS_HEADER	=	0008H
	CREATE_BACKUP	=		0010H
	AUTO_RUN	=			0020H
	EXIT_WHEN_DONE	=		0040H

	_INVALID_HANDLE_VALUE	=	0FFFFFFFFH

	ID_RT_CURSOR	=1
	ID_RT_BITMAP	=2
	ID_RT_ICON	=3
	ID_RT_MENU	=4
	ID_RT_DIALOG	=5
	ID_RT_STRING	=6
	ID_RT_FONTDIR	=7
	ID_RT_FONT		=8
	ID_RT_ACCELERATOR	=9
	ID_RT_RCDATA		=10
	ID_RT_MESSAGETABLE	=11
	ID_RT_GROUP_CURSOR	=12
	ID_RT_GROUP_ICON	=14
	ID_RT_VERSION		=16
	ID_RT_DLGINCLUDE	=17
	ID_RT_PLUGPLAY		=19
	ID_RT_VXD			=20
	ID_RT_ANICURSOR		=21
	ID_RT_ANIICON		=22
	ID_RT_HTML			=23
	ID_RT_MANIFEST		=24


;代码段
    .code
	ASSUME FS:NOTHING
	_patch3_ShellCodeBegin_	LABEL	DWORD
	;-------------- PRE VARIABLE PE LOADER CODE ---------------
_patch3_LABEL_VARIABLE_CRYPT_START_	LABEL	DWORD
VARIABLE_CRYPT_START:
; some API stuff
_RO_szKernel32:			;db "Kernel32.dll",0,13
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szGetModuleHandle:	;db "GetModuleHandleA",0,17
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szVirtualProtect:	;db "VirtualProtect",0,15
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3
_RO_szGetModuleFileName:;db "GetModuleFileNameA",0,19
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3
_RO_szCreateFile:		;db "CreateFileA",0,12
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szGlobalAlloc:		;db "GlobalAlloc",0,12
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szGlobalFree:		;db "GlobalFree",0,11
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
_RO_szReadFile:			;db "ReadFile",0,9
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szGetFileSize:		;db "GetFileSize",0,12
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szCloseHandle:		;db "CloseHandle",0,12
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szIsDebuggerPresent:	;db "IsDebuggerPresent",0,18
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szCreateToolhelp32Snapshot:;db "CreateToolhelp32Snapshot",0,25
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szGetCurrentProcessId:;db "GetCurrentProcessId",0,20
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szProcess32First:;db "Process32First",0,15
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szProcess32Next:;db "Process32Next",0,14
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szModule32First:;db "Module32First",0,14
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szModule32Next:;db "Module32Next",0,13
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szOpenProcess:;db "OpenProcess",0,12
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szTerminateProcess:;db "TerminateProcess",0,17
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3 
_RO_szExitThread:;db "ExitThread",0,11
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szExitProcess:;db "ExitProcess",0,12
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szGetWindowsDirectory:;db "GetWindowsDirectoryA",0,21
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szCreateWindow:;db "CreateWindowA",0,14
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szGetCurrentThread:;db "GetCurrentThread",0,17
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szSetThreadPriority:;db "SetThreadPriority",0,18
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szSuspendThread:;db "SuspendThread",0,14
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szResumeThread	:;db "ResumeThread",0,13
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szUser32:		;db "User32.dll",0,11
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szWaitForInputIdle:	;db "WaitForInputIdle",0,17
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_LoadLibrary:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetProcAddress:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwKernelBase:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetModuleHandle:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_VirtualProtect:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwOrgEntryPoint_Shade:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetModuleFileName:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_CreateFile:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_GlobalAlloc:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_GlobalFree:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_ReadFile:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_GetFileSize:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_CloseHandle:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_IsDebuggerPresent:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_CreateToolhelp32Snapshot:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_GetCurrentProcessId:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_Process32First:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_Process32Next:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_Module32First:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_Module32Next:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_OpenProcess:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_TerminateProcess:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_ExitThread:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_ExitProcess	:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetWindowsDirectory:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_CreateWindow:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetCurrentThread:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_SetThreadPriority:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_SuspendThread:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_ResumeThread:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_WaitForInputIdle:
		INT 3
		INT 3
		INT 3
		INT 3
_patch3_LABEL_VARIABLE_CRYPT_END_	LABEL	DWORD
VARIABLE_CRYPT_END:

DepackerCode:
;--------------------junk code start------------------------------
		;------fake vc++ head-------------
		PUSH EBP  
		MOV EBP,ESP  
		PUSH -1  
		push 40ff12h
		PUSH 40ff13h
		MOV EAX,DWORD PTR FS:[0]  
		PUSH EAX  
		MOV DWORD PTR FS:[0],ESP  
		ADD ESP,-6Ch 
		PUSH EBX  
		PUSH ESI  
		PUSH EDI
		;----------------------------
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		MOV EBX,55h
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		CALL FUCK1
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		CALL FUCK1
		;------some crazy work!------	
		db	08h	dup(0EEh)
		;----------------------------
		CALL FUCK2
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		CALL FUCK2
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		CMP EBX,55h
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		JNZ CallMe2
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		RETN
CallMe0:
	PUSHAD
	CALL CallMe1
CallMe1:	
	POP EBP
	SUB EBP,OFFSET CallMe1

	MOV EDX,EBP
	ADD EDX,OFFSET MAIN1
	PUSH EDX
	CALL MAIN0
	RETN
MAIN0:	
	RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
CallMe2:
	CALL FUCK3
	CALL CallMe0
	RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
FUCK3:
	XOR EAX,EAX
	PUSH DWORD PTR FS:[EAX]
	MOV DWORD PTR FS:[EAX],ESP
	INT 3
	RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
FUCK1:
	XOR EAX,EAX
	PUSH DWORD PTR FS:[EAX]
	MOV DWORD PTR FS:[EAX],ESP
	DEC EBX
	INT 3
	RETN
;--------------------junk code end------------------------------
MAIN1:
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
	;-------------------- DECRYPT MAIN BODY -------------------
	XOR EBX,EBX
	MOV ECX,OFFSET LOADER_CRYPT_END
	SUB ECX,OFFSET LOADER_CRYPT_START;ecx->CRYPT_LOADER_SIZE
	MOV EDX,EBP
	ADD EDX,OFFSET LOADER_CRYPT_START
	LEA EDI,[EDX]
	MOV ESI,EDI
	XOR EAX,EAX
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
Reserve_for_dll:
	CALL PackDecrypt
	NOP
	NOP
	NOP
	JMP UNLOAD_DLL
FUCK2:
	XOR EAX,EAX
	PUSH DWORD PTR FS:[EAX]
	MOV DWORD PTR FS:[EAX],ESP
	INC EBX
	INT 3
	RETN
	INT 3
	INT 3
	INT 3
	INT 3
PackDecrypt:
PackDecryptLoop:
		LODS BYTE PTR DS:[ESI]
_patch3_LABEL_PackDecryptLoop	LABEL	DWORD
		db	060h	dup(0FFh)
		STOS BYTE PTR ES:[EDI]
	LOOP PackDecryptLoop
_patch3_PackEncrypt_START_	LABEL DWORD
LOADER_CRYPT_START:
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;------------------ DECRYPT PRE VARIABLE ------------------
		XOR EBX,EBX
		MOV ECX,OFFSET VARIABLE_CRYPT_END
		SUB ECX,OFFSET VARIABLE_CRYPT_START;ecx->CRYPT_LOADER_SIZE
		MOV EDX,EBP
		ADD EDX,OFFSET VARIABLE_CRYPT_START
		LEA EDI,[EDX]
		MOV ESI,EDI
		XOR EAX,EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;FUNNY JUMP
		MOV EDX,EBP
		ADD EDX,OFFSET VariableDecrypt
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		INT 3
		INT 3
		INT 3
		INT 3
VariableDecrypt:
VariableDecryptLoop:
		LODS BYTE PTR DS:[ESI]
		_patch3_LABEL_VariableDecryptLoop	LABEL	DWORD
		db	060h	dup(0FFh)
		STOS BYTE PTR ES:[EDI]
	LOOP VariableDecryptLoop
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwDEPACKER_SECTION_NAME
		MOV EAX,[EDX]
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;---------------------- DETECT WinNT ----------------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_bNT
		PUSH FS:[30h]
		POP EAX
		TEST EAX,EAX
		JS      NoNT; detected Win 9x
			MOV DWORD PTR [EDX], 1
			JMP IsNT
	NoNT:
			MOV DWORD PTR [EDX], 0
	IsNT:
		;----------------- Get CRC OF LOADER CODE -----------------
		MOV EDX,EBP
		ADD EDX,OFFSET DepackerCode
		LEA EAX,DWORD PTR [EDX]
		MOV ECX,OFFSET OEP_JUMP_CODE_START 
		SUB	ECX,OFFSET DepackerCode
		PUSH ECX
		PUSH EAX
		CALL _GetCheckSum
		ADD ESP,08h

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwLoaderCRC
		MOV DWORD PTR [EDX], EAX

		;------------------------ SI Check 1 ----------------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_SEH
		LEA ESI,[EDX]
		MOV EDX,EBP
		ADD EDX,OFFSET SICheck1_SP
		LEA EAX,[EDX]
		MOV DWORD PTR DS:[ESI+8],EAX;[ESI].SaveEip
		MOV EDI,EBP

		MOV EDX,EBP
		ADD EDX,OFFSET SehHandler1
		LEA EAX,[EDX]
		XOR EBX,EBX
		PUSH EAX
		PUSH DWORD PTR FS:[EBX]
		MOV DWORD PTR FS:[EBX], ESP

		; 0 - SI not found
		; 1 - SI found
		;SehHandler1 更改 ax 04h
		MOV AX,0FFh
		JMP SM1
		RETN;DB 0FFh
SM1:
	INT 3	
SICheck1_SP:
	MOV  EBP, EDI
	; uninstall SEH frame
	XOR  EBX, EBX
    POP  DWORD PTR FS:[EBX]
    ADD  ESP, 4
	CMP AL,4	;判断SehHandler1是否被执行
	JE SkipSICheck1
		JMP SM2
	INT 3;DB 0E9h
SM2: POPAD
	RETN

SkipSICheck1:
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;----------------- GET BASE API ADDRESSES -----------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_PROTECTION_FLAGS
		TEST DWORD PTR [EDX],OCX_TYPE_FLAG
		JZ DONT_NEED_FIND_IMAGEBASE
			MOV EAX,ESP
			MOV ECX,EBP
			ADD ECX,OFFSET find_image_base
			mov     edx,ecx
	find_image_base:

			and     edx, 0FFFFF000h
			mov     eax, dword ptr [edx]
			and     eax, 0FFFFh
			cmp     eax, 05A4Dh
			je      end_find_image_base
			sub     edx, 1000h
			jmp     find_image_base
	end_find_image_base:
			MOV ECX,EBP
			ADD ECX,OFFSET _RO_dwImageBase
			MOV [ECX],EDX
	DONT_NEED_FIND_IMAGEBASE:
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EAX,DWORD PTR [EDX]
		ADD EAX,[EAX+03Ch]
		ADD EAX,080h
		MOV ECX,DWORD PTR [EAX]	; ecx contains the VirtualAddress of the IT
		ADD ECX,DWORD PTR [EDX]
		ADD ECX,010h				;ecx points to the FirstThunk address of the IID
		MOV EAX,DWORD PTR [ECX]
		ADD EAX,DWORD PTR [EDX]
		MOV EBX,DWORD PTR [EAX]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_LoadLibrary
		MOV [EDX],EBX
		ADD EAX,04h
		MOV EBX,DWORD PTR [EAX]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetProcAddress
		MOV DWORD PTR [EDX],EBX	
		;----- GET ALL OTHER API ADDRESSES -----
		; get kernel base
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szKernel32
		LEA EAX,[EDX]
		PUSH EAX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_LoadLibrary
		CALL DWORD PTR[EDX]
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwKernelBase
		MOV ESI,EAX	; esi -> kernel base
		MOV DWORD PTR [EDX], EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> GetModuleHandle
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szGetModuleHandle
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetModuleHandle
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> VirtualProtect
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szVirtualProtect
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_VirtualProtect
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> GetModuleFileName
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szGetModuleFileName
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetModuleFileName
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> CreateFile
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szCreateFile
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateFile
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> GlobalAlloc
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szGlobalAlloc
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GlobalAlloc
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> GlobalFree
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szGlobalFree
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GlobalFree
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> ReadFile
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szReadFile
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_ReadFile
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> GetFileSize
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szGetFileSize
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetFileSize
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> CloseHandle
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szCloseHandle
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CloseHandle
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> IsDebuggerPresent
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szIsDebuggerPresent
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IsDebuggerPresent
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> CreateToolhelp32Snapshot
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szCreateToolhelp32Snapshot
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateToolhelp32Snapshot
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> GetCurrentProcessId
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szGetCurrentProcessId
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetCurrentProcessId
		MOV [EDX],EAX
		;-> Process32First
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szProcess32First
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Process32First
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> Process32Next
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szProcess32Next
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Process32Next
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> szModule32First
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szModule32First
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Module32First
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> szModule32Next	
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szModule32Next	
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Module32Next	
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> OpenProcess
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szOpenProcess
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_OpenProcess
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> TerminateProcess
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szTerminateProcess	
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_TerminateProcess
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> ExitThread
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szExitThread	
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_ExitThread
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> GetWindowsDirectory
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szGetWindowsDirectory
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetWindowsDirectory
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> CreateWindow
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szCreateWindow
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateWindow
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> GetCurrentThread
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szGetCurrentThread
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetCurrentThread
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> SetThreadPriority
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szSetThreadPriority
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_SetThreadPriority
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> SuspendThread
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szSuspendThread
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_SuspendThread
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> ResumeThread
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szResumeThread
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_ResumeThread
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		; get user base
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szUser32
		LEA EAX,[EDX]
		PUSH EAX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_LoadLibrary
		CALL DWORD PTR[EDX]
		MOV ESI,EAX	; esi -> user base
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-> WaitForInputIdle
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szWaitForInputIdle
		LEA EAX,[EDX]
		CALL DoGetProcAddr
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_WaitForInputIdle
		MOV [EDX],EAX
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szKernel32
		LEA EDI,[EDX]
		MOV ECX,OFFSET _RO_LoadLibrary
		XOR AL,AL
		SUB ECX,OFFSET _RO_szKernel32
		REP STOS BYTE  PTR ES:[EDI]			;擦掉外壳输入表函数名
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------

;AntiDebug()判断父进程是否为explorer.exe,以及反dump
;----------------------------------------------------------
_AntiDebug1:
	MOV ECX,49h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Buff
	XOR EAX,EAX
	LEA EDI,[EDX]
	PUSH EDI
	REP STOS DWORD PTR ES:[EDI]
	POP EDI
	MOV DWORD PTR SS:[EDX],128h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetCurrentProcessId
	CALL DWORD PTR[EDX]
	PUSH 0
	PUSH 2
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Temp1
	MOV [EDX],EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CreateToolhelp32Snapshot
	CALL DWORD PTR[EDX]
	MOV ESI,EAX
	MOV EAX,EBP
	ADD EAX,OFFSET _RO_Buff
	PUSH EAX
	PUSH ESI
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Process32First
	CALL DWORD PTR[EDX]
	TEST EAX,EAX
	JE ENDOFCHECKPROCESS1
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Buff
		LEA ECX,[EDX]
		PUSH ECX
		PUSH ESI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Process32Next
		CALL DWORD PTR[EDX]
		TEST EAX,EAX
		JE ENDOFCHECKPROCESS1
		XOR EBX,EBX
		JMP CHECKNEXTPROCESS1
		LEA ECX,DWORD PTR DS:[ECX]
CHECKNEXTPROCESS1: 
			PUSH ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			MOV EAX,[EDX+8h]
			LEA ESI,[EDX+24h]
			MOV EDI,ESI
			PUSH ESI
			PUSH EDI
			CALL _CharUpperBuff
			ADD ESP,08h
			PUSH EDI
			PUSH ESI
			CALL _GetFileNameFromPath
			ADD ESP,08h
			MOV ESI,EDI
			PUSH ESI
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_EXPLORER_EXE
			LEA EDI,[EDX];ASCII "EXPLORER.EXE"
			MOV ECX,0Dh
			XOR EDX,EDX
			REPE CMPSB
			JNZ EXPLORER_NOT_FOUND1
				CMP EBX,0
				JZ MAIN_EXPLORER1
				JMP EXPLORER_NOT_FOUND1
MAIN_EXPLORER1:	MOV EBX,EAX
EXPLORER_NOT_FOUND1:
			POP EDI
			POP ESI
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Temp1
			CMP EAX,DWORD PTR SS:[EDX]
			POP EDX
			JNZ IT_IS_NOT_MYCHILD1
				PUSH EDX
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_Buff
				MOV EAX,[EDX+18h]
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_dwParentProcess
				MOV [EDX],EAX
				POP EDX
IT_IS_NOT_MYCHILD1:
			POP ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA ECX,[EDX]
			PUSH ECX
			PUSH ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Process32Next
			CALL DWORD PTR[EDX]
			TEST EAX,EAX
			JNZ CHECKNEXTPROCESS1
ENDOFCHECKPROCESS1:
		MOV EDX,EBP
		ADD EDX,OFFSET LoaderContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
; it's in an own function to keep a the loader code small
; EAX = address of API string
; ESI = target dll base
DoGetProcAddr:
	PUSH EAX
	PUSH ESI
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetProcAddress
	CALL DWORD PTR[EDX]
	RETN
LoaderContinue1:
	;------------------------ ANTI DUMP---------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],ANTI_DUMP_FLAG
	JZ LetDumpable
		PUSH FS:[30h]
		POP EAX
		TEST EAX,EAX
		JS fuapfdw_is9x					;detected Win 9x
		MOV EAX,[EAX+0Ch]
		MOV EAX,[EAX+0Ch]
		MOV DWORD PTR [EAX+20h],2000h ; increase size variable
		JMP fuapfdw_finished
fuapfdw_is9x:
			PUSH 0
			MOV EBX,EBP
			ADD EBX,OFFSET _RO_GetModuleHandle
			CALL DWORD PTR[EBX]
			TEST EDX,EDX
			JNS fuapfdw_finished		; Most probably incompatible!!!
			CMP DWORD PTR [EDX+8],-1
			JNE fuapfdw_finished		; Most probably incompatible!!!
			MOV EDX,[EDX+4]				; get address of internaly used
										; PE header
			MOV DWORD PTR [EDX+50h],2000h ; increase size variable
fuapfdw_finished:
LetDumpable:
	;----- CHECK FOR PARENT 1	 -----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwParentProcess
	MOV EAX,[EDX]
	OR EAX,EAX
	JNZ PARENT_EXIST1
		POPAD
		RETN
PARENT_EXIST1:
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------

		;---------------- GET HEADER WRITE ACCESS -----------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EDI,DWORD PTR [EDX]
		ADD EDI,DWORD PTR [EDI+03Ch]; edi -> pointer to PE header
		;assume edi : ptr IMAGE_NT_HEADERS
		MOV ESI,DWORD PTR [EDX]
		MOV ECX,DWORD PTR [EDI+54H];.OptionalHeader.SizeOfHeaders
		;assume edi : nothing
		; fix page access
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Buff
		LEA EAX,[EDX]
		PUSH EAX
		PUSH PAGE_READWRITE
		PUSH ECX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		PUSH [EDX]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_VirtualProtect
		CALL DWORD PTR[EDX]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_PROTECTION_FLAGS
		TEST DWORD PTR [EDX],CHECK_HEADER_CRC
		JZ DontCheckCRC
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_PROTECTION_FLAGS
		TEST DWORD PTR [EDX],OCX_TYPE_FLAG
		JNZ CheckCRCforOCX
			; get the calling exe filename
			PUSH MAX_PATH
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA EDI,[EDX]
			PUSH EDI; edi -> filename
			PUSH 0
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_GetModuleFileName
			CALL DWORD PTR[EDX]
			JMP Continue_CRC 
CheckCRCforOCX:
			; get the calling exe filename
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_dwImageBase
			MOV EAX,[EDX]
			PUSH MAX_PATH
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA EDI,[EDX]
			PUSH EDI; edi -> filename
			PUSH EAX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_GetModuleFileName
			CALL DWORD PTR[EDX]
Continue_CRC:
			; map it...
			PUSH 0
			PUSH FILE_ATTRIBUTE_NORMAL
			PUSH OPEN_EXISTING
			PUSH NULL
			PUSH FILE_SHARE_READ
			PUSH GENERIC_READ
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_CreateFile
			CALL DWORD PTR[EDX]
			CMP EAX,_INVALID_HANDLE_VALUE
			JNE HANDLE_IS_VALID1
			XOR EAX,EAX
			JMP SkipChecksumCalc
HANDLE_IS_VALID1:
		MOV EDI,EAX	; edi -> file handle
	
		PUSH NULL
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetFileSize
		CALL DWORD PTR[EDX]

		MOV EDX,OFFSET DepackerCodeEND;OEP_JUMP_CODE_END
		SUB EDX,OFFSET OEP_JUMP_CODE_START;EDX->CHECKSUM_SKIP_SIZE
		SUB EAX,EDX
		SUB EAX,2
		XCHG EAX,ESI; esi -> filesize

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwOrgChecksumSize
		MOV ESI,DWORD PTR[EDX]
		
		PUSH ESI
		PUSH GMEM_FIXED+GMEM_ZEROINIT
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GlobalAlloc
		CALL DWORD PTR[EDX]

		CMP EAX,NULL
		JNE ALLOCATE_IS_VALID
			JMP SkipChecksumCalcAndCleanUp
ALLOCATE_IS_VALID:

		XCHG EAX,EBX; ebx -> mem base
	
		PUSH NULL
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Buff
		LEA EAX,[EDX]

		PUSH EAX
		PUSH ESI
		PUSH EBX
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_ReadFile
		CALL DWORD PTR[EDX]

		; get the checksum
		MOV EAX,EBX; -> Base
		MOV ECX,ESI
		PUSH EBX; [ESP] -> hMem
		PUSH EDI; EDI = hFile
	
		PUSH ECX; -> FileSize
		PUSH EAX; -> Base
		CALL _GetCheckSum
		ADD ESP,08h

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwCalcedCRC
		MOV [EDX],EAX
	
		POP  EDI
		POP  EBX
		; the calculated CRC will be compared at the start of the InitIT function >:-)
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		; FUNNY JUMP :)
		MOV EDX,EBP
		ADD EDX,OFFSET AfterCRCCalcContinue
		LEA  EAX,[EDX]
		PUSH EAX
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;-------------------- SECTIONS DECRYPTER ------------------
_DecryptSectionsInfo:
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_SectionNames
  		LEA EDI,[EDX]
  		MOV ESI,EDI
		LEA EDI,[EDX]
		MOV ECX,OFFSET _RO_EXPLORER_EXE
		SUB ECX,OFFSET _RO_SectionNames
		JMP DecryptSectionsInfo
		INT 3
		INT 3
		INT 3
		INT 3
	DecryptSectionsInfo:
			LODS BYTE PTR DS:[ESI]
_patch3_LABEL_DecryptSectionsInfoLoop	LABEL	DWORD
			db	030h	dup(0FFh)
			STOS BYTE PTR ES:[EDI]
		LOOP DecryptSectionsInfo
	RETN

		;-> Start of GetCheckSum
_GetCheckSum:
		PUSH EBP
		MOV EBP,ESP
		PUSH EBX
		PUSH ECX
		PUSH EDX
		PUSH ESI
		PUSH EDI
		; EAX = file image base
		; ECX = filesize	
		MOV EAX,DWORD PTR SS:[EBP+08h]; -> Destination
		MOV ECX,DWORD PTR SS:[EBP+0Ch]; -> Source
		MOV EDI,EAX	; edi -> data pointer
		XOR EAX,EAX	; eax -> current bytes
		XOR EBX,EBX	; ebx -> current checksum
		XOR EDX,EDX	; edx -> Position (zero based)
		; start calculation
	CheckSumLoop:
			MOV AL,BYTE PTR [EDI]
			MUL EDX
			ADD EBX,EAX 
			INC EDX
   		INC EDI   	
		LOOP CheckSumLoop
   		XCHG EAX,EBX; EAX -> checksum
		POP EDI
		POP ESI
		POP EDX
		POP ECX
		POP EBX
		MOV ESP,EBP
		POP EBP
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
AfterCRCCalcContinue:
		; clean up
		PUSH EBX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GlobalFree
		CALL DWORD PTR[EDX];GlobalFree(checksum);

		XCHG ESI,EAX
SkipChecksumCalcAndCleanUp:	
		PUSH EAX
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CloseHandle
		CALL DWORD PTR[EDX];CloseHandle(handle);	
		POP EAX
SkipChecksumCalc:
DontCheckCRC:
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		CALL _DecryptSectionsInfo
		;----------------------- DECRYPTION ----------------------
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EAX,[EDX]
		CALL _ReBuiltSectionNames
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EAX,[EDX]
		CALL _CryptPE;CryptPE(Base)
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EAX,[EDX]
		CALL _DecompressPE
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EAX,[EDX]
		CALL _RemoveSectionNames
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EAX,[EDX]
		MOV EDI,EAX
		ADD EDI,[EDI+3Ch]
		;assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
		ADD EDI,034h;->ImageBase
		MOV EBX,[EDI]
		CMP EAX,EBX
		JZ do_not_need_relocate
		CALL _RelocationRVA
do_not_need_relocate:
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		CALL _RemoveSectionsInfo
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		MOV EDX,EBP
		ADD EDX,OFFSET AfterDeCryptionContinue
		LEA EAX,[EDX]
		PUSH EAX
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
_DecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop1
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop1:
		LODS BYTE PTR DS:[ESI]
_patch3_SectionDecryptLoop LABEL DWORD
		db	030h	dup(0FFh)
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop1
RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
;-------------------- SECTIONS ENCRYPTER ------------------
_ReBuiltSectionNames:
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	;assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ESI,EDI
	ADD ESI,0F8h
	;assume esi : ptr IMAGE_SECTION_HEADER		; esi -> Section header
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SectionNames
	MOV EBX,EDX
	XOR EDX,EDX
	;.REPEAT	   
SECTION_IS_NOT_ZERO3:
		PUSH EDX
		PUSH ECX
		PUSH EAX		
		PUSH ESI
		PUSH EDI
		; -> retrieve section names
		MOV EDI,ESI
		MOV ESI,EBX
		MOV ECX,08h
sectionnamewrite:
		LODS BYTE PTR DS:[ESI]
		STOS BYTE PTR ES:[EDI]
		LOOP sectionnamewrite
		POP EDI
		POP ESI
		POP EAX
		POP ECX
		POP EDX
		ADD EBX,08h
		ADD ESI,28h;SIZEOF IMAGE_SECTION_HEADER
		INC EDX
	;.UNTIL DX==[EDI].FileHeader.NumberOfSections
	CMP DX,WORD PTR DS:[EDI+6]
	JNZ SECTION_IS_NOT_ZERO3
	;assume esi : nothing
	;assume edi : nothing
	RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
_RemoveSectionsInfo:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SectionNames
	LEA EDI,[EDX]
	XOR AL,AL
	MOV ECX,OFFSET _RO_EXPLORER_EXE
	SUB ECX,OFFSET _RO_SectionNames
	REP STOS BYTE PTR ES:[EDI]
	RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
;------------------- RELOCATION SECTIONS ------------------
_RelocationRVA:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,[EDX]
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	;assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ECX,EBP
	ADD ECX,OFFSET _RO_RelocRVA
	MOV ESI,[ECX]
	ADD ESI,EAX
	ADD EDI,034h;->ImageBase
	MOV EBX,[EDI]
	MOV EDX,EAX;->ImageBase
	SUB EAX,EBX
	MOV EBX,EAX;->RELOC Correction
nextbuffer:
		MOV EAX,DWORD PTR DS:[ESI]
		CMP EAX,0
		JZ finish_correction
		ADD EAX,EDX
		ADD ESI,4
		MOV ECX,DWORD PTR DS:[ESI]
		ADD ESI,4
		SUB ECX,8
nextOffset:
			PUSH EDX
			PUSH ECX
			XOR EDX,EDX
			XOR ECX,ECX
			MOV CX,WORD PTR DS:[ESI]
			ADD ESI,2
			MOV DX,CX
			SHR DX,12
			AND CX,0FFFh
			CMP DX,IMAGE_REL_BASED_ABSOLUTE 
				JNZ check_reloc_type1
				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type1:
			CMP DX,IMAGE_REL_BASED_HIGH
			JNZ check_reloc_type2
				PUSH EAX
				PUSH EDX
				PUSH EBX
				MOV EDX,EAX
				ADD EDX,ECX
				MOV	EAX,DWORD PTR DS:[EDX]
				AND EBX,0FFFF0000h
				ADD EAX,EBX
				MOV DWORD PTR DS:[EDX],EAX
				POP EBX
				POP EDX
				POP EAX

				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type2:
			CMP DX,IMAGE_REL_BASED_LOW
			JNZ check_reloc_type3
				PUSH EAX
				PUSH EDX
				PUSH EBX
				MOV EDX,EAX
				ADD EDX,ECX
				MOV	EAX,DWORD PTR DS:[EDX]
				AND EBX,00000FFFFh
				ADD EAX,EBX
				MOV DWORD PTR DS:[EDX],EAX
				POP EBX
				POP EDX
				POP EAX

				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type3:
			CMP DX,IMAGE_REL_BASED_HIGHLOW
			JNZ check_reloc_type4
				PUSH EAX
				PUSH EDX
				PUSH EBX
				MOV EDX,EAX
				ADD EDX,ECX
				MOV	EAX,DWORD PTR DS:[EDX]
				ADD EAX,EBX
				MOV DWORD PTR DS:[EDX],EAX
				POP EBX
				POP EDX
				POP EAX

				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type4:
			CMP DX,IMAGE_REL_BASED_HIGHADJ
			JNZ check_reloc_type5
				PUSH EAX
				PUSH EDX
				PUSH EBX
				MOV EDX,EAX
				ADD EDX,ECX
				MOV	EAX,DWORD PTR DS:[EDX]
				MOV CX,WORD PTR DS:[ESI]
				ADD ESI,2
				AND EBX,0FFFF0000h
				ADD EBX,ECX
				ADD EAX,EBX
				MOV DWORD PTR DS:[EDX],EAX
				POP EBX
				POP EDX
				POP EAX

				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type5:
		JMP nextOffset
finish_correction:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_RelocRVA
	ADD EAX,[EDX]
	LEA EDI,[EAX]
	XOR EAX,EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_RelocSize
	ADD ECX,[EDX]
	REP STOS BYTE  PTR ES:[EDI]
	RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
	;-------------------- SECTIONS DECRYPTER ------------------
_CODEDecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop2
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop2:
		LODS BYTE PTR DS:[ESI]
_patch3_CODEDecryptLoop LABEL DWORD
		db	030h	dup(0FFh)
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop2
RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		; void ReBuiltSectionNames(char* Base)
_RemoveSectionNames:
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	;assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ESI,EDI
	ADD ESI,0F8h
	;assume esi : ptr IMAGE_SECTION_HEADER		; esi -> Section header
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint
	MOV EAX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade
	MOV [EDX],EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SectionNames
	MOV EBX,EDX
	XOR EDX,EDX
	;.REPEAT	   
SECTION_IS_NOT_ZERO4:
		PUSH EDX
		PUSH ECX
		PUSH ESI
		PUSH EDI

		XOR AL,AL
		MOV EDI,ESI
		MOV ECX,08h
		REP STOS BYTE  PTR ES:[EDI]

		POP EDI
		POP ESI
		POP ECX
		POP EDX
		ADD EBX,08h
		ADD ESI,28h;SIZEOF IMAGE_SECTION_HEADER
		INC EDX
	;.UNTIL DX==[EDI].FileHeader.NumberOfSections
	CMP DX,WORD PTR DS:[EDI+6]
	JNZ SECTION_IS_NOT_ZERO4
	;assume esi : nothing
	;assume edi : nothing
	RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
	; void CryptPE(char* Base)
_CryptPE:
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	;assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ESI,EDI
	ADD ESI,0F8h
	;assume esi : ptr IMAGE_SECTION_HEADER		; esi -> Section header
	XOR EDX,EDX
	;.REPEAT	   
SECTION_IS_NOT_ZERO1:
		PUSH EDX
		PUSH EAX		
		; -> do some special sections !
		CMP DWORD PTR DS:[ESI],'xet.';.text
			JZ _CODE_CHECK_IF_SIZE_IS_ZERO1

		CMP DWORD PTR DS:[ESI],'EDOC';CODE
			JZ _CODE_CHECK_IF_SIZE_IS_ZERO1

		CMP DWORD PTR DS:[ESI],'tad.';.data
			JZ _DATA_CHECK_IF_SIZE_IS_ZERO1

		CMP DWORD PTR DS:[ESI],'ATAD';DATA
			JZ _DATA_CHECK_IF_SIZE_IS_ZERO1

		CMP DWORD PTR DS:[ESI],'SSB';BSS
			JZ _CHECK_IF_SIZE_IS_ZERO1

		CMP DWORD PTR DS:[ESI],'adr.';.rdata
			JZ _CHECK_IF_SIZE_IS_ZERO1

		CMP DWORD PTR DS:[ESI],'adi.';.idata
			JZ _IDATA_CHECK_IF_SIZE_IS_ZERO1

		CMP DWORD PTR DS:[ESI],'ade.';.edata
		JNZ Continue_Other_Test11
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_PROTECTION_FLAGS
			TEST DWORD PTR [EDX],OCX_TYPE_FLAG
			POP EDX
			JZ _EDATA_CHECK_IF_SIZE_IS_ZERO1
Continue_Other_Test11:
		CMP DWORD PTR DS:[ESI],'rsr.';.rsrc
		JNZ Continue_Other_Test12
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_PROTECTION_FLAGS
			TEST DWORD PTR [EDX],OCX_TYPE_FLAG
			POP EDX
			JZ _RSRC_CHECK_IF_SIZE_IS_ZERO1
Continue_Other_Test12:
		JMP __LoopEnd1

		;-> skip also some other sections
_CHECK_IF_SIZE_IS_ZERO1:
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
	   ;-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	;[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch];[esi].VirtualAddress
		ADD ESI,EAX
		CALL _DecryptBuff

		; FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP;ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
_CODE_CHECK_IF_SIZE_IS_ZERO1:
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
	   ;-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	;[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch];[esi].VirtualAddress
		ADD ESI,EAX
		CALL _CODEDecryptBuff

		; FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP;ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
_DATA_CHECK_IF_SIZE_IS_ZERO1:
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
	   ;-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	;[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch];[esi].VirtualAddress
		ADD ESI,EAX
		CALL _DATADecryptBuff

		; FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP;ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;----------------------------
_IDATA_CHECK_IF_SIZE_IS_ZERO1:
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
	   ;-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	;[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch];[esi].VirtualAddress
		ADD ESI,EAX
		CALL _IDATADecryptBuff

		; FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP;ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
		;----------------------------
_EDATA_CHECK_IF_SIZE_IS_ZERO1:
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
	   ;-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	;[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch];[esi].VirtualAddress
		ADD ESI,EAX
		CALL _EDATADecryptBuff

		; FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP;ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
_RSRC_CHECK_IF_SIZE_IS_ZERO1:
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
	   ;-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH EDX
		PUSH ECX
		PUSH EBX
		PUSH EAX
		MOV ECX,DWORD PTR DS:[ESI+10h]	;[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch]	;[esi].VirtualAddress
		ADD ESI,EAX
		PUSH 0
		PUSH EAX
		PUSH ESI
		CALL _CryptResourceDirectory
		ADD ESP,0Ch

		; FUNNY JUMP :)
		POP EAX
		POP EBX
		POP ECX
		POP EDX
		MOV EDX,EBP;ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		;------some crazy work!------
		db	08h	dup(0EEh)
		;----------------------------
SecDecryptContinue1:	   
		POP EDI
		POP ESI
		
__LoopEnd1:   
		ADD ESI,28h;SIZEOF IMAGE_SECTION_HEADER
		POP EAX
		POP EDX
		INC EDX
	CMP DX,WORD PTR DS:[EDI+6]
	JNZ SECTION_IS_NOT_ZERO1
	RETN
	;-------------------- SECTIONS DECRYPTER ------------------
_DATADecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop3
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop3:
		LODS BYTE PTR DS:[ESI]
_patch3_DATADecryptLoop LABEL DWORD
		db	030h	dup(0FFh)
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop3
RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
	;----------------------- DECOMPRESS -----------------------
lzo1f_decompress_asm_fast_safe:
	PUSH EBP
	PUSH EDI
	PUSH ESI
	PUSH EBX
	PUSH ECX
	PUSH EDX
	SUB ESP,000000CH;SUB ESP,0000000CH
	CLD
	MOV ESI,DWORD PTR SS:[ESP+28H];->sourc buffer
	MOV EDI,DWORD PTR SS:[ESP+30H];->destination buffer
	MOV EBP,00000003H
	LEA EAX,DWORD PTR DS:[ESI-3H]
	ADD EAX,DWORD PTR SS:[ESP+2CH];->source size
	MOV DWORD PTR SS:[ESP+4H],EAX
	MOV EAX,EDI
	LEA EDX,DWORD PTR SS:[ESP+34H];->destination size ;MOV
	ADD EAX,DWORD PTR DS:[EDX]

	MOV DWORD PTR SS:[ESP],EAX
	XOR EAX,EAX
	XOR EBX,EBX
	LODS BYTE PTR DS:[ESI]
	CMP AL,11H
	JBE L6
	SUB AL,0EH
	JMP L7
L3:	ADD EAX,000000FFH
	LEA EDX,DWORD PTR DS:[ESI+EAX+12H]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
L4:	MOV BL,BYTE PTR DS:[ESI]
	INC ESI
	OR BL,BL
	JE L3
	LEA EAX,DWORD PTR DS:[EAX+EBX+15H]
	JMP L7
	LEA ESI,DWORD PTR DS:[ESI]
L5:	CMP DWORD PTR SS:[ESP+4H],ESI
	JB L26
	MOV AL,BYTE PTR DS:[ESI]
	INC ESI
L6:	CMP AL,10H
	JNB L9
	OR AL,AL
	JE L4
	ADD EAX,6H
L7:	LEA EDX,DWORD PTR DS:[EDI+EAX-3H]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	LEA EDX,DWORD PTR DS:[ESI+EAX-3H]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
	MOV ECX,EAX
	XOR EAX,EBP
	SHR ECX,02H
	AND EAX,EBP
L8:	MOV EDX,DWORD PTR DS:[ESI]
	ADD ESI,00000004H
	MOV DWORD PTR DS:[EDI],EDX
	ADD EDI,4H
	DEC ECX
	JNZ L8
	SUB ESI,EAX
	SUB EDI,EAX
	MOV AL,BYTE PTR DS:[ESI]
	INC ESI
	CMP AL,10H
	JNB L9
	LEA EDX,DWORD PTR DS:[EDI+3H]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	SHR EAX,02H
	MOV BL,BYTE PTR DS:[ESI]
	LEA EDX,DWORD PTR DS:[EDI-801H]
	LEA EAX,DWORD PTR DS:[EAX+EBX*4H]
	INC ESI
	SUB EDX,EAX
	CMP EDX,DWORD PTR SS:[ESP+30H];->destination buffer
	JB L28
	MOV ECX,DWORD PTR DS:[EDX]
	MOV DWORD PTR DS:[EDI],ECX
	ADD EDI,EBP
	JMP L16
	MOV ESI,ESI
L9:	CMP AL,40H
	JB L12
	MOV ECX,EAX
	SHR EAX,02H
	LEA EDX,DWORD PTR DS:[EDI-1H]
	AND EAX,00000007H
	MOV BL,BYTE PTR DS:[ESI]
	SHR ECX,05H
	LEA EAX,DWORD PTR DS:[EAX+EBX*8H]
	INC ESI
	SUB EDX,EAX
	ADD ECX,4H
	CMP EAX,EBP
	JNB L14
	JMP L17
L10:ADD EAX,000000FFH
	LEA EDX,DWORD PTR DS:[ESI+3H]
	CMP DWORD PTR SS:[ESP+4H],EDX;->destination buffer
	JB L26
L11:MOV BL,BYTE PTR DS:[ESI]
	INC ESI
	OR BL,BL
	JE L10
	LEA ECX,DWORD PTR DS:[EAX+EBX+24H]
	XOR EAX,EAX
	JMP L13
	NOP
L12:CMP AL,20H
	JB L20
	AND EAX,0000001fH
	JE L11
	LEA ECX,DWORD PTR DS:[EAX+5H]
L13:MOV AX,WORD PTR DS:[ESI]
	LEA EDX,DWORD PTR DS:[EDI-1H]
	SHR EAX,02H
	ADD ESI,02H
	SUB EDX,EAX
	CMP EAX,EBP
	JB L17
L14:CMP EDX,DWORD PTR SS:[ESP+30H];->destination buffer
	JB L28
	LEA EAX,DWORD PTR DS:[EDI+ECX-3H]
	SHR ECX,02H
	CMP DWORD PTR SS:[ESP],EAX
	JB L27
L15:MOV EBX,DWORD PTR DS:[EDX]
	ADD EDX,00000004H
	MOV DWORD PTR DS:[EDI],EBX
	ADD EDI,00000004H
	DEC ECX
	JNZ L15
	MOV EDI,EAX
	XOR EBX,EBX
L16:MOV AL,BYTE PTR DS:[ESI-2H]
	AND EAX,EBP
	JE L5
	LEA EDX,DWORD PTR DS:[EDI+EAX]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	LEA EDX,DWORD PTR DS:[ESI+EAX]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
	MOV EDX,DWORD PTR DS:[ESI]
	ADD ESI,EAX
	MOV DWORD PTR DS:[EDI],EDX
	ADD EDI,EAX
	MOV AL,BYTE PTR DS:[ESI]
	INC ESI
	JMP L9
	LEA ESI,DWORD PTR DS:[ESI]
L17:CMP EDX,DWORD PTR SS:[ESP+30H];->destination buffer
	JB L28
	LEA EAX,DWORD PTR DS:[EDI+ECX-3H]
	CMP DWORD PTR SS:[ESP],EAX
	JB L27
	XCHG ESI,EDX
	SUB ECX,EBP
	REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
	MOV ESI,EDX
	JMP L16
L18:ADD ECX,000000FFH
	LEA EDX,DWORD PTR DS:[ESI+3H]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
L19:MOV BL,BYTE PTR DS:[ESI]
	INC ESI
	OR BL,BL
	JE L18
	LEA ECX,DWORD PTR DS:[EBX+ECX+0CH]
	JMP L21
	LEA ESI,DWORD PTR DS:[ESI]
L20:CMP AL,10H
	JB L22
	MOV ECX,EAX
	AND EAX,00000008H
	SHL EAX,0DH
	AND ECX,00000007H
	JE L19
	ADD ECX,00000005H
L21:MOV AX,WORD PTR DS:[ESI]
	ADD ESI,00000002H
	LEA EDX,DWORD PTR DS:[EDI+0FFFFC000H]
	SHR EAX,02H
	JE L23
	SUB EDX,EAX
	JMP L14
	LEA ESI,DWORD PTR DS:[ESI]
L22:LEA EDX,DWORD PTR DS:[EDI+2H]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	SHR EAX,02H
	MOV BL,BYTE PTR DS:[ESI]
	LEA EDX,DWORD PTR DS:[EDI-1H]
	LEA EAX,DWORD PTR DS:[EAX+EBX*4H]
	INC ESI
	SUB EDX,EAX
	CMP EDX,DWORD PTR SS:[ESP+30H];->destination buffer
	JB L28
	MOV AL,BYTE PTR DS:[EDX]
	MOV BYTE PTR DS:[EDI],AL
	MOV BL,BYTE PTR DS:[EDX+1H]
	MOV BYTE PTR DS:[EDI+1H],BL
	ADD EDI,00000002H
	JMP L16
L23:CMP ECX,00000006H
	SETNE AL
	CMP EDI,DWORD PTR SS:[ESP]
	JA L27
	MOV EDX,DWORD PTR SS:[ESP+28H];->sourc buffer
	ADD EDX,DWORD PTR SS:[ESP+2CH];->source size
	CMP ESI,EDX
	JA L26
	JB L25
L24:SUB EDI,DWORD PTR SS:[ESP+30H];->destination buffer
	LEA EDX,DWORD PTR SS:[ESP+34H];->destination size ;MOV
	MOV DWORD PTR DS:[EDX],EDI
	NEG EAX
	ADD ESP,0CH
	POP EDX
	POP ECX
	POP EBX
	POP ESI
	POP EDI
	POP EBP
	RETN 8
	MOV EAX,00000001H
	JMP L24
L25:MOV EAX,00000008H
	JMP L24
L26:MOV EAX,00000004H
	JMP L24
L27:MOV EAX,00000005H
	JMP L24
L28:MOV EAX,00000006H
	JMP L24

; void CopyMemory(PVOID Destination,const VOID* Source,
_CopyMemory:
	PUSH EBP
	MOV EBP,ESP
	PUSH ECX
	PUSH EAX
	PUSH ESI
	PUSH EDI
	MOV EDI,DWORD PTR SS:[EBP+08h]; -> Destination
	MOV ESI,DWORD PTR SS:[EBP+0Ch]; -> Source
	MOV ECX,DWORD PTR SS:[EBP+10h]; -> Length
	XOR EAX,EAX
__memcopy:
		LODS BYTE PTR DS:[ESI];ESI
		STOS BYTE PTR ES:[EDI];EDI
	LOOP __memcopy
	POP EDI
	POP ESI
	POP EAX
	POP ECX
	MOV ESP,EBP
	POP EBP
	RETN

	;;void CharUpperBuff
_CharUpperBuff:
	PUSH EBP
	MOV EBP,ESP
	PUSH ECX
	PUSH EAX
	PUSH ESI
	PUSH EDI
	MOV EDI,DWORD PTR SS:[EBP+08h]; -> Destination
	MOV ESI,DWORD PTR SS:[EBP+0Ch]; -> Source
	MOV ECX,255; -> Length
	XOR EAX,EAX
__makeupperloop:
		LODS BYTE PTR DS:[ESI];ESI
		CMP AL,00h
		JZ endofbuffer
		CMP AL,60h
		JC notinlowerfield
		CMP AL,7Bh
		JNC notinlowerfield
		SUB AL,20h
notinlowerfield:
		STOS BYTE PTR ES:[EDI];EDI
	LOOP __makeupperloop
endofbuffer:
	POP EDI
	POP ESI
	POP EAX
	POP ECX
	MOV ESP,EBP
	POP EBP
	RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
	;-------------------- RESOURCE DECRYPTER ------------------
_CryptResourceDirectory:
	PUSH EBP
	MOV EBP,ESP
	PUSH EAX
	PUSH EBX
	PUSH ECX
	PUSH EDX
	PUSH ESI
	PUSH EDI
	MOV ESI,DWORD PTR SS:[EBP+08h]; -> Base
	MOV EDX,DWORD PTR SS:[EBP+0Ch]; -> dwImageBase
	MOV EAX,DWORD PTR SS:[EBP+10h]; -> dwRVA
	MOV EDI,ESI
	ADD EDI,EAX
	XOR ECX,ECX
	MOV CX,WORD PTR[EDI+0Eh]
	CMP ECX,0
	JZ EndOfRSRCDecrypt1
	XOR EBX,EBX
DecryptResourceLoop1:
		MOV EDI,ESI
		ADD EDI,EAX
		ADD EDI,010h
		ADD EDI,EBX
		ADD EBX,08h
		TEST DWORD PTR [EDI+4],IMAGE_RESOURCE_DATA_IS_DIRECTORY
		JZ DataIsNotDirectory1
			PUSH ECX
			PUSH EBX
			PUSH EAX
			XOR EBX,EBX
			MOV BX,WORD PTR [EDI]
			CMP EBX,ID_RT_CURSOR
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_BITMAP
			JZ FollowOtherDirectory1
			;CMP EBX,ID_RT_ICON
			;JZ FollowOtherDirectory1
			CMP EBX,ID_RT_MENU
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_DIALOG
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_STRING
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_FONTDIR
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_FONT
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_ACCELERATOR
			JZ FollowOtherDirectory1	
			CMP EBX,ID_RT_RCDATA
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_MESSAGETABLE
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_GROUP_CURSOR 
			JZ FollowOtherDirectory1
			;CMP EBX,ID_RT_GROUP_ICON
			;JZ FollowOtherDirectory1
			;CMP EBX,ID_RT_VERSION
			;JZ FollowOtherDirectory1
			CMP EBX,32
			JNC FollowOtherDirectory1
			JMP DontNeedFollow1
FollowOtherDirectory1:
				MOV EAX,DWORD PTR [EDI+4]
				AND EAX,07FFFFFFFh
				PUSH EAX
				PUSH EDX
				PUSH ESI
				CALL _CryptResourceDirectory
				ADD ESP,0Ch
				;CryptResourceDirectory(Base,dwImageBase,directory_entries.OffsetToDirectory);
DontNeedFollow1:
			POP EAX
			POP EBX
			POP ECX
			JMP DecryptRSRCContinue1
DataIsNotDirectory1:		
			PUSH EDX
			PUSH ECX
			PUSH EBX
			PUSH EAX
			PUSH EDI
			PUSH ESI
			;MOV EDI,ESI
			MOV EAX,ESI
			ADD EAX,DWORD PTR [EDI+4]; -> directory_entries.OffsetToData
			LEA EDI,[EAX]
			MOV ECX,DWORD PTR [EDI+4]; -> data_entry.Size
			MOV EAX,DWORD PTR [EDI]  ; ->data_entry.OffsetToData
			ADD EAX,EDX
			LEA EDI,[EAX]
			MOV ESI,EDI
			XOR EAX,EAX
			JMP DecryptRSRCLoop1
			INT 3
			INT 3
			INT 3
			INT 3
DecryptRSRCLoop1:
			LODS BYTE PTR DS:[ESI]
_patch3_RSRCDecryptLoop LABEL DWORD
			db	012h	dup(0FFh)
			STOS BYTE PTR ES:[EDI]
			LOOP DecryptRSRCLoop1
			POP ESI
			POP EDI
			POP EAX
			POP EBX
			POP ECX
			POP EDX
DecryptRSRCContinue1:
	DEC ECX
	CMP ECX,0
	JNZ DecryptResourceLoop1
EndOfRSRCDecrypt1:
	POP EDI
	POP ESI
	POP EDX
	POP ECX
	POP EBX
	POP EAX
	MOV ESP,EBP
	POP EBP
	RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------

	;-------------------- SECTIONS DECRYPTER ------------------
_IDATADecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop4
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop4:
		LODS BYTE PTR DS:[ESI]
_patch3_IDATADecryptLoop LABEL DWORD
		db	030h	dup(0FFh)
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop4
RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
	;void FillMemory
_FillMemory:
	PUSH EBP
	MOV EBP,ESP
	PUSH ECX
	PUSH EBX
	PUSH ESI
	PUSH EDI
	MOV ESI,DWORD PTR SS:[EBP+08h]; -> Destination
	MOV ECX,DWORD PTR SS:[EBP+0Ch]; -> Length
	MOV EBX,DWORD PTR SS:[EBP+10h]; -> Fill
__memfill:
		MOV BYTE PTR [ESI],BL
		INC ESI
        LOOP __memfill
	POP EDI
	POP ESI
	POP EBX
	POP ECX
	MOV ESP,EBP
	POP EBP
	RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
_GetFileNameFromPath:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDX
	PUSH ECX
	PUSH EBX
	PUSH EAX
	PUSH ESI
	MOV ESI,DWORD PTR SS:[EBP+08h]; -> Source
	MOV EDI,ESI; -> Destination
	MOV ECX,255; -> Length
	XOR EAX,EAX
	XOR EBX,EBX
	XOR EDX,EDX	
__filenamecheck:
		LODS BYTE PTR DS:[ESI];ESI
		CMP AL,00h
		JZ endofbuffer1
		CMP AL,5Ch
		JNE ContinueCheck
		MOV EDX,EBX		
ContinueCheck:
		INC EBX
	LOOP __filenamecheck
endofbuffer1:
	;MOV EDI,name; -> Destination
	CMP EDX,00h
	JZ NotFoundAnyPath
	INC EDX
NotFoundAnyPath:
	ADD EDI,EDX
	MOV DWORD PTR SS:[EBP+0Ch],EDI
	POP ESI
	POP EAX
	POP EBX
	POP ECX
	POP EDX
	MOV ESP,EBP
	POP EBP
	RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------

	;-------------------- SECTIONS DECRYPTER ------------------
_EDATADecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop5
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop5:
		LODS BYTE PTR DS:[ESI]
_patch3_EDATADecryptLoop LABEL DWORD
		db	030h	dup(0FFh)
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop5
RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
;_StrNCmp:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDX
	PUSH ECX
	PUSH EBX
	PUSH ESI
	PUSH EDI
	MOV ESI,DWORD PTR SS:[EBP+08h]; -> string1
	MOV EDI,DWORD PTR SS:[EBP+0Ch]; -> string2
	MOV ECX,DWORD PTR SS:[EBP+10h]; -> count
	XOR EAX,EAX
	XOR EBX,EBX
	XOR EDX,EDX
_stringcheck:
		MOV AL, BYTE PTR DS:[ESI];ESI
		MOV BL, BYTE PTR DS:[EDI];ESI
		CMP AL,00h
		JE endofbuffer2
		CMP AL,BL
		JE itisequal	
			INC EDX
itisequal:
		INC ESI
		INC EDI
	LOOP _stringcheck
endofbuffer2:
	;MOV EDI,name; -> Destination
	MOV EAX,EDX
	POP EDI
	POP ESI
	POP EBX
	POP ECX
	POP EDX
	MOV ESP,EBP
	POP EBP
	RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
_aPsafe_depack_asm_fast:
	PUSHAD
	MOV ESI,DWORD PTR SS:[ESP+24h]
	MOV EDI,DWORD PTR SS:[ESP+28h]
	MOV EBX,DWORD PTR DS:[ESI]
	CMP EBX,32335041h
	JNZ SHORT errHappen
	MOV EBX,DWORD PTR DS:[ESI+4h]
	CMP EBX,18h
	JB SHORT errHappen
	ADD EBX,ESI
	;PUSH DWORD PTR DS:[ESI+8h]
	;PUSH EBX
	;CALL _aP_crc32
	;ADD ESP,8h
	;CMP EAX,DWORD PTR DS:[ESI+0Ch]
	;JNZ SHORT errHappen
	PUSH EDI
	PUSH EBX
	CALL _aP_depack_asm_fast;_aP_depack_asm
	ADD ESP,8h
	CMP EAX,DWORD PTR DS:[ESI+10h]
	JNZ SHORT errHappen
	;MOV EBX,EAX
	;PUSH EAX
	;PUSH EDI
	;CALL _aP_crc32
	;ADD ESP,8h
	;CMP EAX,DWORD PTR DS:[ESI+14h]
	;MOV EAX,EBX
	;JE SHORT noerrHappen
	JMP SHORT noerrHappen
errHappen:
	SUB EAX,EAX
noerrHappen:
	MOV DWORD PTR SS:[ESP+1Ch],EAX
	POPAD
	RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
getbit1:
    ADD     DL, DL
    JNZ     stillbitsleft1
    MOV     DL, [ESI]
    INC     ESI
    ADC     DL, DL
stillbitsleft1:
    RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
getgamma1:
    XOR    ECX, ECX
getgamma_no_ecx1:
    INC    ECX
getgammaloop1:
    CALL   getbit1
    ADC    ECX, ECX
    CALL   getbit1
    JC     getgammaloop1
    RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
_aP_depack_asm:
    PUSHAD

    MOV    ESI, [ESP+24h]  ; C calling convention
    MOV    EDI, [ESP+28h]

    CLD
    MOV    DL, 80h

    XOR    EBX, EBX

literal1:
    MOVSB
    MOV    BL, 2
nexttag1:
    CALL   getbit1
    JNC    literal1

    XOR    ECX, ECX
    CALL   getbit1
    JNC    codepair1
    XOR    EAX, EAX
    CALL   getbit1
    JNC    shortmatch1
    MOV    BL, 2
    INC    ECX
    MOV    AL, 10h
getmorebits1:
    CALL   getbit1
    ADC    AL, AL
    JNC    getmorebits1
    JNZ    domatch1
    STOSB
    JMP    SHORT nexttag1
codepair1:
    CALL   getgamma_no_ecx1
    SUB    ECX, EBX
    JNZ    normalcodepair1
    CALL   getgamma1
    JMP    SHORT domatch_lastpos1

shortmatch1:
    LODSB
    SHR    EAX, 1
    JZ     donedepacking1
    ADC    ECX, ECX
    JMP    SHORT domatch_with_2inc1

normalcodepair1:
    XCHG   EAX, ECX
    DEC    EAX
    SHL    EAX, 8h
    LODSB
    CALL   getgamma1
    CMP    EAX, 07D00h
    JAE    domatch_with_2inc1
    CMP    AH, 5h
    JAE    domatch_with_inc1
    CMP    EAX, 7fh
    JA     domatch_new_lastpos1

domatch_with_2inc1:
    INC    ECX

domatch_with_inc1:
    INC    ECX

domatch_new_lastpos1:
    XCHG   EAX, EBP
domatch_lastpos1:
    MOV    EAX, EBP

    MOV    BL, 1

domatch1:
    PUSH   ESI
    MOV    ESI, EDI
    SUB    ESI, EAX
    REP    MOVSB
    POP    ESI
    JMP    SHORT nexttag1

donedepacking1:
    SUB    EDI, [ESP + 28h]
    MOV    [ESP + 1Ch], EDI    ; return unpacked length in eax

    POPAD
    RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
_aP_depack_asm_fast:
    PUSHAD

    MOV    ESI, [ESP+24h]  ; C calling convention
    MOV    EDI, [ESP+28h]

    CLD
    MOV    DL, 80h

literal2:
    MOV    AL, [ESI]
    INC    ESI
    MOV    [EDI], AL
    INC    EDI

    MOV    EBX, 2h

nexttag2:
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft21
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft21:
;----------------
    JNC    literal2

;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft22
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft22:
;----------------
    JNC    codepair2

    XOR    EAX, EAX
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft23
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft23:
;----------------
    JNC    shortmatch2

;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft24
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft24:
;----------------
    ADC    EAX, EAX
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft25
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft25:
;----------------
    ADC    EAX, EAX
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft26
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft26:
;----------------
    ADC    EAX, EAX
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft27
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft27:
;----------------
    ADC    EAX, EAX
    JZ     thewrite2
    PUSH   EDI
    SUB    EDI, EAX
    MOV    AL, [EDI]
    POP    EDI
thewrite2:
    MOV    [EDI], AL
    INC    EDI
    MOV    EBX, 2h
    JMP    SHORT nexttag2

codepair2:

;getgammaM MACRO reg
    MOV    EAX, 1h
getmorebits21:
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft28
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft28:
;----------------
    ADC    EAX, EAX
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft29
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft29:
;----------------
    JC     getmorebits21
;----------------
    SUB    EAX, EBX
    MOV    EBX, 1h
    JNZ    normalcodepair2

;getgammaM MACRO reg
    MOV    ECX, 1h
getmorebits2:
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft30
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft30:
;----------------
    ADC    ECX, ECX
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft31
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft31:
;----------------
    JC     getmorebits2
;----------------
;domatchM MACRO reg
    PUSH   ESI
    MOV    ESI, EDI
    SUB    ESI, EBP
    REP    MOVSB
    POP    ESI
;----------------

    JMP    nexttag2

normalcodepair2:
    DEC    EAX
    SHL    EAX, 8h
    MOV    AL, [ESI]
    INC    ESI
    MOV    EBP, EAX

;getgammaM MACRO reg
    MOV    ECX, 1h
getmorebits3:
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft32
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft32:
;----------------
    ADC    ECX, ECX
;getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft33
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft33:
;----------------
    JC     getmorebits3
;----------------

    CMP    EAX, 7D00h
    SBB    ECX, 0FFFFFFFFh
    CMP    EAX, 500h
    SBB    ECX, 0FFFFFFFFh

    CMP    EAX, 80h
    ADC    ECX, 0

    CMP    EAX, 80h
    ADC    ECX, 0

;domatchM MACRO reg
    PUSH   ESI
    MOV    ESI, EDI
    SUB    ESI, EAX
    REP    MOVSB
    POP    ESI
;----------------

    JMP    nexttag2

shortmatch2:
    MOV    AL, [ESI]
    INC    ESI
    XOR    ECX, ECX
	SHR	   AL, 1h ;db     0c0h, 0e8h, 001h
    JZ     donedepacking2
    ADC    ECX, 2h
    MOV    EBP, EAX
;domatchM MACRO reg
    PUSH   ESI
    MOV    ESI, EDI
    sub    ESI, EAX
    REP    MOVSB
    POP    ESI
;----------------
    MOV    EBX, 1h
    JMP    nexttag2

donedepacking2:
    SUB    EDI, [ESP + 28h]
    MOV    [ESP + 1Ch], EDI    ; return unpacked length in eax

    POPAD
    RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
_DecompressPE:
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	;assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ESI,EDI
	ADD ESI,0F8h
	;assume esi : ptr IMAGE_SECTION_HEADER		; esi -> Section header
	XOR EDX,EDX
	;.REPEAT	   
SECTION_IS_NOT_ZERO2:
		PUSH EDX
		PUSH EAX
		; -> do only some special sections !

		CMP DWORD PTR DS:[ESI],'xet.';.text
			JZ _CHECK_IF_SIZE_IS_ZERO2
		
		CMP DWORD PTR DS:[ESI],'EDOC';CODE
			JZ _CHECK_IF_SIZE_IS_ZERO2

		CMP DWORD PTR DS:[ESI],'tad.';.data
			JZ _CHECK_IF_SIZE_IS_ZERO2

		CMP DWORD PTR DS:[ESI],'ATAD';DATA
			JZ _CHECK_IF_SIZE_IS_ZERO2

		CMP DWORD PTR DS:[ESI],'SSB';BSS
			JZ _CHECK_IF_SIZE_IS_ZERO2
		
		CMP DWORD PTR DS:[ESI],'adr.';.rdata
			JZ _CHECK_IF_SIZE_IS_ZERO2

		CMP DWORD PTR DS:[ESI],'adi.';.idata
			JZ _CHECK_IF_SIZE_IS_ZERO2

		CMP DWORD PTR DS:[ESI],'ade.';.edata
		JNZ Continue_Other_Test2
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_PROTECTION_FLAGS
			TEST DWORD PTR [EDX],OCX_TYPE_FLAG
			POP EDX
			JZ _CHECK_IF_SIZE_IS_ZERO2
Continue_Other_Test2:
		CMP DWORD PTR DS:[ESI],'rsr.';.rsrc
		JZ _RSRC_INIT
		JMP __LoopEnd2

_RSRC_INIT:	
		JMP __LoopEnd2

_CHECK_IF_SIZE_IS_ZERO2:
		;-> skip also some other sections
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd2
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd2
   
		;-> decompress it
		PUSH ESI
		PUSH EDI

		MOV ECX,DWORD PTR DS:[ESI+10h]	;[esi].SizeOfRawData
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Temp1
		MOV [EDX],ECX
		MOV ESI,DWORD PTR DS:[ESI+0Ch];[esi].VirtualAddress
		ADD ESI,EAX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Buff
		LEA EDI,[EDX]
		
		PUSH ECX
		PUSH ESI
		PUSH EDI
		CALL _CopyMemory; Copy Section to spare buffer
		ADD ESP,0Ch

		;----- Deceive -----
		MOV EAX,ESI
		MOV DWORD PTR [EAX],0C3619060h
		CALL EAX
		;-------------------

		MOV EAX,DWORD PTR [EDI]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_BuffSize
		MOV [EDX],EAX

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwCompressType
		MOV EAX,[EDX]
		CMP EAX,00h
		JNZ aPLib_COMPRESS
;UPX_COMPRESS:

		ADD EDI,04h

		MOV EAX,NULL
		PUSH EAX

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_BuffSize
		LEA EAX,[EDX]
		PUSH EAX;->destination size
	
		PUSH ESI;PUSH ESI;->destination buffer

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Temp1
		LEA EAX,[EDX]
		PUSH EAX;->source size

		PUSH EDI;PUSH EDI;->sourc buffer

		CALL lzo1f_decompress_asm_fast_safe
		; lzo1f_decompress_asm_fast_safe
		;				(src,src_len,dst,dst_len,wrkmem )
		ADD ESP,0Ch

aPLib_COMPRESS:
		PUSH ESI;PUSH ESI;->destination buffer

		PUSH EDI;PUSH EDI;->sourc buffer

		CALL _aPsafe_depack_asm_fast
		;aPsafe_depack_asm_fast(source,destination);
		ADD ESP,08h

		MOV ESI,EDI
		;assume edi : nothing

		MOV EAX,0
		PUSH EAX
		PUSH ECX
		PUSH EDI
		CALL _FillMemory
		ADD ESP,0Ch
		;FillMemory(Destination,Length,Fill);

		; FUNNY JUMP :)
		MOV EDX,EBP;MOV EDX,EBX
		ADD EDX,OFFSET SecDecryptContinue12
		LEA EAX, [EDX]
		PUSH EAX
		RETN
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------
SecDecryptContinue12:	   
		POP EDI
		POP ESI
__LoopEnd2:   
		ADD ESI,28h;SIZEOF IMAGE_SECTION_HEADER
		POP EAX
		POP EDX
		INC EDX
	CMP DX,WORD PTR DS:[EDI+6]
	JNZ SECTION_IS_NOT_ZERO2
	RETN
AfterDeCryptionContinue:
;----- CHECK FOR DEBUG API's 1-----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JNZ NO_DEBUG_CHECK1
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IsDebuggerPresent
		CALL DWORD PTR[EDX]
		OR EAX,EAX
		JE NO_DEBUG_CHECK1
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_dwParentProcess
			MOV EAX,[EDX]
			PUSH EAX
			PUSH 1h
			PUSH 1F0FFFh
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_OpenProcess
			CALL DWORD PTR[EDX]
			PUSH 0
			PUSH EAX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_TerminateProcess
			CALL DWORD PTR[EDX]
NO_DEBUG_CHECK1:
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------

;----------------------------------------------------------
;AntiDebug()
;----------------------------------------------------------
_AntiDebug2:
	XOR EAX,EAX
	MOV ECX,49h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Buff
	LEA EDI,[EDX]
	PUSH EDI
	REP STOS DWORD PTR ES:[EDI]
	POP EDI
	MOV DWORD PTR SS:[EDX],128h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetCurrentProcessId
	CALL DWORD PTR[EDX]
	PUSH 0
	PUSH 2
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Temp1
	MOV [EDX],EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CreateToolhelp32Snapshot
	CALL DWORD PTR[EDX]
	MOV ESI,EAX
	MOV EAX,EBP
	ADD EAX,OFFSET _RO_Buff
	PUSH EAX
	PUSH ESI
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Process32First
	CALL DWORD PTR[EDX]
	TEST EAX,EAX
	JE ENDOFCHECKPROCESS2
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Buff
		LEA ECX,[EDX]
		PUSH ECX
		PUSH ESI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Process32Next
		CALL DWORD PTR[EDX]
		TEST EAX,EAX
		JE ENDOFCHECKPROCESS2
		XOR EBX,EBX
		JMP CHECKNEXTPROCESS2
		LEA ECX,DWORD PTR DS:[ECX]
CHECKNEXTPROCESS2: 
			PUSH ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			MOV EAX,[EDX+8h]
			LEA ESI,[EDX+24h]
			MOV EDI,ESI
			PUSH ESI
			PUSH EDI
			CALL _CharUpperBuff
			ADD ESP,08h
			PUSH EDI
			PUSH ESI
			CALL _GetFileNameFromPath
			ADD ESP,08h
			MOV ESI,EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_EXPLORER_EXE
			LEA EDI,[EDX];ASCII "EXPLORER.EXE"
			MOV ECX,0Dh
			XOR EDX,EDX
			REPE CMPSB
			JNZ EXPLORER_NOT_FOUND2
				CMP EBX,0
				JZ MAIN_EXPLORER2
				JMP EXPLORER_NOT_FOUND2
MAIN_EXPLORER2:	MOV EBX,EAX
EXPLORER_NOT_FOUND2:
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Temp1
			CMP EAX,DWORD PTR SS:[EDX]
			POP EDX
			JNZ IT_IS_NOT_MYCHILD2
				PUSH EDX
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_Buff
				MOV EAX,[EDX+18h]
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_dwParentProcess
				MOV [EDX],EAX
				POP EDX
IT_IS_NOT_MYCHILD2:	
			POP ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA ECX,[EDX]
			PUSH ECX
			PUSH ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Process32Next
			CALL DWORD PTR[EDX]
			TEST EAX,EAX
			JNZ CHECKNEXTPROCESS2
ENDOFCHECKPROCESS2:
	;------some crazy work!------
	db	08h	dup(0EEh)
	;----------------------------

;------ PREPARE THE OEP JUMP EXCEPTION :) ------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JNZ DLL_DONOT_NEET_THIS
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EBX,[EDX]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade
		MOV EAX,[EDX]
		ROR EAX,10h
		XOR EAX,'dane'
		ADD EBX,EAX
		ROR EBX,07h
		MOV	[ESP+010h],EBX
		MOV EDX,EBP
		ADD EDX,OFFSET SehHandler_OEP_Jump
		LEA EBX,[EDX]
		MOV [ESP+01Ch],EBX
DLL_DONOT_NEET_THIS:
		;----- SET Index Variable of TLS table to 0 -----
		; check whether there's a tls table
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EDI,DWORD PTR [EDX]
		ADD EDI,DWORD PTR [EDI+03Ch]; edi -> pointer to PE header
		;assume edi : ptr IMAGE_NT_HEADERS
		MOV EBX,DWORD PTR [EDI+0C0h];OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress
		;assume edi : nothing
		CMP EBX,0	; no tls section
		JZ SkipTlsFix
		ADD EBX,DWORD PTR [EDX]	; ebx -> pointer to tls table
		;assume ebx : ptr IMAGE_TLS_DIRECTORY32
		MOV EAX,DWORD PTR [EBX+08h]
		MOV DWORD PTR [EAX],0
		;assume ebx : nothing	
	SkipTlsFix:
		;----- CRC COMPARE -----
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwCalcedCRC
		MOV EAX,DWORD PTR [EDX]

		OR EAX,EAX
		JE INIT_IMPORT_TABLE
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_dwOrgChecksum
			CMP EAX,DWORD PTR [EDX]
			JE NotSkipInitIt
				JMP SkipInitIt
	NotSkipInitIt:

	INIT_IMPORT_TABLE:
		;----- INIT IMPORT TABLE -----
		; 0 - an error occurred
		; 1 - IT initialized successfully
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IIDInfo
		LEA ESI,[EDX];ESI -> pointer to the current IID
		;ASSUME ESI : PTR sItInfo	

		;----------------- PREPARE API REDIRECTION ----------------
		PUSH EBX
	MOV EBX,EBP
	ADD EBX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EBX],API_REDIRECT_FLAG
	JZ DonotAPIRedirect
		PUSH ESI
		MOV EBX,EBP
		ADD EBX,OFFSET _RO_Buff
		LEA  EDI,[EBX]
		;ASSUME EDI : PTR sReThunkInfo
		XOR  ECX, ECX
Kernel32IIDInfoLoop:   
		CMP DWORD PTR DS:[ESI+4],0
		JZ EndOfKernel32IIDInfo
			MOV EDX,DWORD PTR DS:[ESI+4];[ESI].FirstThunk
			MOV EBX,EBP
			ADD EBX,OFFSET _RO_dwImageBase
			ADD EDX,DWORD PTR [EBX]
Kernel32FunInfoLoop:
			CMP DWORD PTR DS:[EDX],0
			JZ EndOfKernel32FuncInfo
				INC ECX
				ADD EDX,4
			JMP Kernel32FunInfoLoop
EndOfKernel32FuncInfo:
			ADD ESI,0Ch;SIZEOF sItInfo
		JMP Kernel32IIDInfoLoop
EndOfKernel32IIDInfo:

		; allocate memory for the api stubs
		XOR EDX,EDX
		MOV EAX,5;SIZEOF sApiStub
		MUL ECX
		PUSH EAX
		PUSH GMEM_FIXED
		MOV EBX,EBP
		ADD EBX,OFFSET _RO_GlobalAlloc
		CALL DWORD PTR[EBX]
		OR EAX,EAX; fatal exit
		JNZ DonotDofatalexit
			ADD ESP,4
			POPAD
			RETN
DonotDofatalexit:
		MOV DWORD PTR DS:[EDI],EAX;[EDI].ApiStubMemAddr
		MOV DWORD PTR DS:[EDI+4],EAX;[EDI].pNextStub
   		POP  ESI
DonotAPIRedirect:
	POP EBX
	; start with the real routine
DllIIDInfoLoop:
	CMP DWORD PTR DS:[ESI+4],0
	JZ EndOfDllIIDInfo;
	   ; load the library
		MOV EBX,DWORD PTR DS:[ESI];[esi].DllNameRVA
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		ADD EBX,DWORD PTR [EDX]
		; decrypt dll string
		MOV EAX,EBX	   
		CALL _EnDeCryptString
		MOV EDX,EBP
		ADD EDX,OFFSET InitITContinue1
		LEA EAX, [EDX]; goto InitITContinue1
		PUSH EAX
		RETN

		;DWORD EnDeCryptString(char* Base,DWORD VA)
_EnDeCryptString:
  	PUSH ESI
  	PUSH EDI   		
	MOV ESI,EAX
	MOV EDI,EAX
DllCryptLoop:
		LODS BYTE PTR DS:[ESI]
		ROR AL,4
		STOS BYTE PTR ES:[EDI]
		CMP BYTE PTR DS:[EDI],0
	JNZ DllCryptLoop
	POP EDI
	POP ESI
	RETN	

InitITContinue1:
		PUSH EBX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_LoadLibrary
		CALL DWORD PTR[EDX]
		TEST EAX,EAX
		JZ SkipInitIt	
		; zero dll name
		PUSH EDX
		PUSH EAX; save dll base
		;----------------------------------------------------------
		;---------------- Delete Import Information ---------------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_PROTECTION_FLAGS
		TEST DWORD PTR [EDX],DESTROY_IMPORT_FLAG
		JZ DontKillDllName
			; push return address
			MOV EDX,EBP
			ADD EDX,OFFSET DontKillDllName
			LEA EAX,[EDX]
			PUSH EAX ; push return address :)
			MOV EAX,EBX
			JMP KillString
DontKillDllName:
		POP EBX	; EBX -> library handle
		POP EDX
		; process the (Original-)FirstThunk members
		MOV ECX,DWORD PTR DS:[ESI+8];[esi].OrgFirstThunk
		OR ECX,ECX
		JNZ OrgFirstThunkNotZero1
			MOV ECX,DWORD PTR DS:[ESI+4];[esi].FirstThunk
OrgFirstThunkNotZero1: 
		PUSH EBX
		MOV EBX,EBP
		ADD EBX,OFFSET _RO_dwImageBase
		ADD ECX,[EBX]	; ecx -> pointer to current thunk
		MOV EDX,DWORD PTR DS:[ESI+4];[esi].FirstThunk
		ADD EDX,[EBX]	; edx -> pointer to current thunk (always the non-original one)
		POP EBX
FuncIIDInfoLoop:
		CMP DWORD PTR DS:[ECX],0
		JZ EndOfFuncIIDInfo
			TEST DWORD PTR [ECX],IMAGE_ORDINAL_FLAG32; is it an ordinal import ?
			JNZ __OrdinalImp
	  		; process a name import
				MOV EAX,DWORD PTR [ECX]
				ADD EAX,2
				PUSH EBX
				MOV EBX,EBP
				ADD EBX,OFFSET _RO_dwImageBase
				ADD EAX,[EBX]; eax points now to the Name of the Import
				POP EBX

				PUSH EAX
				CALL _EnDeCryptString
				POP  EAX

				MOV EDI,EAX	; save the API name pointer for destroying it later

				PUSH EDX
				PUSH ECX; save the Thunk pointers

				PUSH EAX
				PUSH EBX
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_GetProcAddress
				CALL DWORD PTR[EDX]

				OR EAX,EAX
				JNZ GetProcAddressNotNULL
					POP ECX
					POP EDX
					JMP SkipInitIt
GetProcAddressNotNULL:
				POP ECX
				POP EDX
				;->kill API name			
				PUSH EDX
  				PUSHAD
				;----------------------------------------------------------
				;---------------- Delete Import Information ---------------
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_PROTECTION_FLAGS
				TEST DWORD PTR[EDX],DESTROY_IMPORT_FLAG
  				JZ  DontKillApiName
					MOV EDX,EBP
					ADD EDX,OFFSET DontKillApiName
  					LEA EAX, [EDX]	; push return address
  					PUSH EAX
					MOV EAX, EDI
					JMP KillString
DontKillApiName:
				POPAD
				POP EDX
				;-> paste API address
				MOV DWORD PTR [EDX],EAX	   
				JMP __NextThunkPlease

__OrdinalImp:
			; process an ordinal import
			PUSH EDX
			PUSH ECX	; save the thunk pointers
			MOV EAX,DWORD PTR [ECX]
			SUB EAX,080000000h
			PUSH EAX
			PUSH EBX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_GetProcAddress
			CALL DWORD PTR[EDX]
			TEST EAX,EAX
			JZ SkipInitIt
			POP ECX
			POP EDX
			MOV DWORD PTR [EDX],EAX
__NextThunkPlease:
	 		; eax = Current Api address
   			; ebx = dll base
   			; edx = non-org thunk pointer
			;----------------------------------------------------------
			;----------------- PREPARE API REDIRECTION ----------------
			PUSH ECX
			MOV ECX,EBP
			ADD ECX,OFFSET _RO_PROTECTION_FLAGS
			TEST DWORD PTR [ECX],API_REDIRECT_FLAG
			JZ DonotAPIRedirect2
				MOV ECX,EBP
				ADD ECX,OFFSET _RO_bNT
				CMP DWORD PTR [ECX],0
				JZ WindowsNotNT
					CMP EBX,070000000h
						JB CHECK_0x70000000
					CMP EBX,077FFFFFFh
						JBE FinishThunkRedDo
CHECK_0x70000000:
						JMP	SkipThunkRed
					JMP FinishThunkRedDo
WindowsNotNT:
					CMP EBX,080000000h
					JNB FinishThunkRedDo
						JMP SkipThunkRed
FinishThunkRedDo:
				PUSH EDI
				PUSH ESI
				MOV ECX,EBP
				ADD ECX,OFFSET _RO_Buff
				LEA EDI,[ECX]
				;ASSUME EDI : PTR sReThunkInfo
				MOV ESI,DWORD PTR DS:[EDI+4];[EDI].pNextStub
   				MOV [EDX],ESI; make the thunk point to stub mem
   				SUB EAX,ESI
   				SUB EAX,5; sizeof E9XXXXXXXX - Jump long
   				MOV BYTE PTR [ESI],0E9h
				MOV DWORD PTR [ESI+1],EAX
				ADD DWORD PTR DS:[EDI+4],5;ADD [EDI].pNextStub,SIZEOF sApiStub
				POP ESI
				POP EDI
SkipThunkRed:
DonotAPIRedirect2:
			POP ECX
   			ADD ECX,4
			ADD EDX,4
			JMP FuncIIDInfoLoop 
EndOfFuncIIDInfo:
		ADD ESI,0Ch;SIZEOF sItInfo	 make esi point to the next IID
		JMP DllIIDInfoLoop
EndOfDllIIDInfo:
	XOR EAX,EAX
	INC EAX
;------------------------------
SkipInitIt:
	CMP EAX,1
	JE ERASE_PE_HEADER
		; exit
		POPAD
		RETN
ERASE_PE_HEADER:
	;----- ERASE PE HEADER ------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],ERASE_HEADER_FLAG
  	JZ SkipEraseHeader
		; zero the header
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EDI,DWORD PTR [EDX]
		ADD EDI,DWORD PTR [EDI+03Ch]; edi -> pointer to PE header
		;assume edi : ptr IMAGE_NT_HEADERS
		MOV ESI,DWORD PTR [EDX]
		MOV ECX,DWORD PTR [EDI+54H];.OptionalHeader.SizeOfHeaders
		;assume edi : nothing
ZeroMemLoop:
			MOV BYTE PTR [ESI],0
			INC ESI
        LOOP ZeroMemLoop
SkipEraseHeader:

;------ CHECK AGAIN LOADER CRC & COMPARE ------
	MOV EDX,EBP
	ADD EDX,OFFSET DepackerCode
  	LEA EAX,DWORD PTR [EDX]
	MOV ECX,OFFSET OEP_JUMP_CODE_START 
	SUB	ECX,OFFSET DepackerCode;ECX->LOADER_CRC_CHECK_SIZE
  	JMP SM10
		RETN;INT 09h;DB   0E9h
  	SM10:
  	PUSH ECX
	PUSH EAX
	CALL _GetCheckSum
	ADD ESP,08h

  	JMP SM11
  		RETN;INT 0Ch;DB   0C7h
  	SM11:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwLoaderCRC
  	MOV EBX,DWORD PTR [EDX]
	XOR EAX,EBX
	JE DECRYPT_ENTRYPOINT
		JMP SM12
		RETN;INT 3;DB 2C 
SM12:
		POPAD
		JMP SM13
		NOP;INT 3;DB E8
SM13:
		RETN

		;----- DECRYPT ENTRYPOINT JUMP CODE -----
DECRYPT_ENTRYPOINT:
	MOV EDX,EBP
	ADD EDX,OFFSET OEP_JUMP_CODE_START
  	LEA EDI,[EDX]
  	MOV ESI,EDI
	LEA EDI,[EDX]
	MOV ECX,OFFSET OEP_JUMP_CODE_END
	SUB ECX,OFFSET OEP_JUMP_CODE_START;ECX->CRYPT_OEP_JUMP_SIZE
	JMP OepJumpDecryptLoop
	INT 3
	INT 3
	INT 3
	INT 3
OepJumpDecryptLoop:
		LODS BYTE PTR DS:[ESI]
_patch3_LABEL_OepJumpDecryptLoop	LABEL	DWORD
		db	030h	dup(0FFh)
		STOS BYTE PTR ES:[EDI]
	LOOP OepJumpDecryptLoop
	MOV EDX,EBP
	ADD EDX,OFFSET OEP_JUMP_CODE_START
	LEA EAX,[EDX]
	PUSH EAX
	RET
	;-----------------------
	INT 3
	INT 3
	INT 3
	INT 3
	;----- JUMP TO OEP -----
_patch3_LABEL_OEP_JUMP_CODE_START_	LABEL	DWORD
OEP_JUMP_CODE_START:
	;----- CHECK FOR PARENT 2	 -----
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwParentProcess
		MOV EAX,[EDX]
		OR EAX,EAX
		JNZ PARENT_EXIST2
			POPAD
			RETN
PARENT_EXIST2:
;----- CHECK FOR DEBUG API's 2-----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JNZ NO_DEBUG_CHECK2
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IsDebuggerPresent
		CALL DWORD PTR[EDX]
		OR EAX,EAX
		JE FREEZE_PARENT2
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_dwParentProcess
			MOV EAX,[EDX]
			PUSH EAX
			PUSH 1h
			PUSH 1F0FFFh
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_OpenProcess
			CALL DWORD PTR[EDX]
			PUSH 0
			PUSH EAX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_TerminateProcess
			CALL DWORD PTR[EDX]
FREEZE_PARENT2:
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_dwParentProcess
			MOV EAX,[EDX]
			PUSH EAX
			PUSH 1h
			PUSH 1F0FFFh
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_OpenProcess
			CALL DWORD PTR[EDX]
			PUSH INFINITE
			PUSH EAX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_WaitForInputIdle
			CALL DWORD PTR[EDX]
NO_DEBUG_CHECK2:
;----- CHECK FOR DEBUG API's 3-----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JNZ DLL_DEBUG_CHECK3
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IsDebuggerPresent
		CALL DWORD PTR[EDX]
		OR EAX,EAX
		JE SECOND_SI_CHECK
			CALL EAX
			OR EAX,EAX
			JE SECOND_SI_CHECK
				POPAD
				RETN
		JMP SECOND_SI_CHECK
DLL_DEBUG_CHECK3:
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IsDebuggerPresent
		CALL DWORD PTR[EDX]
		OR EAX,EAX
		JE SECOND_SI_CHECK
SECOND_SI_CHECK:
	;------ SECOND SI CHECK ------
	; doesn't work on NT
	; install SEH frame
	;----------------------------------------------------------
	;IsSoftIce95Loaded()
	;----------------------------------------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],CHECK_SI_FLAG
	JZ   SkipSICheck3
		;------ CHECK FOR SOFTICE 95 ------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szSoftICE95
		LEA EDI,[EDX]
		PUSH NULL
		PUSH FILE_ATTRIBUTE_NORMAL
		PUSH OPEN_EXISTING
		PUSH NULL
		PUSH (FILE_SHARE_READ OR FILE_SHARE_WRITE)
		PUSH (GENERIC_READ OR GENERIC_WRITE)
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateFile
		CALL DWORD PTR[EDX]
		CMP EAX,_INVALID_HANDLE_VALUE
		JE CheckforNTICE3
			MOV EDI,EAX
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_CloseHandle
			CALL DWORD PTR[EDX]
			PUSH 0
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_ExitThread
			CALL DWORD PTR[EDX]
		;------ CHECK FOR SOFTICE NT ------
CheckforNTICE3:
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szSoftICENT
		LEA EDI,[EDX]
		PUSH NULL
		PUSH FILE_ATTRIBUTE_NORMAL
		PUSH OPEN_EXISTING
		PUSH NULL
		PUSH (FILE_SHARE_READ OR FILE_SHARE_WRITE)
		PUSH (GENERIC_READ OR GENERIC_WRITE)
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateFile
		CALL DWORD PTR[EDX]
		CMP EAX,_INVALID_HANDLE_VALUE
		JE SkipSICheck3
			MOV EDI,EAX
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_CloseHandle
			CALL DWORD PTR[EDX]
			PUSH 0
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_ExitThread
			CALL DWORD PTR[EDX]
SkipSICheck3:
SkipSICheck4:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JZ THIS_FILE_ISNOT_DLL
		MOV EDX,EBP
		ADD EDX,OFFSET OepJumpCodeCont2
		LEA EAX,[EDX]
		PUSH EAX
		RET    
THIS_FILE_ISNOT_DLL:
	MOV EDX,EBP
	ADD EDX,OFFSET OepJumpCodeCont1
	LEA EAX,[EDX]
	PUSH EAX
	RET    

; ------ OEP SEH HANDLER ------
;SehHandler_OEP_Jump PROC C pExcept:DWORD,pFrame:DWORD,pContext:DWORD,pdestination:DWORD
SehHandler_OEP_Jump:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDI
	MOV EAX,DWORD PTR SS:[EBP+010h];pContext
	;ASSUME EAX : PTR CONTEXT

	; restore original seh handle
	MOV EDI,DWORD PTR DS:[EAX+0C4h]	;[EAX].regEsp
	PUSH DWORD PTR DS:[EDI]
	XOR EDI,EDI
	POP DWORD PTR FS:[EDI]

	; kill seh frame
	ADD DWORD PTR DS:[EAX+0C4h],8	;[EAX].regEsp

	; set EIP to the OEP
	MOV EDI,DWORD PTR DS:[EAX+0A4h];[EAX].regEbx; EDI -> OEP
	ROL EDI,7
	MOV DWORD PTR DS:[EAX+0B8h],EDI;[EAX].regEip

	MOV EAX,0;ExceptionContinueExecution
	;ASSUME EAX : NOTHING
	POP EDI
	LEAVE
	RETN
;SehHandler_OEP_Jump ENDP
;-----------------------------------------
	NOP
	NOP
	NOP
	NOP
_RO_bNT_Mirror:
	NOP
	NOP
	NOP
	NOP
_RO_dwImageBase_Mirror:
	NOP
	NOP
	NOP
	NOP
_RO_dwOrgEntryPoint_Shade_Mirror:
	NOP
	NOP
	NOP
	NOP
UNLOAD_DLL:
	;----------------------------	
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase_Mirror
	MOV EBX,[EDX]
	MOV EDX,EBX
	PUSH EDX
	MOV EAX,ESP
CheckDLLPoint0_mirror:
		ADD EAX,4
		MOV EDX,[EAX]
		CMP EBX,EDX
		MOV DWORD PTR[EAX-28h],00h
		JNZ CheckDLLPoint0_mirror

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT_Mirror
	MOV ECX,[EDX]
	CMP ECX,01h
	JZ NOT_WIN98_mirror
CheckDLLPoint1_mirror:
		ADD EAX,4
		MOV EDX,[EAX]
		CMP EBX,EDX
		MOV DWORD PTR[EAX-28h],00h
		JNZ CheckDLLPoint1_mirror
NOT_WIN98_mirror:

	SUB EAX,4
	PUSH EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase_Mirror
	MOV EBX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade_Mirror
	MOV EAX,[EDX]
	ROR EAX,10h
	XOR EAX,'dane'
	ADD EBX,EAX

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT_Mirror
	MOV ECX,[EDX]

	PUSH EBX
	PUSH ECX
	XOR AL,AL

	MOV EDX,EBP
	ADD EDX,OFFSET OepJumpCodeCont2
	LEA EDI,[EDX]
	MOV ECX,OFFSET OEP_JUMP_CODE_END
	SUB ECX,OFFSET OepJumpCodeCont2
	REP STOS BYTE  PTR ES:[EDI]
		
	POP ECX
	POP EBX
	POP EAX
	POP EDX

	CMP ECX,01h
	JZ WINNT_PREPARE_OEP_mirror
		
		;MOV ESI,EDX
		;MOV EBP,ESP
		;ADD EBP,1C4h
		;POPAD	; RESTORE STARTUP REGS
				; After this POPAD:
				; EAX - OEP Seh handler
				; EBX - OEP (rored)*/
		;ADD ESP,04h
		MOV ECX,EBX
		MOV EDI,[EAX-020h]
		MOV ESI,[EAX-01Ch]
		MOV EBP,[EAX-018h]
		;MOV ESP,[ESP-014h]
		MOV EBX,[ESP-04h];[EAX-010h]
		MOV EDX,[EAX-0Ch]
		;MOV ECX,[EAX-08h]
		;MOV EAX,[ESP-04h]
		MOV ESP,EAX
		MOV EAX,EBX
		JMP ECX
WINNT_PREPARE_OEP_mirror:
;		MOV ESI,ESP
;		ADD ESI,10h
;		MOV EBP,ESP
;		ADD EBP,1Ch
		;POPAD	; RESTORE STARTUP REGS
				; After this POPAD:
				; EAX - OEP Seh handler
				; EBX - OEP (rored)*/
		;ADD ESP,04h
		MOV ECX,EBX
		MOV EDI,[EAX-020h]
		MOV ESI,[EAX-01Ch]
		MOV EBP,[EAX-018h]
		;MOV ESP,[ESP-014h]
		MOV EBX,[EAX-004h];[EAX-010h]
		MOV EDX,[EAX-0Ch]
		;MOV ECX,[EAX-08h]
		;MOV EAX,[ESP-04h]
		MOV ESP,EAX
		MOV EAX,EBX
		JMP ECX
	;----------------------------	
OepJumpCodeCont2:
;------ install OEP JUMP SEH frame ------
	;----------------------------	

	;----- CHECK FOR PARENT 3	 -----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwParentProcess
	MOV EAX,[EDX]
	OR EAX,EAX
	JNZ PARENT_EXIST32
		POPAD
		RETN
PARENT_EXIST32:

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EBX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET 	_RO_dwImageBase_Mirror
	MOV [EDX],EBX
	MOV EDX,EBX
	PUSH EDX
	MOV EAX,ESP
CheckDLLPoint0:
		ADD EAX,4
		MOV EDX,[EAX]
		CMP EBX,EDX
		MOV DWORD PTR[EAX-28h],00h
		JNZ CheckDLLPoint0

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT
	MOV ECX,[EDX]
	CMP ECX,01h
	JZ NOT_WIN98
CheckDLLPoint1:
		ADD EAX,4
		MOV EDX,[EAX]
		CMP EBX,EDX
		MOV DWORD PTR[EAX-28h],00h
		JNZ CheckDLLPoint1
NOT_WIN98:

	SUB EAX,4
	PUSH EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EBX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade
	MOV EAX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade_Mirror
	MOV [EDX],EAX
	ROR EAX,10h
	XOR EAX,'dane'
	ADD EBX,EAX

	MOV EDX,EBP
	ADD EDX,OFFSET Reserve_for_dll
	MOV DWORD PTR[EDX],0E901EB90h
	ADD EDX,04h
	MOV DWORD PTR[EDX],0E901EB90h


	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT
	MOV ECX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT_Mirror
	MOV [EDX],ECX

	PUSH EBX
	PUSH ECX
	XOR AL,AL

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_LoadLibrary
	LEA EDI,[EDX]
	MOV ECX,OFFSET VARIABLE_CRYPT_END
	SUB ECX,OFFSET _RO_LoadLibrary
	REP STOS BYTE  PTR ES:[EDI]
		
	MOV EDX,EBP
	ADD EDX,OFFSET PackDecrypt;DepackerCode
	LEA EDI,[EDX]
	MOV ECX,OFFSET SehHandler_OEP_Jump;OEP_JUMP_CODE_START
	SUB ECX,OFFSET PackDecrypt;DepackerCode
	REP STOS BYTE PTR ES:[EDI]

	MOV EDX,EBP
	ADD EDX,OFFSET OepJumpCodeCont1;OEP_JUMP_CODE_END
	LEA EDI,[EDX]
	MOV ECX,OFFSET LOADER_CRYPT_END
	SUB ECX,OFFSET OepJumpCodeCont1;OEP_JUMP_CODE_END
	REP STOS BYTE  PTR ES:[EDI]

	POP ECX
	POP EBX
	POP EAX
	POP EDX

	CMP ECX,01h
	JZ WINNT_PREPARE_OEP
		
		;MOV ESI,EDX
		;MOV EBP,ESP
		;ADD EBP,1C4h
		;POPAD	; RESTORE STARTUP REGS
				; After this POPAD:
				; EAX - OEP Seh handler
				; EBX - OEP (rored)*/
		;ADD ESP,04h
		MOV ECX,EBX
		MOV EDI,[EAX-020h]
		MOV ESI,[EAX-01Ch]
		MOV EBP,[EAX-018h]
		;MOV ESP,[ESP-014h]
		MOV EBX,[ESP-04h];[EAX-010h]
		MOV EDX,[EAX-0Ch]
		;MOV ECX,[EAX-08h]
		;MOV EAX,[ESP-04h]
		MOV ESP,EAX
		MOV EAX,EBX
		JMP ECX
WINNT_PREPARE_OEP:
;		MOV ESI,ESP
;		ADD ESI,10h
;		MOV EBP,ESP
;		ADD EBP,1Ch
		;POPAD	; RESTORE STARTUP REGS
				; After this POPAD:
				; EAX - OEP Seh handler
				; EBX - OEP (rored)*/
		;ADD ESP,04h
		MOV ECX,EBX
		MOV EDI,[EAX-020h]
		MOV ESI,[EAX-01Ch]
		MOV EBP,[EAX-018h]
		;MOV ESP,[ESP-014h]
		MOV EBX,[EAX-004h];[EAX-010h]
		MOV EDX,[EAX-0Ch]
		;MOV ECX,[EAX-08h]
		;MOV EAX,[ESP-04h]
		MOV ESP,EAX
		MOV EAX,EBX
		JMP ECX
	;----------------------------	
;OEP_JUMP_CODE_END2:
;-----------------------------------------
;------ install OEP JUMP SEH frame ------
OepJumpCodeCont1:
	;---- ZERO THE LOADER CODE AND DATA ----
	;----- CHECK FOR PARENT 3	 -----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwParentProcess
	MOV EAX,[EDX]
	OR EAX,EAX
	JNZ PARENT_EXIST31
		POPAD
		RETN
PARENT_EXIST31:

	XOR AL,AL

	MOV EDX,EBP
	ADD EDX,OFFSET CallMe0
	MOV BYTE PTR[EDX],0C3h

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_LoadLibrary
	LEA EDI,[EDX]
	MOV ECX,OFFSET VARIABLE_CRYPT_END
	SUB ECX,OFFSET _RO_LoadLibrary
	REP STOS BYTE PTR ES:[EDI]

	MOV EDX,EBP
	ADD EDX,OFFSET MAIN1;DepackerCode
	LEA EDI,[EDX]
	MOV ECX,OFFSET SehHandler_OEP_Jump
	SUB ECX,OFFSET MAIN1;DepackerCode
	REP STOS BYTE PTR ES:[EDI]

	MOV EDX,EBP
	ADD EDX,OFFSET OEP_JUMP_CODE_END
	LEA  EDI,[EDX]
	MOV ECX,OFFSET LOADER_CRYPT_END
	SUB ECX,OFFSET OEP_JUMP_CODE_END
	REP STOS BYTE PTR ES:[EDI]

	POPAD	; RESTORE STARTUP REGS
			; After this POPAD:
			; EAX - OEP Seh handler
			; EBX - OEP (rored)
	
  	;------ install OEP JUMP SEH frame ------	
	PUSH EAX
	XOR  EAX, EAX
	PUSH DWORD PTR FS:[EAX]
	MOV DWORD PTR FS:[EAX],ESP

	JMP  SM3
	RETN	;DB 87
SM3: 		; the seh handler will set EIP to the OEP :)


_patch3_LABEL_OEP_JUMP_CODE_END_	LABEL	DWORD
OEP_JUMP_CODE_END:
	NOP
	INT 3
	INT 3
	INT 3
	INT 3
	; -------- KILL STRING --------
; EAX = ASCII string address
KillString:
	JMP KillStr2
KillStr1:
		MOV BYTE PTR DS:[EAX],0
		INC EAX
KillStr2:
		CMP BYTE PTR DS:[EAX],0
	JNZ SHORT KillStr1
	RETN

; ------- SEH HANDLER 1 -------
;SehHandler1 PROC C pExcept:DWORD,pFrame:DWORD,pContext:DWORD,pdestination:DWORD
SehHandler1:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDI
	MOV EAX,DWORD PTR SS:[EBP+010h]	;pContext
	;ASSUME EAX : PTR CONTEXT
	MOV EDI,DWORD PTR DS:[EAX+09Ch]	;[EAX].regEdi
	MOV EDX,EDI
	ADD EDX,OFFSET _RO_SEH_SaveEip
	PUSH DWORD PTR DS:[EDX];[EDI+SEH.SaveEip]
	POP DWORD PTR DS:[EAX+0B8h]		;[eax].regEip
	MOV DWORD PTR DS:[EAX+0B4h],EDI	;[eax].regEbp
	MOV DWORD PTR DS:[EAX+0B0h],04h	;[EAX].regEax
	; SI NOT detected !
	MOV EAX,0;ExceptionContinueExecution
	;ASSUME EAX : NOTHING
	POP EDI
	LEAVE
	RETN

	; ------- SEH HANDLER 2 -------
;SehHandler2 PROC C pExcept:DWORD,pFrame:DWORD,pContext:DWORD,pdestination:DWORD
;SehHandler2:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDI
	MOV EAX,DWORD PTR SS:[EBP+010h]	;pContext
	;ASSUME EAX : PTR CONTEXT
	MOV EDI,DWORD PTR DS:[EAX+09Ch]	;[EAX].regEdi
	MOV EDX,EDI
	ADD EDX,OFFSET _RO_SEH_SaveEip
	PUSH DWORD PTR DS:[EDX]			;[EDI+SEH.SaveEip]
	POP DWORD PTR DS:[EAX+0B8h]		;[eax].regEip
	MOV DWORD PTR DS:[EAX+0B4h],EDI	;[eax].regEbp
	MOV DWORD PTR DS:[EAX+09Ch],0	;[EAX].regEdi
	; SI NOT detected !
	MOV EAX,0	;ExceptionContinueExecution
	;ASSUME EAX : NOTHING
	POP EDI
	LEAVE
	RETN
	;-------------- PRE VARIABLE PE LOADER CODE ---------------
_patch3_PRE_VARIABLE_START_	LABEL	DWORD
	_RO_dwCompressType:			;	DD 0
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwDEPACKER_SECTION_NAME:;	DD 'Cy'
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwImageBase:	
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwCalcedCRC:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwParentProcess:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_IIDInfo:
;_RO_IIDInfo0:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo1:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo2:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo3:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo4:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo5:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo6:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo7:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo8:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo9:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo10:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo11:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo12:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo13:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo14:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo15:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo16:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo17:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo18:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo19:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo20:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo21:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo22:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo23:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo24:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo25:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo26:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo27:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo28:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo29:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo0:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo1:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo2:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo3:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo4:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo5:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo6:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo7:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo8:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo9:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo10:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo11:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo12:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo13:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo14:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo15:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo16:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo17:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo18:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo19:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo20:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo21:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo22:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo23:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo24:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo25:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo26:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo27:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo28:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
;_RO_IIDInfo29:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
_RO_SEH:
;_RO_SEH_OrgEsp:
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SEH_OrgEbp:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_SEH_SaveEip:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_PROTECTION_FLAGS:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwLoaderCRC:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_bNT:
		INT 3
		INT 3
		INT 3
		INT 3
_patch3_LABEL_RO_SectionNames_START_	LABEL	DWORD
_RO_SectionNames:
;_RO_SectionName0:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName1:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName2:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName3:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName4:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName5:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName6:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName7:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName8:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName9:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName10:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName11:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName12:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName13:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName14:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName15:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName16:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName17:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName18:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_SectionName19:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwOrgEntryPoint:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_CODE_Size: ;CODE_Size	;.text/CODE 
		INT 3
		INT 3
		INT 3
		INT 3
_RO_DATA_Size: ;DATA_Size	;.data/DATA/
		INT 3
		INT 3
		INT 3
		INT 3
_RO_BSS_Size: ;BSS_Size	;BSS 
		INT 3
		INT 3
		INT 3
		INT 3
_RO_RDATA_Size: ;RDATA_Size;.rdata 
		INT 3
		INT 3
		INT 3
		INT 3
_RO_IDATA_Size: ;IDATA_Size;.idata 
		INT 3
		INT 3
		INT 3
		INT 3
_RO_EDATA_Size: ;EDATA_Size;.edata 
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_TLS_Size: ;TLS_Size;.tls
		INT 3
		INT 3
		INT 3
		INT 3
_RO_RSRC_Size: ;RSRC_Size	;.rsrc
		INT 3
		INT 3
		INT 3
		INT 3
_RO_RelocRVA: ;RelocRVA
		INT 3
		INT 3
		INT 3
		INT 3
_RO_RelocSize: ;RelocRVA
		INT 3
		INT 3
		INT 3
		INT 3
_patch3_LABEL_RO_EXPLORER_EXE_END_	LABEL	DWORD
_RO_EXPLORER_EXE:;DB "EXPLORER.EXE"0,13
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szSoftICE95:;DB  "\\\\.\\SICE",0,9
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szSoftICENT:;DB  "\\\\.\\NTICE",0,10
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_patch3_PackEncrypt_END_	LABEL	DWORD
LOADER_CRYPT_END:
; This variables won't be crypted:
;TlsBackupLabel:;IMAGE_TLS_DIRECTORY32 
;_RO_TlsBackup_StartAddressOfRawData:
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_TlsBackup_EndAddressOfRawData:
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_TlsBackup_AddressOfIndex:             ; PDWORD
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_TlsBackup_AddressOfCallBacks:         ; PIMAGE_TLS_CALLBACK *
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_TlsBackup_SizeOfZeroFill:
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_TlsBackup_Characteristics:
		INT 3
		INT 3
		INT 3
		INT 3
;ChecksumLabel:
;_RO_RlocBackup:
;_RO_RlocBackup_VirtualAddress
		INT 3
		INT 3
		INT 3
		INT 3
;_RO_RlocBackup_SizeOfBlock:
		INT 3
		INT 3
		INT 3
		INT 3
_patch3_RO_dwOrgChecksumSize LABEL DWORD
_RO_dwOrgChecksumSize:
		INT 3
		INT 3
		INT 3
		INT 3
_patch3_RO_dwOrgChecksum LABEL DWORD
_RO_dwOrgChecksum:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_Temp1: ;Temp1
		INT 3
		INT 3
		INT 3
		INT 3
_RO_Temp2: ;Temp2
		INT 3
		INT 3
		INT 3
		INT 3
_RO_BuffSize:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_Buff: ;buffer for some stuff, its size: 10000h(VS) - DEPACKER_CODE_SIZE
		INT 3
		INT 3
		INT 3
		INT 3
DepackerCodeEND:
	RETN
	;"ETGXZKATZ"
	INC EBP	;'E'
	PUSH ESP;'T'
	INC EDI	;'G'
	POP EAX	;'X'
	POP EDX	;'Z'
	DEC EBX	;'K'
	INC ECX	;'A'
	PUSH ESP;'T'
	POP EDX	;'Z'

	db 0E9h
	_patch3_offset_entry_jump	dd	0
	ret

start:
	jmp DepackerCode
	ret
_patch3_ShellCodeEnd_	LABEL	DWORD
    end; start