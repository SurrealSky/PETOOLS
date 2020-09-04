// DataDirectoryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "DataDirectoryDlg.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"


// DataDirectoryDlg �Ի���

IMPLEMENT_DYNAMIC(DataDirectoryDlg, CDialogEx)

DataDirectoryDlg::DataDirectoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG9, pParent)
{
	pFrameDlg = NULL;
}

DataDirectoryDlg::~DataDirectoryDlg()
{
	if (pFrameDlg != NULL)
	{
		delete pFrameDlg;
		pFrameDlg = NULL;
	}
}

void DataDirectoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DataDirectoryDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON1, IDC_BUTTON52, OnBnClickedMfcbutton)
END_MESSAGE_MAP()


// DataDirectoryDlg ��Ϣ�������


BOOL DataDirectoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//����UI����
	CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CString strFormat;
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	GetDlgItem(IDC_EDIT1)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size);
	GetDlgItem(IDC_EDIT2)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	GetDlgItem(IDC_EDIT8)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size);
	GetDlgItem(IDC_EDIT9)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress);
	GetDlgItem(IDC_EDIT3)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size);
	GetDlgItem(IDC_EDIT4)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress);
	GetDlgItem(IDC_EDIT10)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].Size);
	GetDlgItem(IDC_EDIT11)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress);
	GetDlgItem(IDC_EDIT7)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size);
	GetDlgItem(IDC_EDIT12)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
	GetDlgItem(IDC_EDIT13)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size);
	GetDlgItem(IDC_EDIT14)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress);
	GetDlgItem(IDC_EDIT15)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size);
	GetDlgItem(IDC_EDIT16)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].VirtualAddress);
	GetDlgItem(IDC_EDIT17)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].Size);
	GetDlgItem(IDC_EDIT18)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].VirtualAddress);
	GetDlgItem(IDC_EDIT19)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].Size);
	GetDlgItem(IDC_EDIT20)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
	GetDlgItem(IDC_EDIT21)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size);
	GetDlgItem(IDC_EDIT22)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress);
	GetDlgItem(IDC_EDIT23)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size);
	GetDlgItem(IDC_EDIT24)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress);
	GetDlgItem(IDC_EDIT25)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size);
	GetDlgItem(IDC_EDIT26)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress);
	GetDlgItem(IDC_EDIT27)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size);
	GetDlgItem(IDC_EDIT28)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress);
	GetDlgItem(IDC_EDIT29)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].Size);
	GetDlgItem(IDC_EDIT30)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress);
	GetDlgItem(IDC_EDIT31)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size);
	GetDlgItem(IDC_EDIT32)->SetWindowText(strFormat);

	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR+1].VirtualAddress);
	GetDlgItem(IDC_EDIT33)->SetWindowText(strFormat);
	strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR+1].Size);
	GetDlgItem(IDC_EDIT34)->SetWindowText(strFormat);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void DataDirectoryDlg::OnBnClickedMfcbutton(UINT  uId)
{
	if (pFrameDlg == NULL)
	{
		pFrameDlg = new DialogFirst(AfxGetMainWnd());
		pFrameDlg->Create(IDD_DIALOG1, AfxGetMainWnd());
	}
	CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	switch (uId)
	{
		case IDC_BUTTON1:
		{
			//�����
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_EXPORT);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON8:
		{
			//�����
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_IMPORT);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON11:
		{
			//��Դ
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_RESOURCE);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON14:
		{
			//����
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_EXCEPTION);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON17:
		{
			//��ȫ
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_SECURITY);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON20:
		{
			//�ض�λ
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_BASERELOC);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON23:
		{
			//����
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_DEBUG);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON26:
		{
			//��Ȩ
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON29:
		{
			//ȫ��ָ��
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_GLOBALPTR);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON32:
		{
			//TLS ��
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_TLS);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON35:
		{
			//��������
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON38:
		{
			//���뷶Χ
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON41:
		{
			//IAT
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_IAT);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON44:
		{
			//�ӳٵ���
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON47:
		{
			//COM
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
		case IDC_BUTTON50:
		{
			//����
			if (pMainDlg->mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR+1].Size > 0)
			{
				pFrameDlg->Init(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR+1);
				pFrameDlg->ShowWindow(SW_SHOW);
			}
		}break;
	}
	
}
