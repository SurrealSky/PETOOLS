#pragma once
#include "afxwin.h"


// CAddSectionDlg �Ի���

class CAddSectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddSectionDlg)

public:
	CAddSectionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddSectionDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit mNameEdit;
	CEdit mDataLength;
	virtual BOOL OnInitDialog();
};
