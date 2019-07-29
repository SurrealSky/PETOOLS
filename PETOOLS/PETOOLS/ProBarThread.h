#pragma once



// CProBarThread

class CProBarThread : public CWinThread
{
	DECLARE_DYNCREATE(CProBarThread)

public:
	CProBarThread();
	virtual ~CProBarThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void SetProValue(int);
	void Create();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void AFX_MSG_CALL OnSetValue(WPARAM wParam, LPARAM lParam);
};

//ÓÃÓÚÐý×ªËø
extern volatile BOOL gWait;


