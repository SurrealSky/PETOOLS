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


// CAddPatch 对话框

class CAddPatch : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPatch)

public:
	CAddPatch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddPatch();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
public:
	CEdit mNameEdit;
	CEdit mJmpCode;
	CEdit mNopBytes;
	CComboBox mBinFile;
	MyListCtrl mList;
	std::list<ShellCode> shellcodes;
	BOOL InitDisaDate(STu8*,STu32);
	CString GetApplicationPath();
	void LoadShellCodes(std::list<ShellCode>&);
	STu32 MemofOffset(const STu8 *data, const STu32 data_len, const STu8 *pbyte, const STu32 pbyte_len);
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedRadio1();
};
