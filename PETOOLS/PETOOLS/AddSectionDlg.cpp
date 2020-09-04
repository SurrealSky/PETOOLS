// AddSectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "AddSectionDlg.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"


// CAddSectionDlg �Ի���

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


// CAddSectionDlg ��Ϣ�������

void CAddSectionDlg::OnBnClickedButton1()
{
	//// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mNameEdit.SetLimitText(8);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
