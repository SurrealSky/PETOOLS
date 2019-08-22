#pragma once
#include "../Common/Ini.h"
#include "../Common/log4z.h"
#include "GlobeVar.h"
#include "MFCStatic.h"
#include "mfcedit.h"
#include "MFCStatus.h"
#include "afxcmn.h"
#include "MyListCtrl.h"
#include "resource.h"

// DialogFirst 对话框

typedef struct _UiVisible
{
	bool isExport;
	bool isImport;
	bool isReloc;
	bool isResource;
	bool isDelayImport;
}UiVisible,*PUiVisible;

class DialogFirst : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFirst)

public:
	DialogFirst(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogFirst();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	void Init(int Argu);
private:
	BOOL SetDlgUI();
	static unsigned __stdcall WorkThreadProc(void* lpParameter);
	BOOL SetExportCtrl();
	BOOL SetImportCtrl();
	BOOL SetReloc();
	BOOL SetResource();
	BOOL SetRelay();
	void Reset();
	static BOOL CALLBACK EnumChildProc(HWND hwnd,LPARAM lParam);
public:
	Ini m_Ini;
	int	dwArgu;
	UiVisible	mUiVisible;

	MFCStatic m_Static1;
	MFCStatic m_Static2;
	MFCStatic m_Static3;
	MFCStatic m_Static4;
	MFCStatic m_Static5;
	MFCStatic m_Static6;
	MFCStatic m_Static7;
	MFCStatic m_Static8;
	MFCStatic m_Static9;
	MFCStatic m_Static10;
	MFCStatic m_Static11;
	MFCStatic m_Static12;
	MFCEdit m_Edit1;
	MFCEdit m_Edit2;
	MFCEdit m_Edit3;
	MFCEdit m_Edit4;
	MFCEdit m_Edit5;
	MFCEdit m_Edit6;
	MFCEdit m_Edit7;
	MFCEdit m_Edit8;
	MFCEdit m_Edit9;
	MFCEdit m_Edit10;
	MFCEdit m_Edit11;
	MyListCtrl m_List1;
	MyListCtrl m_List2;
	MyListCtrl m_List3;
	MyListCtrl m_List4;
	MyListCtrl m_List6;
	MyListCtrl m_List5;
};
