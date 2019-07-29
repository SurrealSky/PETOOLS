#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include"MyListCtrl.h"


// CAddPatch �Ի���

class CAddPatch : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPatch)

public:
	CAddPatch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddPatch();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mNameEdit;
	CEdit mOffsetEdit;
	afx_msg void OnBnClickedOk();
	int m_Radio;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
public:
	BOOL InitDisaDate();
	MyListCtrl mList;
private:
	unsigned char *pPatch;
	unsigned int  dwSize;
};
