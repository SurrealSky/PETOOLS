// TabPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "TabPage1.h"
#include "afxdialogex.h"
#include "PETOOLSDlg.h"
#include "EncryptDlg.h"
#include "ProBarThread.h"
#include"resource.h"


// CTabPage �Ի���

IMPLEMENT_DYNAMIC(CTabPage1, CDialogEx)

CTabPage1::CTabPage1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabPage1::IDD, pParent)
{
	m_bStaticIsInitialized=false;
}

CTabPage1::~CTabPage1()
{
}

void CTabPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEdit1);
	DDX_Control(pDX, IDC_EDIT2, mEdit2);
	DDX_Control(pDX, IDC_LIST1, mList);
}


BEGIN_MESSAGE_MAP(CTabPage1, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CTabPage1::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTabPage ��Ϣ�������


void CTabPage1::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(m_bStaticIsInitialized)
	{
		//ReSize(&mNameEdit,cx,cy);
		//ReSize(&mOffsetEdit,cx,cy);
	}
	GetClientRect(&m_rectOriginalWindow);//���仯��ĶԻ����С��Ϊ�ɴ�С
}

void CTabPage1::ReSize(CWnd *pWnd,int cx,int cy)
{
	if(pWnd->m_hWnd==NULL) return;
	CRect rect2;
	pWnd->GetWindowRect(&rect2);
	ScreenToClient(rect2);

	rect2.left=rect2.left * cx/m_rectOriginalWindow.Width();
    rect2.right=rect2.right* cx/m_rectOriginalWindow.Width();
    rect2.top=rect2.top * cy/m_rectOriginalWindow.Height();
    rect2.bottom=rect2.bottom * cy/m_rectOriginalWindow.Height();

	pWnd->MoveWindow(rect2);
}


BOOL CTabPage1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_bStaticIsInitialized=false;//��ʱ�ر�
	
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
	InitDisaDate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTabPage1::OnBnClickedButton1()
{
	/*
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

	CString strOffset;
	mEdit2.GetWindowTextA(strOffset);
	if(strOffset.GetLength()==0)
	{
		AfxMessageBox("����ƫ��Ϊ��!");
		return;
	}
	bool bRet=false;
	bRet=pMainDlg->mPeProtect.EncryptOne(strName.GetBuffer(0),
	(unsigned char *)encrypt_patch_execu1,sizeof(encrypt_patch_execu1),StrToInt(strOffset));
	if(bRet)
		pHnd->SendMessage(MSG_SAVE);
	else
		pHnd->EndDialog(IDCANCEL);
		*/

}

BOOL CTabPage1::InitDisaDate()
{	
	//���������

//	mList.DeleteAllItems();
//
//	CProBarThread pProBarThread;
//	pProBarThread.Create();
//	pProBarThread.SetProValue(50);
//
//	ULONGLONG offset=0;//���ڷ�����ַƫ��
//	unsigned int mode =0;
//	//�жϻ���λ��
//#ifdef PE_MODEL
//	mode=32;
//#else
//	mode=64;
//#endif
//
//	//���ڷ����������ƣ��������ļ�ӳ��
//
//	char szCode[256] = {0};			// ��Ż��ָ����Ϣ
//	CString strBuffer;				//���ʮ���������ݺ�������������
//	unsigned int nIndex = 0;		// ÿ������ָ��ȣ����ڵ�ַƫ��
//	unsigned char *pCode = (unsigned char *)encrypt_patch_execu1;
//	unsigned int dwSize=sizeof(encrypt_patch_execu1);
//
//	CDisassembler d;
//	d.Udis86Init(pCode,dwSize,mode);
//
//	for(int i=0;d.Udis86Loop()!=0;i++)
//	{
//		uint64_t off=offset;
//		off+=d.DecodeHexUdis86(szCode,sizeof(szCode));
//		//��ʾ��ַ����
//		switch(mode)
//		{
//		case 32:
//			{
//				strBuffer.Format("%d",off);
//			}break;
//		case 64:
//			{
//				strBuffer.Format("%d",off);
//			}break;
//		default:
//			{
//				strBuffer.Format("%d",off);
//			}break;
//		}
//		this->mList.InsertItem(i,strBuffer);
//		//��ʾʮ������������
//		size_t nindex=0;
//		d.DecodeAsmUdis86(szCode,sizeof(szCode),&nindex);
//		strBuffer.Empty();
//		for(int k=0;k<nindex;k++)
//		{
//			CString strTemp;
//			unsigned int ss=(unsigned char)*(pCode+off+k-offset);
//			strTemp.Format("%02X ",ss);
//			strBuffer.Append(strTemp);
//		}
//		this->mList.SetItemText(i,1,strBuffer);
//		// ��ʾ���ָ��
//		SecureZeroMemory(szCode,sizeof(szCode));
//		d.DecodeAsmUdis86(szCode,sizeof(szCode),&nindex);
//		strBuffer=szCode;
//		this->mList.SetItemText(i,2,strBuffer);
//	}
//	pProBarThread.SetProValue(100);
	return TRUE;
}
