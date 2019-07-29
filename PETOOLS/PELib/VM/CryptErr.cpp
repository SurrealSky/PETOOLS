
#include"../PELib.h"
#include "CryptErr.h"

const char	*szFileErr			="File access error :(";
const char	*szNoPEErr			="Invalid PE file!";
const char	*szNoMemErr			="Not enough memory :(";
const char	*szFsizeErr			="Files with a filesize of 0 aren't allowed!";
const char	*szNoRoom4SectionErr="There's no room for a new section :(";
const char	*szSecNumErr		="Too many sections!";
const char	*szIIDErr			="Too much ImageImportDescriptors!";
const char	*szFileISProtect	="File already was protected!";
const char	*szPEnotValid		="Invalid PE file! It might be protected by another tool.";
const char	*szPEisCOMRuntime	="This Version does not support COM Runtime structure.";
const char	*szDLLnotSupport	="This Version does not support dynamic link library.";
const char	*szWDMnotSupport	="This Version does not support windows driver model.";
const char	*szTServernotSupport="This Version does not support terminal server aware.";
const char	*szSYSnotSupport	="This Version does not support system file.";
const char	*szNOSEHnotSupport	="No SE handler resides in this PE.";
const char	*szNOBINDnotSupport	="Can not support PE file with no bind.";
const char	*szPackSectionName	="Section's Name is not recognized :(";

void ShowErr(unsigned char numErr);

//----------------------------------------------------------------
//----- ERROR MESSAGES ----
//The ShowErr display message by receiving its Error Number
void ShowErr(unsigned char numErr)
{
	char *szErr=new TCHAR[64];
	switch(numErr)
	{
	case MemErr:
		strcpy(szErr,szNoMemErr);
		break;

	case PEErr:
		strcpy(szErr,szNoPEErr);
		break;

	case FileErr:
		strcpy(szErr,szFileErr);
		break;

	case NoRoom4SectionErr:
		strcpy(szErr,szNoRoom4SectionErr);
		break;

	case FsizeErr:
		strcpy(szErr,szFsizeErr);
		break;

	case SecNumErr:
		strcpy(szErr,szSecNumErr);
		break;

	case IIDErr:
		strcpy(szErr,szIIDErr);
		break;

	case FileISProtect:
		strcpy(szErr,szFileISProtect);
		break;

	case PEnotValid:
		strcpy(szErr,szPEnotValid);
		break;
		
	case PEisCOMRuntime:
		strcpy(szErr,szPEisCOMRuntime);
		break;

	case DLLnotSupport:
		strcpy(szErr,szDLLnotSupport);
		break;

	case WDMnotSupport:
		strcpy(szErr,szWDMnotSupport);
		break;

	case TServernotSupport:
		strcpy(szErr,szTServernotSupport);
		break;

	case SYSnotSupport:
		strcpy(szErr,szSYSnotSupport);
		break;

	case NOSEHnotSupport:
		strcpy(szErr,szNOSEHnotSupport);
		break;

	case NOBINDnotSupport:
		strcpy(szErr,szNOBINDnotSupport);
		break;

	case PackSectionName:
		strcpy(szErr,szPackSectionName);
		break;
	}
	MessageBox(GetActiveWindow(),szErr,
			   "Error", 
			   MB_OK | MB_ICONERROR );
}	