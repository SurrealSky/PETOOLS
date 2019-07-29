#pragma once
#include"Ini.h"
#include "afxwin.h"
#include "MyListCtrl.h"
#include "resource.h"


// CDisaDialog 对话框

class CDisaDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDisaDialog)

public:
	CDisaDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDisaDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	void SetDlgUI();
	BOOL InitDisaDate();
public:
	Ini m_Ini;
	// 反汇编窗口
	MyListCtrl m_List1;
};
