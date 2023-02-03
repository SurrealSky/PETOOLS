
// PETOOLSDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <Ini.h>
#include "mfcstatic.h"
#include "afxeditbrowsectrl.h"
#include "afxbutton.h"
#include <locale.h>
#include "MFCEdit.h"
#include "afxfontcombobox.h"
#include "MFCStatus.h"
#include "afxwin.h"
#include <strsafe.h>
#include"GlobeVar.h"
#include"ProgressDialog.h"
#include"../PELib/PE/PEMake.h"
#include"PosCalcDlg.h"


// CPETOOLSDlg 对话框
class CPETOOLSDlg : public CDialogEx
{
// 构造
public:
	CPETOOLSDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CPETOOLSDlg();                     //析构函数

// 对话框数据
	enum { IDD = IDD_PETOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//相关变量
	Ini mIni;
	PEMake mPEMake;
	CMFCButton m_Button1;
	CMFCButton m_Button2;
	CMFCButton m_Button3;
	CMFCButton m_Button4;
	CMFCButton m_Button5;
	CMFCButton m_Button6;
	CMFCButton m_Button7;
	CMFCButton m_Button8;
	CMFCButton m_Button9;
	CMFCButton m_Button10;
	CMFCButton m_Button11;

	MFCStatus m_Status;

	MFCStatic m_Static1;
	MFCStatic m_Static2;
	MFCStatic m_Static3;
	MFCStatic m_Static4;
	MFCStatic m_Static5;
	MFCStatic m_Static6;
	MFCStatic m_Static7;
	MFCStatic m_Static9;
	MFCStatic m_Static10;
	MFCStatic m_Static11;
	MFCStatic m_Static12;
	MFCStatic m_Static13;
	MFCStatic m_Static14;
	MFCStatic m_Static15;
	MFCStatic m_Static16;
	MFCStatic m_Static17;
	MFCStatic m_Static18;
	MFCStatic m_Static19;
	MFCStatic m_Static20;
	MFCStatic m_Static21;
	MFCStatic m_Static22;
	MFCStatic m_Static23;
	MFCStatic m_Static24;
	MFCStatic m_Static25;
	MFCStatic m_Static26;
	MFCStatic m_Static27;
	MFCStatic m_Static28;
	MFCStatic m_Static29;
	MFCStatic m_Static30;
	MFCStatic m_Static31;
	MFCStatic m_Static32;
	MFCStatic m_Static33;
	MFCStatic m_Static34;
	MFCStatic m_Static35;
	MFCStatic m_Static36;
	MFCStatic m_Static37;
	MFCStatic m_Static38;
	MFCStatic m_Static39;
	MFCStatic m_Static40;
	MFCStatic m_Static41;
	MFCStatic m_Static42;
	MFCStatic m_Static43;
	MFCStatic m_Static44;
	MFCStatic m_Static45;
	MFCStatic m_Static46;

	MFCEdit m_Edit1;
	MFCEdit m_Edit2;
	MFCEdit m_Edit5;
	MFCEdit m_Edit6;
	MFCEdit m_Edit7;
	MFCEdit m_Edit8;
	MFCEdit m_Edit9;
	MFCEdit m_Edit10;
	MFCEdit m_Edit11;
	MFCEdit m_Edit12;
	MFCEdit m_Edit13;
	MFCEdit m_Edit14;
	MFCEdit m_Edit15;
	MFCEdit m_Edit16;
	MFCEdit m_Edit17;
	MFCEdit m_Edit18;
	MFCEdit m_Edit19;
	MFCEdit m_Edit20;
	MFCEdit m_Edit21;
	MFCEdit m_Edit22;
	MFCEdit m_Edit23;
	MFCEdit m_Edit24;
	MFCEdit m_Edit25;
	MFCEdit m_Edit26;
	MFCEdit m_Edit27;
	MFCEdit m_Edit28;
	MFCEdit m_Edit29;
	MFCEdit m_Edit30;
	MFCEdit m_Edit31;
	MFCEdit m_Edit32;
	MFCEdit m_Edit33;
	MFCEdit m_Edit34;
	MFCEdit m_Edit35;
	MFCEdit m_Edit36;
	MFCEdit m_Edit37;
	MFCEdit m_Edit38;
	MFCEdit m_Edit39;
	MFCEdit m_Edit40;
	MFCEdit m_Edit41;
	
	CPosCalcDlg *pPosCalcDlg;
public:
	//相关方法
	BOOL SetDlgUI(void);
	BOOL SetDumpFunc(void);
	void SetControlUI(TCHAR pFile[],CMFCButton *,TCHAR *);
	void SetControlUI(TCHAR pFile[],MFCStatic *,TCHAR *,BOOL isVisible=TRUE);
	void SetControlUI(TCHAR pFile[],MFCEdit *,TCHAR *,BOOL isEnable,BOOL isVisible=TRUE);
	void SetControlUI(TCHAR pFile[],CWnd *,TCHAR *,BOOL isVisible=TRUE);
	BOOL SetCtrlContent();
	void Reset();

	static BOOL CALLBACK EnumChildProc(HWND hwnd,LPARAM lParam);
public:
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnBnClickedMfcbutton2();
	afx_msg void OnBnClickedMfcbutton3();
	afx_msg void OnBnClickedMfcbutton4();
	afx_msg void OnBnClickedMfcbutton5();
	afx_msg void OnBnClickedMfcbutton6();
	afx_msg void OnBnClickedMfcbutton7();
	afx_msg void OnBnClickedMfcbutton8();
public:
	afx_msg void OnOpen();
	afx_msg void OnDisa();
	afx_msg void OnReset();
	afx_msg void OnTest();
protected:
	afx_msg LRESULT OnUpdateUi(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnSaveFile();
	afx_msg void OnSaveAs();
	afx_msg void OnHexEditView();
	afx_msg void OnBnClickedMfcbutton9();
	afx_msg void OnBnClickedMfcbutton10();
	afx_msg void OnBnClickedMfcbutton11();
};