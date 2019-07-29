
// PEMakeDlg.h : 头文件
//

#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"
#include"GlobeVar.h"


// CPEMakeDlg 对话框
class CPEMakeDlg : public CDialogEx
{
// 构造
public:
	CPEMakeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PEMAKE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMfcbutton1();
	CMFCEditBrowseCtrl tbFilePath;
	CEdit mDisplay;
	PEMake mPEMake;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
