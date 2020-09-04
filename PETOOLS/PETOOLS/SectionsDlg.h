#pragma once
#include "MyListCtrl.h"


// SectionsDlg 对话框

class SectionsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SectionsDlg)

public:
	SectionsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SectionsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	MyListCtrl m_List1;
	virtual BOOL OnInitDialog();
};
