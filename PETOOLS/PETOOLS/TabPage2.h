#pragma once
#include "afxwin.h"
#include "mylistctrl.h"


// CTabPage2 �Ի���

class CTabPage2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTabPage2)

public:
	CTabPage2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabPage2();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit mEdit1;
	MyListCtrl mList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	CEdit mEdit2;
};
