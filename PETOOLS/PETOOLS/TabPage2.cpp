// TabPage2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "TabPage2.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"
#include"EncryptDlg.h"


// CTabPage2 �Ի���

IMPLEMENT_DYNAMIC(CTabPage2, CDialogEx)

CTabPage2::CTabPage2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabPage2::IDD, pParent)
{

}

CTabPage2::~CTabPage2()
{
}

void CTabPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEdit1);
	DDX_Control(pDX, IDC_LIST1, mList);
	DDX_Control(pDX, IDC_EDIT2, mEdit2);
}


BEGIN_MESSAGE_MAP(CTabPage2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTabPage2::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTabPage2 ��Ϣ�������


BOOL CTabPage2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	TCHAR  column[][MAX_HEADLENGTH]={"��ַ","HEX ����","�����"};
	this->mList.SetHeaders(column,sizeof(column)/sizeof(*column));
	//�ı���뷽ʽ
	LVCOLUMN co={0};
	co.mask=LVCF_FMT; 
	this->mList.GetColumn(0,&co);
	co.fmt|=LVS_ALIGNLEFT;
	this->mList.SetColumn(1,&co);
	this->mList.SetColumn(2,&co);
	this->mList.SetColumnWidth(0,65);

	//����Ĭ�ϵ�ַӰ��
	CPETOOLSDlg *pMainDlg=dynamic_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	std::string strMap=pMainDlg->mPEMake.mPeCtx.path;
	strMap.erase(strMap.find_last_of('.'));
	strMap.append(".map");
	this->mEdit2.SetWindowTextA(strMap.c_str());
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTabPage2::OnBnClickedButton1()
{
	/*
	// TODO: �ڴ���ӿؼ�֪ͨ����������

		// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPETOOLSDlg *pMainDlg=dynamic_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CEncryptDlg *pHnd=dynamic_cast<CEncryptDlg*>(GetParent());

	CString strName;
	mEdit1.GetWindowTextA(strName);
	if(strName.GetLength()==0)
	{
		AfxMessageBox("������Ϊ��!");
		return;
	}

	CString strMap;
	mEdit2.GetWindowTextA(strMap);
	if(strMap.GetLength()==0)
	{
		AfxMessageBox("Ӱ��mapΪ��!");
		return;
	}
	//�ڴ˴�����Ӱ��map
	pMainDlg->mPeProtect.LoadMap(strMap.GetBuffer(0));
	MapStructrue* stu = pMainDlg->mPeProtect.GetMap("_start");
	if( !stu )
	{
		AfxMessageBox("map����ʧ��");
		return;
	}

	bool bRet=false;
	bRet=pMainDlg->mPeProtect.EncryptThree(strName,stu);
	if(bRet)
		pHnd->EndDialog(IDOK);
	else
		pHnd->EndDialog(IDCANCEL);
		*/
}
