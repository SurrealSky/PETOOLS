#pragma once


// CPosCalcDlg 对话框

class CPosCalcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPosCalcDlg)

public:
	CPosCalcDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPosCalcDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
	CString mVAEdt;
	CString mRVAEdt;
	CString mFOAEdt;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
