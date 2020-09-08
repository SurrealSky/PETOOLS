#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include"MyListCtrl.h"
#include<pack\ByteBuffer.h>
#include<list>

typedef struct _ShellCode
{
	CString strBinFile;
	ByteBuffer bin;
}ShellCode;


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
	afx_msg void OnBnClickedOk();
public:
	CEdit mNameEdit;
	CComboBox mBinFile;
	MyListCtrl mList;
	std::list<ShellCode> shellcodes;
	BOOL InitDisaDate(STu8*,STu32);
	CString GetApplicationPath();
	void LoadShellCodes(std::list<ShellCode>&);
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk2();
};
