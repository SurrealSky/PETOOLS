
// PEMakeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"
#include"GlobeVar.h"


// CPEMakeDlg �Ի���
class CPEMakeDlg : public CDialogEx
{
// ����
public:
	CPEMakeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PEMAKE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMfcbutton1();
	CMFCEditBrowseCtrl tbFilePath;
	CEdit mDisplay;
	PEMake mPEMake;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
