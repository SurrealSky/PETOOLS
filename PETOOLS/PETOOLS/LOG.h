#pragma once
class LOG
{
public:
	LOG(void);
	~LOG(void);
	TCHAR *GetPath(void){return this->PATH;};
	TCHAR *GetTemp(void){return this->TEMP;};
	BOOL LogControl(TCHAR *);
private:
	TCHAR PATH[MAX_PATH];
	TCHAR TEMP[MAX_PATH];
};

