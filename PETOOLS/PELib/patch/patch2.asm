;------------------------
; �ó�����ʾ��һ����¼���ڵĲ�������
; ���ض�λ��Ϣ�������ݶΣ��޵����
; ����
; 2010.6.28
;------------------------
    .386
    .model flat,stdcall
    option casemap:none

include    c:\masm32\include\windows.inc
include    c:\masm32\include\user32.inc
;includelib user32.lib
include    c:\masm32\include\kernel32.inc
;includelib kernel32.lib

ID_BUTTON1         equ   1
ID_BUTTON2         equ   2
ID_LABEL1          equ   3
ID_LABEL2          equ   4
ID_EDIT1           equ   5
ID_EDIT2           equ   6

_QLGetProcAddress typedef proto :dword,:dword      ;��������
_QLLoadLibraryA   typedef proto :dword
_QLCreateWindowExA typedef proto  :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
_QLDefWindowProcA typedef proto   :DWORD,:DWORD,:DWORD,:DWORD
_QLDestroyWindow typedef proto   :DWORD
_QLDispatchMessageA typedef proto   :DWORD
_QLGetDlgItemTextA typedef proto   :DWORD,:DWORD,:DWORD,:DWORD
_QLGetMessageA typedef proto   :DWORD,:DWORD,:DWORD,:DWORD
_QLMessageBoxA    typedef proto   :dword,:dword,:dword,:dword
_QLPostQuitMessage typedef proto   :DWORD
_QLRegisterClassExA typedef proto   :DWORD
_QLShowWindow typedef proto   :DWORD,:DWORD
_QLTranslateAcceleratorA typedef proto   :DWORD,:DWORD,:DWORD
_QLTranslateMessage typedef proto   :DWORD
_QLUpdateWindow typedef proto   :DWORD

_QLExitProcess typedef proto   :DWORD
_QLGetModuleHandleA typedef proto   :DWORD
_QLRtlZeroMemory typedef proto   :DWORD,:DWORD
_QLlstrcmpA typedef proto   :DWORD,:DWORD


;user32.dll
_ApiGetProcAddress  typedef ptr _QLGetProcAddress  ;������������
_ApiLoadLibraryA       typedef ptr _QLLoadLibraryA
_ApiCreateWindowExA   typedef ptr _QLCreateWindowExA
_ApiDefWindowProcA   typedef ptr _QLDefWindowProcA
_ApiDestroyWindow   typedef ptr _QLDestroyWindow
_ApiDispatchMessageA   typedef ptr _QLDispatchMessageA
_ApiGetDlgItemTextA   typedef ptr _QLGetDlgItemTextA
_ApiGetMessageA   typedef ptr _QLGetMessageA
_ApiMessageBoxA   typedef ptr _QLMessageBoxA
_ApiPostQuitMessage   typedef ptr _QLPostQuitMessage
_ApiRegisterClassExA   typedef ptr _QLRegisterClassExA
_ApiShowWindow   typedef ptr _QLShowWindow
_ApiTranslateAcceleratorA   typedef ptr _QLTranslateAcceleratorA
_ApiTranslateMessage   typedef ptr _QLTranslateMessage
_ApiUpdateWindow   typedef ptr _QLUpdateWindow
;kernel32.dll
_ApiExitProcess        typedef ptr _QLExitProcess
_ApiGetModuleHandleA   typedef ptr _QLGetModuleHandleA
_ApiRtlZeroMemory   typedef ptr _QLRtlZeroMemory
_ApilstrcmpA   typedef ptr _QLlstrcmpA



;�����
    .code
jmp start

szCaption          db  '��ӭ����',0
szText             db  '���ǺϷ��û�����ʹ�ø������',0
szCaptionMain      db  'ϵͳ��¼',0
szClassName        db  'Menu Example',0
szButtonClass      db  'button',0
szEditClass        db  'edit',0
szLabelClass       db  'static',0

szButtonText1      db  '��  ¼',0
szButtonText2      db  'ȡ  ��',0
szLabel1           db  '�û�����',0
szLabel2           db  '��   �룺',0
lpszUser           db  'admin',0       ;ģ���û���������
lpszPass           db  '123456',0

szBuffer           db  256 dup(0)
szBuffer2          db  256 dup(0)

hInstance          dd  ?
hWinMain           dd  ?
hWinEdit           dd  ?

hUser32Base        dd  ?
hKernel32Base      dd  ?

szGetProcAddress   db 'GetProcAddress',0
szLoadLibraryA     db 'LoadLibraryA',0
szCreateWindowExA  db 'CreateWindowExA',0
szDefWindowProcA   db 'DefWindowProcA',0
szDestroyWindow    db 'DestroyWindow',0
szDispatchMessageA db 'DispatchMessageA',0
szGetDlgItemTextA  db 'GetDlgItemTextA',0
szGetMessageA      db 'GetMessageA',0
szMessageBoxA      db 'MessageBoxA',0
szPostQuitMessage  db 'PostQuitMessage',0
szRegisterClassExA db 'RegisterClassExA',0
szShowWindow       db 'ShowWindow',0
szTranslateAcceleratorA  db 'TranslateAcceleratorA',0
szTranslateMessage db 'TranslateMessage',0
szUpdateWindow     db 'UpdateWindow',0
szUser32           db 'user32.dll',0,0
szExitProcess      db 'ExitProcess',0
szGetModuleHandleA db 'GetModuleHandleA',0
szRtlZeroMemory    db 'RtlZeroMemory',0
szlstrcmpA         db 'lstrcmpA',0
szKernel32         db 'kernel32.dll',0,0

_GetProcAddress  _ApiGetProcAddress ? ;������������
_LoadLibraryA       _ApiLoadLibraryA ?
_CreateWindowExA   _ApiCreateWindowExA  ?
_DefWindowProcA   _ApiDefWindowProcA  ?
_DestroyWindow   _ApiDestroyWindow  ?
_DispatchMessageA   _ApiDispatchMessageA  ?
_GetDlgItemTextA   _ApiGetDlgItemTextA  ?
_GetMessageA   _ApiGetMessageA  ?
_MessageBoxA   _ApiMessageBoxA  ?
_PostQuitMessage   _ApiPostQuitMessage  ?
_RegisterClassExA   _ApiRegisterClassExA  ?
_ShowWindow   _ApiShowWindow  ?
_TranslateAcceleratorA   _ApiTranslateAcceleratorA  ?
_TranslateMessage   _ApiTranslateMessage  ?
_UpdateWindow   _ApiUpdateWindow  ?
;kernel32.dll
_ExitProcess        _ApiExitProcess  ?
_GetModuleHandleA   _ApiGetModuleHandleA  ?
_RtlZeroMemory   _ApiRtlZeroMemory  ?
_lstrcmpA   _ApilstrcmpA  ?



;------------------------------------
; ����kernel32.dll�е�һ����ַ��ȡ���Ļ���ַ
;------------------------------------
_getKernelBase  proc _dwKernelRetAddress
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
_getApi proc _hModule,_lpApi
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
;----------------
; �˳�����
;----------------
_Quit  proc
       pushad
       call @F   ; ��ȥ�ض�λ
@@:
       pop ebx
       sub ebx,offset @B   ;��λ����ַebx  

       push [ebx+offset hWinMain]
       mov edx,[ebx+offset _DestroyWindow]
       call edx    

       push NULL
       mov edx,[ebx+offset _PostQuitMessage]
       call edx    
       
       popad
       ret
_Quit  endp

_Exit proc
       call @F   ; ��ȥ�ض�λ
@@:
       pop ebx
       sub ebx,offset @B   ;��λ����ַebx  

       push NULL
       mov edx,[ebx+offset _ExitProcess]
       call edx
_Exit endp
;------------------
; ������Ϣ�����ӳ���
;------------------
_ProcWinMain proc uses ebx edi esi,hWnd,uMsg,wParam,lParam
      local @stPos:POINT
      local hLabel1:dword
      local hLabel2:dword
      local hEdit1:dword
      local hEdit2:dword
      local hButton1:dword
      local hButton2:dword

      call @F   ; ��ȥ�ض�λ
   @@:
      pop ebx
      sub ebx,offset @B   ;��λ����ַebx

      mov eax,uMsg
      
      .if eax==WM_CREATE
          mov eax,hWnd
          mov [ebx+offset hWinMain],eax

          ;��ǩ
          mov eax,offset szLabelClass
          add eax,ebx
          mov ecx,offset szLabel1
          add ecx,ebx
      
          mov edx,[ebx+offset hInstance]

          push ebx

          push NULL
          push edx
          push ID_LABEL1
          push hWnd
          push 30
          push 100
          push 20
          push 10
          push WS_CHILD or WS_VISIBLE
          push ecx
          push eax
          push NULL
          mov edx,[ebx+offset _CreateWindowExA]
          call edx


          mov hLabel1,eax
          pop ebx

          mov eax,offset szLabelClass
          add eax,ebx
          mov ecx,offset szLabel2
          add ecx,ebx
      
          mov edx,[ebx+offset hInstance]

          push ebx


          push NULL
          push edx
          push ID_LABEL2
          push hWnd
          push 30
          push 100
          push 50
          push 10
          push WS_CHILD or WS_VISIBLE
          push ecx
          push eax
          push NULL
          mov edx,[ebx+offset _CreateWindowExA]
          call edx


          mov hLabel2,eax
          pop ebx

          ;�ı���
          mov eax,offset szEditClass
          add eax,ebx
     
          mov edx,[ebx+offset hInstance]

          push ebx


          push NULL
          push edx
          push ID_EDIT1
          push hWnd
          push 22
          push 175
          push 19
          push 105
          push WS_CHILD or WS_VISIBLE \
                 or WS_BORDER
          push NULL
          push eax
          push WS_EX_TOPMOST
          mov edx,[ebx+offset _CreateWindowExA]
          call edx


          mov hEdit1,eax
          pop ebx

          mov eax,offset szEditClass
          add eax,ebx
     
          mov edx,[ebx+offset hInstance]
          push ebx

          push NULL
          push edx
          push ID_EDIT2
          push hWnd
          push 22
          push 175
          push 49
          push 105
          push WS_CHILD or WS_VISIBLE \
                 or WS_BORDER or ES_PASSWORD
          push NULL
          push eax
          push WS_EX_TOPMOST
          mov edx,[ebx+offset _CreateWindowExA]
          call edx

          mov hEdit2,eax
          pop ebx

          ;��ť
          mov eax,offset szButtonClass
          add eax,ebx
          mov ecx,offset szButtonText1
          add ecx,ebx
     
          mov edx,[ebx+offset hInstance]
          push ebx

          push NULL
          push edx
          push ID_BUTTON1
          push hWnd
          push 30
          push 60
          push 100
          push 120
          push WS_CHILD or WS_VISIBLE
          push ecx
          push eax
          push NULL
          mov edx,[ebx+offset _CreateWindowExA]
          call edx


          mov hButton1,eax
          pop ebx

          mov eax,offset szButtonClass
          add eax,ebx
          mov ecx,offset szButtonText2
          add ecx,ebx
     
          mov edx,[ebx+offset hInstance]
          push ebx 

          push NULL
          push edx
          push ID_BUTTON2
          push hWnd
          push 30
          push 60
          push 100
          push 200
          push WS_CHILD or WS_VISIBLE
          push ecx
          push eax
          push NULL
          mov edx,[ebx+offset _CreateWindowExA]
          call edx

          mov hButton2,eax
          pop ebx
      .elseif eax==WM_COMMAND  ;����˵������ټ���Ϣ
          mov eax,wParam
          movzx eax,ax
          .if eax==ID_BUTTON1

             mov eax,offset szBuffer
             add eax,ebx
             push ebx

             push sizeof szBuffer
             push eax
             push ID_EDIT1
             push hWnd
             mov edx,[ebx+offset _GetDlgItemTextA]
             call edx

             pop ebx

             mov eax,offset szBuffer2
             add eax,ebx
             push ebx

             push sizeof szBuffer2
             push eax
             push ID_EDIT2
             push hWnd
             mov edx,[ebx+offset _GetDlgItemTextA]
             call edx

             pop ebx
             mov eax,offset szBuffer
             add eax,ebx
             mov ecx,offset lpszUser
             add ecx,ebx
             push ebx

             push ecx
             push eax
             mov edx,[ebx+offset _lstrcmpA]
             call edx

             pop ebx
             .if eax
                jmp _ret
             .endif
             mov eax,offset szBuffer2
             add eax,ebx
             mov ecx,offset lpszPass
             add ecx,ebx
             push ebx

             push ecx
             push eax
             mov edx,[ebx+offset _lstrcmpA]
             call edx

             pop ebx
             .if eax
                jmp _ret
             .endif
             jmp _ret1
          .elseif eax==ID_BUTTON2
_ret:        call _Exit
_ret1:       call _Quit
          .endif
      .elseif eax==WM_CLOSE
      .else
          push lParam
          push wParam
          push uMsg
          push hWnd
          mov edx,[ebx+offset _DefWindowProcA]
          call edx
          ret
      .endif
      
      xor eax,eax
      ret
_ProcWinMain endp


;----------------------
; �����ڳ���
;----------------------
_WinMain  proc _base

       local @stWndClass:WNDCLASSEX
       local @stMsg:MSG
       local @hAccelerator

       mov ebx,_base
       push ebx

       push NULL
       mov edx,[ebx+offset _GetModuleHandleA]
       call edx


       pop ebx
       mov [ebx+offset hInstance],eax

       push ebx
       ;ע�ᴰ����


       push sizeof @stWndClass
       lea eax,@stWndClass
       push eax
       mov edx,[ebx+offset _RtlZeroMemory]
       call edx       


       mov @stWndClass.hIcon,NULL
       mov @stWndClass.hIconSm,NULL

       mov @stWndClass.hCursor,NULL

       pop ebx

       mov edx,offset _ProcWinMain
       add edx,ebx
       mov ecx,offset szClassName
       add ecx,ebx

       push [ebx+offset hInstance]
       pop @stWndClass.hInstance
       mov @stWndClass.cbSize,sizeof WNDCLASSEX
       mov @stWndClass.style,CS_HREDRAW or CS_VREDRAW
       mov @stWndClass.lpfnWndProc,edx
       mov @stWndClass.hbrBackground,COLOR_WINDOW
       mov @stWndClass.lpszClassName,ecx
       push ebx

       lea eax,@stWndClass
       push eax
       mov edx,[ebx+offset _RegisterClassExA]
       call edx

       pop ebx

       mov edx,offset szClassName
       add edx,ebx
       mov ecx,offset szCaptionMain
       add ecx,ebx

       mov eax,offset hInstance
       add eax,ebx
       push ebx


       ;��������ʾ����
       push NULL
       push [eax]
       push NULL
       push NULL
       mov eax,180
       push eax
       mov eax,300
       push eax
       mov eax,280
       push eax
       mov eax,350
       push eax
       push WS_OVERLAPPED or WS_CAPTION or \
              WS_MINIMIZEBOX
       push ecx
       push edx
       push WS_EX_CLIENTEDGE
       mov edx,[ebx+offset _CreateWindowExA]
       call edx


       pop ebx
       mov [ebx+offset hWinMain],eax
       
       mov edx,offset hWinMain
       add edx,ebx

       push ebx
       push edx

       push SW_SHOWNORMAL
       push [edx]
       mov ecx,[ebx+offset _ShowWindow]
       call ecx

       pop edx

       push [edx]
       mov ecx,[ebx+offset _UpdateWindow]
       call ecx

       pop ebx
   
       ;��Ϣѭ��
       .while TRUE
          push ebx

          push 0
          push 0
          push NULL
          lea eax,@stMsg
          push eax
          mov edx,[ebx+offset _GetMessageA]
          call edx

          pop ebx
          .break .if eax==0
          mov ecx,offset hWinMain
          add ecx,ebx

          push ebx
          
          lea eax,@stMsg
          push eax
          push @hAccelerator
          push [ecx]
          mov edx,[ebx+offset _TranslateAcceleratorA]
          call edx

          pop ebx
          .if eax==0
             lea eax,@stMsg
             push eax
             mov edx,[ebx+offset _TranslateMessage]
             call edx

             lea eax,@stMsg
             push eax
             mov edx,[ebx+offset _DispatchMessageA]
             call edx
          .endif
       .endw
       ret
_WinMain endp

;-----------------
; ��ȡ���ж�̬���ӿ�Ļ���ַ
;-----------------
_getDllBase proc
    pushad
    call @F   ; ��ȥ�ض�λ
@@:
    pop ebx
    sub ebx,offset @B

    nop

    ;ʹ��LoadLibrary��ȡuser32.dll�Ļ���ַ
    mov eax,offset szUser32
    add eax,ebx

    mov edx,[ebx+offset _LoadLibraryA]

    push eax
    call edx
    mov [ebx+offset hUser32Base],eax

    popad
    ret
_getDllBase endp

;-----------------
; ��ȡ���к�������ڵ�ַ
;-----------------
_getFuns proc
    pushad
    call @F   ; ��ȥ�ض�λ
@@:
    pop ebx
    sub ebx,offset @B

    ;CreateWindowExA
    mov eax,offset szCreateWindowExA
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _CreateWindowExA],eax

    ;DefWindowProcA
    mov eax,offset szDefWindowProcA
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _DefWindowProcA],eax

    ;DestroyWindow
    mov eax,offset szDestroyWindow
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _DestroyWindow],eax

    ;DispatchMessageA
    mov eax,offset szDispatchMessageA
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _DispatchMessageA],eax

    ;GetDlgItemTextA
    mov eax,offset szGetDlgItemTextA
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _GetDlgItemTextA],eax

    ;GetMessageA
    mov eax,offset szGetMessageA
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _GetMessageA],eax

    ;MessageBoxA
    mov eax,offset szMessageBoxA
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _MessageBoxA],eax

    ;PostQuitMessage
    mov eax,offset szPostQuitMessage
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _PostQuitMessage],eax

    ;RegisterClassExA
    mov eax,offset szRegisterClassExA
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _RegisterClassExA],eax

    ;ShowWindow
    mov eax,offset szShowWindow
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _ShowWindow],eax

    ;TranslateAcceleratorA
    mov eax,offset szTranslateAcceleratorA
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _TranslateAcceleratorA],eax

    ;TranslateMessage
    mov eax,offset szTranslateMessage
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _TranslateMessage],eax

    ;UpdateWindow
    mov eax,offset szUpdateWindow
    add eax,ebx
    push eax
    push [ebx+offset hUser32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _UpdateWindow],eax


    ;ExitProcess
    mov eax,offset szExitProcess
    add eax,ebx
    push eax
    push [ebx+offset hKernel32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _ExitProcess],eax

    ;GetModuleHandleA
    mov eax,offset szGetModuleHandleA
    add eax,ebx
    push eax
    push [ebx+offset hKernel32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _GetModuleHandleA],eax


    ;RtlZeroMemory
    mov eax,offset szRtlZeroMemory
    add eax,ebx
    push eax
    push [ebx+offset hKernel32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _RtlZeroMemory],eax


    ;lstrcmpA
    mov eax,offset szlstrcmpA
    add eax,ebx
    push eax
    push [ebx+offset hKernel32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _lstrcmpA],eax

    popad
    ret
_getFuns endp


start:
    ;ȡ��ǰ�����Ķ�ջջ��ֵ
    mov eax,dword ptr [esp]
    push eax
    call @F   ; ��ȥ�ض�λ
@@:
    pop ebx
    sub ebx,offset @B
    pop eax
    ;��ȡkernel32.dll�Ļ���ַ
    invoke _getKernelBase,eax
    mov [ebx+offset hKernel32Base],eax

    ;�ӻ���ַ��������GetProcAddress��������ַ
    mov eax,offset szGetProcAddress
    add eax,ebx
    mov ecx,[ebx+offset hKernel32Base]
    invoke _getApi,ecx,eax
    mov [ebx+offset _GetProcAddress],eax   ;Ϊ�������ø�ֵ GetProcAddress

    ;ʹ��GetProcAddress��������ַ������������������GetProcAddress���������LoadLibraryA����ַ
    mov eax,offset szLoadLibraryA
    add eax,ebx
    
    push eax
    push [ebx+offset hKernel32Base]
    mov edx,[ebx+offset _GetProcAddress]
    call edx
    mov [ebx+offset _LoadLibraryA],eax

    invoke _getDllBase      ;��ȡ�����õ���dll�Ļ���ַ��kernel32����
    invoke _getFuns         ;��ȡ�����õ��ĺ�������ڵ�ַ��GetProcAddress��LoadLibraryA����
    invoke _WinMain,ebx

    jmpToStart   db 0E9h,0F0h,0FFh,0FFh,0FFh
    ret
    end start
