// AddSectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "AddSectionDlg.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"
#include"resource.h"


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
	DDX_Control(pDX, IDC_EDIT35, mDataOffset);
	DDX_Control(pDX, IDC_EDIT8, mVirtualOffset);
	DDX_Control(pDX, IDC_EDIT9, mVirtualSize);
	DDX_Control(pDX, IDC_EDIT4, mSize);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, mbinFile);
}


BEGIN_MESSAGE_MAP(CAddSectionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddSectionDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT4, &CAddSectionDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_CHECK8, &CAddSectionDlg::OnClickedCheck8)
END_MESSAGE_MAP()


// CAddSectionDlg ��Ϣ�������




BOOL CAddSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mNameEdit.SetLimitText(8);
	mSize.SetLimitText(8);
	mSize.SetWindowTextA("00000000");
	mNameEdit.SetWindowTextA(".NewSec");
	CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	STu32 VirtualOffset = pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector.back().VirtualAddress
		+ pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector.back().SizeOfRawData;
	CString strFormat;
	strFormat.Format("%08X", VirtualOffset);
	mVirtualOffset.SetWindowTextA(strFormat);
	strFormat.Format("%08X", 0);
	mVirtualSize.SetWindowTextA(strFormat);
	STu32 DataOffset = pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector.back().PointerToRawData
		+ pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector.back().SizeOfRawData;
	strFormat.Format("%08X", DataOffset);
	mDataOffset.SetWindowTextA(strFormat);
	strFormat.Format("%08X", 0);
	mDataLength.SetWindowTextA(strFormat);

	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(1);

	::EnableWindow(mbinFile, FALSE);
	::EnableWindow(mSize, TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAddSectionDlg::OnBnClickedButton1()
{
	//// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPETOOLSDlg* pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CString strName;
	mNameEdit.GetWindowTextA(strName);
	if (strName.GetLength() == 0) strName = ".null";
	
	STu32 characteristics = 0;
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		characteristics |= IMAGE_SCN_MEM_SHARED;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
	{
		characteristics |= IMAGE_SCN_MEM_EXECUTE;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
	{
		characteristics |= IMAGE_SCN_MEM_READ;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck())
	{
		characteristics |= IMAGE_SCN_MEM_WRITE;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck())
	{
		characteristics |= IMAGE_SCN_CNT_CODE;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck())
	{
		characteristics |= IMAGE_SCN_CNT_INITIALIZED_DATA;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck())
	{
		characteristics |= IMAGE_SCN_CNT_UNINITIALIZED_DATA;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck())
	{
		CString binFile = "";
		mbinFile.GetWindowTextA(binFile);
		HANDLE mHandle = CreateFile(binFile.GetBuffer(0), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == mHandle)
		{
			AfxMessageBox("�ļ���ʧ��!");
			return;
		}

		DWORD dwSizeHigh = 0, dwSizeLow = 0;
		dwSizeLow = GetFileSize(mHandle, &dwSizeHigh);
		if (dwSizeLow == INVALID_FILE_SIZE || dwSizeHigh != 0)
		{
			CloseHandle(mHandle);
			AfxMessageBox("�ļ�̫��!");
			return;
		}
		STu8 * pVirMem = MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc, dwSizeLow);
		if (pVirMem == NULL)
		{
			CloseHandle(mHandle);
			AfxMessageBox("�ڴ����ʧ��!");
			return;
		}

		DWORD readsize;
		if (!ReadFile(mHandle, pVirMem, dwSizeLow, &readsize, NULL))
		{
			CloseHandle(mHandle);
			AfxMessageBox("�ļ���ȡʧ��!");
			return;
		}
		CloseHandle(mHandle);
		bool bRet = pMainDlg->mPEMake.AddSectionToEnd((STu8*)strName.GetBuffer(0), pVirMem, readsize, characteristics);
		if (bRet)
			CDialogEx::OnOK();
		else
			CDialogEx::OnCancel();
		MemMgr::GetInstance().CommonDeallocate(TypeSGIVirtualAllocTAlloc, pVirMem);
	}
	else
	{
		CString strSize;
		mSize.GetWindowTextA(strSize);
		STu32 size = strtoll(strSize, 0, 16);
		if (size == 0)
		{
			AfxMessageBox("�����С����");
			CDialogEx::OnCancel();
			return;
		}
		bool bRet = pMainDlg->mPEMake.AddSectionToEnd((STu8*)strName.GetBuffer(0), NULL,size, characteristics);
		if (bRet)
			CDialogEx::OnOK();
		else
			CDialogEx::OnCancel();
	}
	
}

//�����С�ı�
void CAddSectionDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strSize;
	mSize.GetWindowTextA(strSize);
	STu32 RawSize=strtoll(strSize, 0, 16);
	if (RawSize >= 0)
	{
		//�������������С
		CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
		STu32 iVirtualSize = pMainDlg->mPEMake.SectionAlignmentSize(RawSize);
		STu32 iFileAlignSize = pMainDlg->mPEMake.FileAlignmentSize(RawSize);
		CString strFormat;
		strFormat.Format("%08X", iVirtualSize);
		mVirtualSize.SetWindowTextA(strFormat);
		strFormat.Format("%08X", iFileAlignSize);
		mDataLength.SetWindowTextA(strFormat);
	}
	else
	{
		AfxMessageBox("�����С����");
	}
}


void CAddSectionDlg::OnClickedCheck8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck())
	{
		//������������
		::EnableWindow(mbinFile, TRUE);
		mSize.SetWindowTextA("----");
		::EnableWindow(mSize, FALSE);
	}
	else
	{
		//��������������
		::EnableWindow(mbinFile, FALSE);
		mSize.SetWindowTextA("0");
		::EnableWindow(mSize, TRUE);
	}
}
