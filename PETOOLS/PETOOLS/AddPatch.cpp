// AddPatch.cpp : 实现文件
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "AddPatch.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"
#include"ProBarThread.h"
#include"../Common/disasm/disasm.h"


// CAddPatch 对话框

IMPLEMENT_DYNAMIC(CAddPatch, CDialogEx)

CAddPatch::CAddPatch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddPatch::IDD, pParent)
	, m_Radio(0)
{
	pPatch=NULL;
	dwSize=0;
}

CAddPatch::~CAddPatch()
{
}

void CAddPatch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mNameEdit);
	DDX_Control(pDX, IDC_LIST1, mList);
	DDX_Control(pDX, IDC_EDIT2, mOffsetEdit);
}


BEGIN_MESSAGE_MAP(CAddPatch, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddPatch::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CAddPatch::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAddPatch::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CAddPatch::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CAddPatch 消息处理程序


BOOL CAddPatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mNameEdit.SetLimitText(8);
	//默认选中第一个
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(BST_CHECKED);
	m_Radio=0;
	//设置LIST控件
	//设置list
	TCHAR  column[][MAX_HEADLENGTH]={"地址","HEX 数据","反汇编"};
	this->mList.SetHeaders(column,sizeof(column)/sizeof(*column));
	//改变对齐方式
	LVCOLUMN co={0};
	co.mask=LVCF_FMT; 
	this->mList.GetColumn(0,&co);
	co.fmt|=LVS_ALIGNLEFT;
	this->mList.SetColumn(1,&co);
	this->mList.SetColumn(2,&co);
	this->mList.SetColumnWidth(0,65);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAddPatch::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CString strName;
	mNameEdit.GetWindowTextA(strName);
	if(strName.GetLength()==0)
	{
		AfxMessageBox("区段名为空!");
		return;
	}
	//两个位置需要修正，一个是程序OEP，一个是最后的跳转
	CString strOffset;
	mOffsetEdit.GetWindowTextA(strOffset);
	if(strOffset.GetLength()==0)
	{
		AfxMessageBox("修正偏移为空!");
		return;
	}
	bool bRet=pMainDlg->mPEMake.AddPatch(strName.GetBuffer(0),pPatch,dwSize,StrToInt(strOffset));
	if(bRet)
		CDialogEx::OnOK();
	else
		CDialogEx::OnCancel();
}


void CAddPatch::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio=0;
	const char patch_execu1[0x4] = { 0x8b,0xff,0x8b,0xff };
	pPatch=(unsigned char*)patch_execu1;
	dwSize=sizeof(patch_execu1);
	InitDisaDate();
}


void CAddPatch::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio=1;
	const char patch_execu2[0x4] = { 0x8b,0xff,0x8b,0xff };
	pPatch=(unsigned char*)patch_execu2;
	dwSize=sizeof(patch_execu2);
	InitDisaDate();
}


void CAddPatch::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio=2;
	const char patch_execu3[0x4] = { 0x8b,0xff,0x8b,0xff };
	pPatch=(unsigned char*)patch_execu3;
	dwSize=sizeof(patch_execu3);
	InitDisaDate();
}

BOOL CAddPatch::InitDisaDate()
{	
	//先清除数据

	mList.DeleteAllItems();

	CProBarThread pProBarThread;
	pProBarThread.Create();
	pProBarThread.SetProValue(50);

	ULONGLONG offset=0;//用于反汇编地址偏移
	unsigned int mode =0;
	//判断机器位数
#ifdef PE_MODEL
	mode=32;
#else
	mode=64;
#endif

	char *pCode = (char *)pPatch;
	unsigned int size = dwSize;
	unsigned int pStartAddr=0 ;

	for (unsigned int len = 0, i = 0; len<size; i++)
	{
		CString strBuffer;
		strBuffer.Format("%08X", pStartAddr + len);
		this->mList.InsertItem(i, strBuffer);
		t_disasm da;
		len += Disasm(pCode + len, MAXCMDSIZE, pStartAddr + len, &da, DISASM_CODE);
		strBuffer.Empty();
		strBuffer.Append(da.dump);
		this->mList.SetItemText(i, 1, strBuffer);
		strBuffer.Empty();
		strBuffer.Append(da.result);
		this->mList.SetItemText(i, 2, strBuffer);
	}
	pProBarThread.SetProValue(100);
	return TRUE;
}