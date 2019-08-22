#include"GlobeVar.h"

const char *UNUSE="N/A";

void Create16EditWindow(unsigned char *buffer,unsigned int size,unsigned int startoff,unsigned int endoff)
{
	HE_SETTINGS s;
	memset(&s, 0, sizeof(s));
	s.dwMask = HE_SET_MEMORYBLOCKINPUT | HE_SET_SETSELECTION;
	//s.szFilePath = "D://flash.exe";
	s.diMem.bReadOnly = TRUE;
	s.diMem.pDataBuff = buffer;
	s.diMem.dwSize = size;
	s.dwSelStartOff = startoff;
	s.dwSelEndOff = endoff;

	if (!HESpecifySettings(&s))
	{
		MessageBox(0,"16EditLoader", "File access error !", MB_ICONERROR);
		return;
	}
	//
	// enter window loop (with current thread)
	//
	HEEnterWindowLoop();
}
