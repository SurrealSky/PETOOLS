#pragma once
#include "afxcmn.h"


// CProgressDialog 对话框

class CProgressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgressDialog();

// 对话框数据
	enum { IDD = IDD_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 进度条控件
	CProgressCtrl m_ProCtrl;
};
