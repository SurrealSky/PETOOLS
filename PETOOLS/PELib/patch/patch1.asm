;------------------------
; �޵���������ݶΡ����ض�λ��Ϣ����ȫ�ֱ�����HelloWorld
; ����
; 2010.6.27
;------------------------
    .386
    .model flat,stdcall
    option casemap:none

include    c:\masm32\include\windows.inc

PUBLIC				_patch1_ShellCodeBegin_
PUBLIC				_patch1_ShellCodeEnd_
PUBLIC				_patch1_offset_entry_jump


_QLGetProcAddress typedef proto :dword,:dword      ;��������
_ApiGetProcAddress  typedef ptr _QLGetProcAddress  ;������������

_QLLoadLib        typedef proto :dword
_ApiLoadLib       typedef ptr _QLLoadLib

_QLMessageBoxA    typedef proto :dword,:dword,:dword,:dword
_ApiMessageBoxA   typedef ptr _QLMessageBoxA


;�����
    .code
_patch1_ShellCodeBegin_	LABEL	DWORD

jmp start

szText         db  'HelloWorldPE',0
szGetProcAddr  db  'GetProcAddress',0
szLoadLib      db  'LoadLibraryA',0
szMessageBox   db  'MessageBoxA',0

user32_DLL     db  'user32.dll',0,0



;------------------------------------
; ����kernel32.dll�е�һ����ַ��ȡ���Ļ���ַ
;------------------------------------
_getKernelBase  proc private _dwKernelRetAddress
   local @dwRet

   pushad

   mov @dwRet,0
   
   mov edi,_dwKernelRetAddress
   and edi,0ffff0000h  ;����ָ������ҳ�ı߽磬��1000h����

   .repeat
     .if word ptr [edi]==IMAGE_DOS_SIGNATURE  ;�ҵ�kernel32.dll��dosͷ
        mov esi,edi
        add esi,[esi+003ch]
        .if word ptr [esi]==IMAGE_NT_SIGNATURE ;�ҵ�kernel32.dll��PEͷ��ʶ
          mov @dwRet,edi
          .break
        .endif
     .endif
     sub edi,010000h
     .break .if edi<070000000h
   .until FALSE
   popad
   mov eax,@dwRet
   ret
_getKernelBase  endp   

;-------------------------------
; ��ȡָ���ַ�����API�����ĵ��õ�ַ
; ��ڲ�����_hModuleΪ��̬���ӿ�Ļ�ַ��_lpApiΪAPI����������ַ
; ���ڲ�����eaxΪ�����������ַ�ռ��е���ʵ��ַ
;-------------------------------
_getApi proc private _hModule,_lpApi
   local @ret
   local @dwLen

   pushad
   mov @ret,0
   ;����API�ַ����ĳ��ȣ���������
   mov edi,_lpApi
   mov ecx,-1
   xor al,al
   cld
   repnz scasb
   mov ecx,edi
   sub ecx,_lpApi
   mov @dwLen,ecx

   ;��pe�ļ�ͷ������Ŀ¼��ȡ�������ַ
   mov esi,_hModule
   add esi,[esi+3ch]
   assume esi:ptr IMAGE_NT_HEADERS
   mov esi,[esi].OptionalHeader.DataDirectory.VirtualAddress
   add esi,_hModule
   assume esi:ptr IMAGE_EXPORT_DIRECTORY

   ;���ҷ������Ƶĵ���������
   mov ebx,[esi].AddressOfNames
   add ebx,_hModule
   xor edx,edx
   .repeat
     push esi
     mov edi,[ebx]
     add edi,_hModule
     mov esi,_lpApi
     mov ecx,@dwLen
     repz cmpsb
     .if ZERO?
       pop esi
       jmp @F
     .endif
     pop esi
     add ebx,4
     inc edx
   .until edx>=[esi].NumberOfNames
   jmp _ret
@@:
   ;ͨ��API����������ȡ��������ٻ�ȡ��ַ����
   sub ebx,[esi].AddressOfNames
   sub ebx,_hModule
   shr ebx,1
   add ebx,[esi].AddressOfNameOrdinals
   add ebx,_hModule
   movzx eax,word ptr [ebx]
   shl eax,2
   add eax,[esi].AddressOfFunctions
   add eax,_hModule
   
   ;�ӵ�ַ��õ����������ĵ�ַ
   mov eax,[eax]
   add eax,_hModule
   mov @ret,eax

_ret:
   assume esi:nothing
   popad
   mov eax,@ret
   ret
_getApi endp

_goThere  proc private
   local _getProcAddress:_ApiGetProcAddress   ;���庯��
   local _loadLibrary:_ApiLoadLib
   local _messageBox:_ApiMessageBoxA


   local hKernel32Base:dword
   local hUser32Base:dword
   local lpGetProcAddr:dword
   local lpLoadLib:dword

   pushad

    ;��ȡkernel32.dll�Ļ���ַ
    invoke _getKernelBase,eax

    mov hKernel32Base,eax

    ;�ӻ���ַ��������GetProcAddress��������ַ
    mov eax,offset szGetProcAddr
    add eax,ebx

    mov edi,hKernel32Base
    mov ecx,edi

    invoke _getApi,ecx,eax
    mov lpGetProcAddr,eax
    ;Ϊ�������ø�ֵ GetProcAddress
    mov _getProcAddress,eax   

    ;ʹ��GetProcAddress��������ַ��
    ;����������������GetProcAddress������
    ;���LoadLibraryA����ַ
    mov eax,offset szLoadLib
    add eax,ebx
    invoke _getProcAddress,hKernel32Base,eax
    mov _loadLibrary,eax

    ;ʹ��LoadLibrary��ȡuser32.dll�Ļ���ַ
    mov eax,offset user32_DLL
    add eax,ebx
    invoke _loadLibrary,eax

    mov hUser32Base,eax

    ;ʹ��GetProcAddress��������ַ��
    ;��ú���MessageBoxA����ַ
    mov eax,offset szMessageBox
    add eax,ebx
    invoke _getProcAddress,hUser32Base,eax
    mov _messageBox,eax

    ;���ú���MessageBoxA
    mov eax,offset szText
    add eax,ebx
    invoke _messageBox,NULL,eax,NULL,MB_OK

    popad
    ret
_goThere endp

start:
    ;ȡ��ǰ�����Ķ�ջջ��ֵ
    mov eax,dword ptr [esp]
    push eax
    call @F   ; ��ȥ�ض�λ
@@:
    pop ebx
    sub ebx,offset @B
    pop eax

    invoke _goThere

	db 0E9h
	_patch1_offset_entry_jump	dd	0
    ret

	_patch1_ShellCodeEnd_	LABEL	DWORD

    end