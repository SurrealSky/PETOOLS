#pragma once
#include "MyListCtrl.h"


// SectionsDlg �Ի���

class SectionsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SectionsDlg)

public:
	SectionsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SectionsDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	MyListCtrl m_List1;
	virtual BOOL OnInitDialog();
};
