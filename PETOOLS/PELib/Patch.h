//汇编patch相关定义


extern "C" DWORD _patch1_ShellCodeBegin_;
extern "C" DWORD _patch1_ShellCodeEnd_;
extern "C" DWORD _patch1_offset_entry_jump;

extern "C" DWORD _patch2_ShellCodeBegin_;
extern "C" DWORD _patch2_ShellCodeEnd_;
extern "C" DWORD _patch2_offset_entry_jump;

extern "C" DWORD _patch3_ShellCodeBegin_;

extern "C" DWORD _patch3_LABEL_OEP_JUMP_CODE_START_;
extern "C" DWORD _patch3_LABEL_OEP_JUMP_CODE_END_;
extern "C" DWORD _patch3_LABEL_OepJumpDecryptLoop;

extern "C" DWORD _patch3_LABEL_RO_SectionNames_START_;
extern "C" DWORD _patch3_LABEL_RO_EXPLORER_EXE_END_;
extern "C" DWORD _patch3_LABEL_DecryptSectionsInfoLoop;

extern "C" DWORD _patch3_LABEL_VARIABLE_CRYPT_START_;
extern "C" DWORD _patch3_LABEL_VARIABLE_CRYPT_END_;
extern "C" DWORD _patch3_LABEL_VariableDecryptLoop;

extern "C" DWORD _patch3_PackEncrypt_START_;
extern "C" DWORD _patch3_PackEncrypt_END_;
extern "C" DWORD _patch3_LABEL_PackDecryptLoop;

extern "C" DWORD _patch3_PRE_VARIABLE_START_;

extern "C" DWORD _patch3_SectionDecryptLoop;
extern "C" DWORD _patch3_CODEDecryptLoop;
extern "C" DWORD _patch3_DATADecryptLoop;
extern "C" DWORD _patch3_EDATADecryptLoop;
extern "C" DWORD _patch3_IDATADecryptLoop;
extern "C" DWORD _patch3_RSRCDecryptLoop;

extern "C" DWORD _patch3_RO_dwOrgChecksumSize;
extern "C" DWORD _patch3_RO_dwOrgChecksum;

extern "C" DWORD _patch3_ShellCodeEnd_;
extern "C" DWORD _patch3_offset_entry_jump;