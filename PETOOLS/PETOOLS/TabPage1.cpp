// TabPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "TabPage1.h"
#include "afxdialogex.h"
#include "PETOOLSDlg.h"
#include "EncryptDlg.h"
#include "ProBarThread.h"
#include"resource.h"


// CTabPage 对话框

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


// CTabPage 消息处理程序


void CTabPage1::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(m_bStaticIsInitialized)
	{
		//ReSize(&mNameEdit,cx,cy);
		//ReSize(&mOffsetEdit,cx,cy);
	}
	GetClientRect(&m_rectOriginalWindow);//将变化后的对话框大小设为旧大小
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

	// TODO:  在此添加额外的初始化
	m_bStaticIsInitialized=false;//暂时关闭
	
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
	InitDisaDate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTabPage1::OnBnClickedButton1()
{
	/*
	// TODO: 在此添加控件通知处理程序代码
	CPETOOLSDlg *pMainDlg=dynamic_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CEncryptDlg *pHnd=dynamic_cast<CEncryptDlg*>(GetParent());

	CString strName;
	mEdit1.GetWindowTextA(strName);
	if(strName.GetLength()==0)
	{
		AfxMessageBox("区段名为空!");
		return;
	}

	CString strOffset;
	mEdit2.GetWindowTextA(strOffset);
	if(strOffset.GetLength()==0)
	{
		AfxMessageBox("修正偏移为空!");
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
	//先清除数据

//	mList.DeleteAllItems();
//
//	CProBarThread pProBarThread;
//	pProBarThread.Create();
//	pProBarThread.SetProValue(50);
//
//	ULONGLONG offset=0;//用于反汇编地址偏移
//	unsigned int mode =0;
//	//判断机器位数
//#ifdef PE_MODEL
//	mode=32;
//#else
//	mode=64;
//#endif
//
//	//由于分配粒度限制，将整个文件映射
//
//	char szCode[256] = {0};			// 存放汇编指令信息
//	CString strBuffer;				//存放十六进制数据和其他缓冲数据
//	unsigned int nIndex = 0;		// 每条机器指令长度，用于地址偏移
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
//		//显示地址编码
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
//		//显示十六进制数编码
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
//		// 显示汇编指令
//		SecureZeroMemory(szCode,sizeof(szCode));
//		d.DecodeAsmUdis86(szCode,sizeof(szCode),&nindex);
//		strBuffer=szCode;
//		this->mList.SetItemText(i,2,strBuffer);
//	}
//	pProBarThread.SetProValue(100);
	return TRUE;
}
