// PosCalcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "PosCalcDlg.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"


// CPosCalcDlg �Ի���

IMPLEMENT_DYNAMIC(CPosCalcDlg, CDialogEx)

CPosCalcDlg::CPosCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG8, pParent)
	, mVAEdt(_T(""))
	, mRVAEdt(_T(""))
	, mFOAEdt(_T(""))
{

}

CPosCalcDlg::~CPosCalcDlg()
{
}

void CPosCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, mVAEdt);
	DDX_Text(pDX, IDC_EDIT4, mRVAEdt);
	DDX_Text(pDX, IDC_EDIT5, mFOAEdt);
}


BEGIN_MESSAGE_MAP(CPosCalcDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPosCalcDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPosCalcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPosCalcDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPosCalcDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CPosCalcDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CPosCalcDlg ��Ϣ�������


BOOL CPosCalcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//���VA
void CPosCalcDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	//mRVAEdt = "";
	//mFOAEdt = "";
	UpdateData(FALSE);
}

//���RVA
void CPosCalcDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	//mVAEdt = "";
	//mFOAEdt = "";
	UpdateData(FALSE);
}

//���FOA
void CPosCalcDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	//mVAEdt = "";
	//mRVAEdt = "";
	UpdateData(FALSE);
}

//ת��
void CPosCalcDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	LONGLONG oldvalue=0;
	if (GetDlgItem(IDC_EDIT3)->IsWindowEnabled())
	{
		if (mVAEdt.GetLength() == 0) return;
		CString temp = "0x" + mVAEdt;
		::StrToInt64Ex(temp, STIF_SUPPORT_HEX, &oldvalue);
		mVAEdt.Format("%08X", oldvalue);
		CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
		LONGLONG newvalue = oldvalue - pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.ImageBase;//RVA
		mRVAEdt.Format("%08X", newvalue);
		newvalue = pMainDlg->mPEMake.RvaToFoa(newvalue);//FOA
		mFOAEdt.Format("%08X", newvalue);
	}
	else if (GetDlgItem(IDC_EDIT4)->IsWindowEnabled())
	{
		if (mRVAEdt.GetLength() == 0) return;

		CString temp = "0x" + mRVAEdt;
		::StrToInt64Ex(temp, STIF_SUPPORT_HEX, &oldvalue);
		CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
		LONGLONG newvalue=pMainDlg->mPEMake.RvaToFoa(oldvalue);//FOA
		mVAEdt.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.ImageBase+ oldvalue);
		mRVAEdt.Format("%08X", oldvalue);
		mFOAEdt.Format("%08X", newvalue);
	}
	else if (GetDlgItem(IDC_EDIT5)->IsWindowEnabled())
	{
		if (mFOAEdt.GetLength() == 0) return;
		CString temp = "0x" + mFOAEdt;
		::StrToInt64Ex(temp, STIF_SUPPORT_HEX, &oldvalue);
		CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
		LONGLONG newvalue = pMainDlg->mPEMake.FoaToRva(oldvalue);//RVA
		mVAEdt.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.ImageBase + newvalue);
		mRVAEdt.Format("%08X", newvalue);
		mFOAEdt.Format("%08X", oldvalue);
	}
	UpdateData(FALSE);
}


void CPosCalcDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	if(mFOAEdt.GetLength() == 0)
		Create16EditWindow((unsigned char *)(pMainDlg->mPEMake.mPeCtx.pVirMem), pMainDlg->mPEMake.mPeCtx.size, 0, 0);
	else
	{
		unsigned int foa = StrToInt(mFOAEdt);
		Create16EditWindow((unsigned char *)(pMainDlg->mPEMake.mPeCtx.pVirMem), pMainDlg->mPEMake.mPeCtx.size, foa, 0);
	}
}
