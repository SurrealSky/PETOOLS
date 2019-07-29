#pragma once


// MFCEdit

class MFCEdit : public CMFCEditBrowseCtrl
{
	DECLARE_DYNAMIC(MFCEdit)

public:
	MFCEdit();
	virtual ~MFCEdit();

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void PreSubclassWindow();
};


