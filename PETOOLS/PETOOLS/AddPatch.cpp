// AddPatch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "AddPatch.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"
#include"ProBarThread.h"
#include"../Common/disasm/disasm.h"


// CAddPatch �Ի���

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


// CAddPatch ��Ϣ�������


BOOL CAddPatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mNameEdit.SetLimitText(8);
	//Ĭ��ѡ�е�һ��
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(BST_CHECKED);
	m_Radio=0;
	//����LIST�ؼ�
	//����list
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAddPatch::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CString strName;
	mNameEdit.GetWindowTextA(strName);
	if(strName.GetLength()==0)
	{
		AfxMessageBox("������Ϊ��!");
		return;
	}
	//����λ����Ҫ������һ���ǳ���OEP��һ����������ת
	CString strOffset;
	mOffsetEdit.GetWindowTextA(strOffset);
	if(strOffset.GetLength()==0)
	{
		AfxMessageBox("����ƫ��Ϊ��!");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Radio=0;
	const char patch_execu1[0x4] = { 0x8b,0xff,0x8b,0xff };
	pPatch=(unsigned char*)patch_execu1;
	dwSize=sizeof(patch_execu1);
	InitDisaDate();
}


void CAddPatch::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Radio=1;
	const char patch_execu2[0x4] = { 0x8b,0xff,0x8b,0xff };
	pPatch=(unsigned char*)patch_execu2;
	dwSize=sizeof(patch_execu2);
	InitDisaDate();
}


void CAddPatch::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Radio=2;
	const char patch_execu3[0x4] = { 0x8b,0xff,0x8b,0xff };
	pPatch=(unsigned char*)patch_execu3;
	dwSize=sizeof(patch_execu3);
	InitDisaDate();
}

BOOL CAddPatch::InitDisaDate()
{	
	//���������

	mList.DeleteAllItems();

	CProBarThread pProBarThread;
	pProBarThread.Create();
	pProBarThread.SetProValue(50);

	ULONGLONG offset=0;//���ڷ�����ַƫ��
	unsigned int mode =0;
	//�жϻ���λ��
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