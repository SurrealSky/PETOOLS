#pragma once
#include "afxcmn.h"
#include "TabPage1.h"
#include "TabPage2.h"


// CEncryptDlg �Ի���

class CEncryptDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEncryptDlg)

public:
	CEncryptDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEncryptDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl mTabCtrl;
	CTabPage1 mpage1;
	CTabPage2 mpage2;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	afx_msg LRESULT OnMsgSave(WPARAM wParam, LPARAM lParam);
};
