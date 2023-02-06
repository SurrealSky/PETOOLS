// AddSectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "AddSectionDlg.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"
#include"resource.h"


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


// CAddSectionDlg 消息处理程序




BOOL CAddSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	// 异常: OCX 属性页应返回 FALSE
}

void CAddSectionDlg::OnBnClickedButton1()
{
	//// TODO: 在此添加控件通知处理程序代码
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
			AfxMessageBox("文件打开失败!");
			return;
		}

		DWORD dwSizeHigh = 0, dwSizeLow = 0;
		dwSizeLow = GetFileSize(mHandle, &dwSizeHigh);
		if (dwSizeLow == INVALID_FILE_SIZE || dwSizeHigh != 0)
		{
			CloseHandle(mHandle);
			AfxMessageBox("文件太大!");
			return;
		}
		STu8 * pVirMem = MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc, dwSizeLow);
		if (pVirMem == NULL)
		{
			CloseHandle(mHandle);
			AfxMessageBox("内存分配失败!");
			return;
		}

		DWORD readsize;
		if (!ReadFile(mHandle, pVirMem, dwSizeLow, &readsize, NULL))
		{
			CloseHandle(mHandle);
			AfxMessageBox("文件读取失败!");
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
			AfxMessageBox("输入大小有误");
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

//物理大小改变
void CAddSectionDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strSize;
	mSize.GetWindowTextA(strSize);
	STu32 RawSize=strtoll(strSize, 0, 16);
	if (RawSize >= 0)
	{
		//重新设置虚拟大小
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
		AfxMessageBox("输入大小有误");
	}
}


void CAddSectionDlg::OnClickedCheck8()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck())
	{
		//设置区段数据
		::EnableWindow(mbinFile, TRUE);
		mSize.SetWindowTextA("----");
		::EnableWindow(mSize, FALSE);
	}
	else
	{
		//不设置区段数据
		::EnableWindow(mbinFile, FALSE);
		mSize.SetWindowTextA("0");
		::EnableWindow(mSize, TRUE);
	}
}
