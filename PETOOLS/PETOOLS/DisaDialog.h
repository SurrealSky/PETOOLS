#pragma once
#include"Ini.h"
#include "afxwin.h"
#include "MyListCtrl.h"
#include "resource.h"


// CDisaDialog �Ի���

class CDisaDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDisaDialog)

public:
	CDisaDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDisaDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	void SetDlgUI();
	BOOL InitDisaDate();
public:
	Ini m_Ini;
	// ����ര��
	MyListCtrl m_List1;
};
