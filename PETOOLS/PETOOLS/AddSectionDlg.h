#pragma once
#include "afxwin.h"


// CAddSectionDlg 对话框

class CAddSectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddSectionDlg)

public:
	CAddSectionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddSectionDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit mNameEdit;
	CEdit mDataLength;
	CEdit mDataOffset;
	CEdit mVirtualOffset;
	CEdit mVirtualSize;
	CEdit mSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit4();
};
