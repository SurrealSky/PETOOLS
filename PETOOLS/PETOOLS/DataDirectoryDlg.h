#pragma once
#include"DialogFirst.h"

// DataDirectoryDlg �Ի���

class DataDirectoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DataDirectoryDlg)

public:
	DataDirectoryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DataDirectoryDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedMfcbutton(UINT  uId);
private:
	DialogFirst *pFrameDlg;
};
