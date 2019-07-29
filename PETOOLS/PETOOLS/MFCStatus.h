#pragma once


// MFCStatus

class MFCStatus : public CStatusBarCtrl
{
	DECLARE_DYNAMIC(MFCStatus)

public:
	MFCStatus();
	virtual ~MFCStatus();
	CProgressCtrl m_progres;
public:
	void SetUI();
	void SetProcessBar(UINT pos){this->m_progres.SetPos(pos);};
protected:
	DECLARE_MESSAGE_MAP()
};


