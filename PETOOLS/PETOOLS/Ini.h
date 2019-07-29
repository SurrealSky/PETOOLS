#pragma once
#include<Windows.h>

class Ini
{
public:
	Ini(void);
	~Ini(void);
public:
	int GetIntKey(IN TCHAR *File,IN TCHAR *section,IN TCHAR *key);
	void GetStrKey(IN TCHAR *File,IN TCHAR *section,IN TCHAR *key,OUT TCHAR *pOutBuffer);
	TCHAR *GetPath(void);
private:
	TCHAR PATH[MAX_PATH];
};

