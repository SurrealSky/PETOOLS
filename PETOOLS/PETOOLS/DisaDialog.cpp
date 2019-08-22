// DisaDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "DisaDialog.h"
#include "afxdialogex.h"
#include "ProBarThread.h"
#include"PETOOLSDlg.h"
#include"../Common/disasm/disasm.h"

// CDisaDialog 对话框

IMPLEMENT_DYNAMIC(CDisaDialog, CDialogEx)

CDisaDialog::CDisaDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDisaDialog::IDD, pParent)
{
}

CDisaDialog::~CDisaDialog()
{
}

void CDisaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDisaDialog, CDialogEx)
END_MESSAGE_MAP()


// CDisaDialog 消息处理程序


BOOL CDisaDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->SetDlgUI();
	this->InitDisaDate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDisaDialog::SetDlgUI()
{
	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(AfxGetMainWnd());

	int x=0,y=0,height=0,width=0;
	TCHAR TextDisplay[MAX_PATH]={0};
	height=m_Ini.GetIntKey("otherconfigure.ini","DisaWin","height");
	width=m_Ini.GetIntKey("otherconfigure.ini","DisaWin","width");
	x=(GetSystemMetrics(SM_CXSCREEN)-width)/2;
	y=(GetSystemMetrics(SM_CYSCREEN)-height)/2;
	this->MoveWindow(x,y,width,height,TRUE);
	this->m_Ini.GetStrKey("otherconfigure.ini","DisaWin","title",TextDisplay);
	this->SetWindowText(TextDisplay);
	pMainDlg->SetControlUI("otherconfigure.ini",&m_List1,"List1");

	//设置list
	TCHAR  column[][MAX_HEADLENGTH]={"地址","HEX 数据","反汇编","注释"};
	this->m_List1.SetHeaders(column,sizeof(column)/sizeof(*column));
	//改变对齐方式
	LVCOLUMN co={0};
	co.mask=LVCF_FMT; 
	this->m_List1.GetColumn(0,&co);
	co.fmt|=LVS_ALIGNLEFT;
	this->m_List1.SetColumn(1,&co);
	this->m_List1.SetColumn(2,&co);
	this->m_List1.SetColumnWidth(0,65);
}

BOOL CDisaDialog::InitDisaDate()
{	
	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	DWORD pStartAddr=0;
	DWORD size=0;
	ULONGLONG offset=0;//用于反汇编地址偏移
	unsigned int mode =0;

	//判断机器位数
#ifdef PE_MODEL
	pStartAddr=pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.BaseOfCode;
	size=pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfCode;
	offset=pStartAddr+pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.ImageBase;
	mode=32;
#else
	pStartAddr=pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.BaseOfCode;
	size=pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfCode;
	offset=pStartAddr+pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.ImageBase;
	mode=64;
#endif

	char *pCode = (char *)pMainDlg->mPEMake.mPeCtx.pVirMem+/*pMainDlg->mPEMake.RvaToFoa(pStartAddr)*/pStartAddr;
	pStartAddr+=pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.ImageBase;

	for(unsigned int len=0,i=0;len<size;i++)
	{
		CString strBuffer;
		strBuffer.Format("%08X",pStartAddr+len);
		this->m_List1.InsertItem(i,strBuffer);
		t_disasm da;
 		len+=Disasm(pCode+len,MAXCMDSIZE,pStartAddr+len,&da,DISASM_CODE);
		strBuffer.Empty();
		strBuffer.Append(da.dump);
		this->m_List1.SetItemText(i,1,strBuffer);
		strBuffer.Empty();
		strBuffer.Append(da.result);
		this->m_List1.SetItemText(i,2,strBuffer);
	}
	
	return TRUE;
}
