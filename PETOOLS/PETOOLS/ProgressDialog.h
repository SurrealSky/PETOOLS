#pragma once
#include "afxcmn.h"


// CProgressDialog �Ի���

class CProgressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProgressDialog();

// �Ի�������
	enum { IDD = IDD_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �������ؼ�
	CProgressCtrl m_ProCtrl;
};
