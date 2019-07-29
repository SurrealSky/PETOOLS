#pragma once
#include "afxwin.h"
#include "mylistctrl.h"


// CTabPage �Ի���

class CTabPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTabPage1)

public:
	CTabPage1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabPage1();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	bool m_bStaticIsInitialized;
	CRect m_rectOriginalWindow;
public:
	virtual BOOL OnInitDialog();
public:
	void ReSize(CWnd*,int,int);
	afx_msg void OnBnClickedButton1();
	BOOL InitDisaDate();
	void SetTab(int);
public:
	int	mTab;
	CEdit mEdit1;
	CEdit mEdit2;
	MyListCtrl mList;
};
