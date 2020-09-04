// AddSectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "AddSectionDlg.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"


// CAddSectionDlg 对话框

IMPLEMENT_DYNAMIC(CAddSectionDlg, CDialogEx)

CAddSectionDlg::CAddSectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddSectionDlg::IDD, pParent)
{

}

CAddSectionDlg::~CAddSectionDlg()
{
}

void CAddSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mNameEdit);
	DDX_Control(pDX, IDC_EDIT2, mDataLength);
}


BEGIN_MESSAGE_MAP(CAddSectionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddSectionDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAddSectionDlg 消息处理程序

void CAddSectionDlg::OnBnClickedButton1()
{
	//// TODO: 在此添加控件通知处理程序代码
	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CString strName;
	mNameEdit.GetWindowTextA(strName);
	if(strName.GetLength()==0) strName=".null";
	CString strSize;
	mDataLength.GetWindowTextA(strSize);
	int size=StrToInt(strSize);
	if(size==0)
		size=0x200;
	bool bRet=pMainDlg->mPEMake.AddSectionToEnd((STu8*)strName.GetBuffer(0),size);
	if(bRet)
		CDialogEx::OnOK();
	else
		CDialogEx::OnCancel();
		
}


BOOL CAddSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mNameEdit.SetLimitText(8);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
