#pragma once
#include"DialogFirst.h"

// DataDirectoryDlg 对话框

class DataDirectoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DataDirectoryDlg)

public:
	DataDirectoryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DataDirectoryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedMfcbutton(UINT  uId);
private:
	DialogFirst *pFrameDlg;
};
