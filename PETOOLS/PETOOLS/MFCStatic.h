#pragma once


// MFCStatic

class MFCStatic : public CStatic
{
	DECLARE_DYNAMIC(MFCStatic)

public:
	MFCStatic();
	virtual ~MFCStatic();
protected:
	DECLARE_MESSAGE_MAP()
public:
	TCHAR Title[MAX_PATH];
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	virtual void PreSubclassWindow();
};


