#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include"MyListCtrl.h"


// CAddPatch 对话框

class CAddPatch : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPatch)

public:
	CAddPatch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddPatch();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mNameEdit;
	CEdit mOffsetEdit;
	afx_msg void OnBnClickedOk();
	int m_Radio;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
public:
	BOOL InitDisaDate();
	MyListCtrl mList;
private:
	unsigned char *pPatch;
	unsigned int  dwSize;
};
