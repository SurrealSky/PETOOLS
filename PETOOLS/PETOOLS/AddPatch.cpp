// AddPatch.cpp : 实现文件
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "AddPatch.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"
#include"ProBarThread.h"
#include<disasm/disasm.h>
#include<Hex.h>


// CAddPatch 对话框

IMPLEMENT_DYNAMIC(CAddPatch, CDialogEx)

CAddPatch::CAddPatch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddPatch::IDD, pParent)
{
}

CAddPatch::~CAddPatch()
{
}

void CAddPatch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mNameEdit);
	DDX_Control(pDX, IDC_LIST1, mList);
	DDX_Control(pDX, IDC_COMBO1, mBinFile);
	DDX_Control(pDX, IDC_EDIT2, mJmpCode);
	DDX_Control(pDX, IDC_EDIT3, mNopBytes);
}


BEGIN_MESSAGE_MAP(CAddPatch, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddPatch::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddPatch::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK2, &CAddPatch::OnBnClickedOk2)
	ON_BN_CLICKED(IDC_RADIO1, &CAddPatch::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAddPatch::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CAddPatch 消息处理程序


BOOL CAddPatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mNameEdit.SetLimitText(8);
	mNameEdit.SetWindowTextA(".xxx");
	
	CheckDlgButton(IDC_RADIO1, TRUE);
	mJmpCode.EnableWindow(FALSE);
	mJmpCode.SetWindowTextA("E9F0F0F0F0");

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

	//加载shellcodes
	LoadShellCodes(shellcodes);

	std::list<ShellCode>::iterator itor = shellcodes.begin();
	for (; itor!= shellcodes.end(); itor++)
	{
		this->mBinFile.AddString(itor->strBinFile);
		mBinFile.SetItemDataPtr(mBinFile.GetCount() - 1, &(itor->bin));
	}
	mBinFile.SetCurSel(0);
	OnCbnSelchangeCombo1();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddPatch::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CString strName;
	mNameEdit.GetWindowTextA(strName);
	if(strName.GetLength()==0)
	{
		AfxMessageBox("区段名为空!");
		return;
	}
	STu32 nopbytes = 0;
	CString strNopBytes;
	mNopBytes.GetWindowTextA(strNopBytes);
	nopbytes = strtoll(strNopBytes, 0, 0x10);

	ByteBuffer *buffer = NULL;
	buffer=(ByteBuffer*)mBinFile.GetItemDataPtr(mBinFile.GetCurSel());
	if (buffer != NULL)
	{
		STu8 *pPatch = (STu8*)(buffer->contents());
		STu32 dwSize = buffer->size();

		bool bRet = FALSE;
		if (IsDlgButtonChecked(IDC_RADIO2))
		{
			//修正JMP OEP
			CString strJmp;
			mJmpCode.GetWindowTextA(strJmp);
			strJmp.Remove(' ');
			SurrealHex::HexConvert mHex;
			std::string strJmpCode = mHex.StrToHex((STu8*)strJmp.GetBuffer(0), strJmp.GetLength());

			STu32 offset = MemofOffset(pPatch, dwSize, (STu8*)strJmpCode.c_str(), strJmpCode.size());
			offset += 1;//跳过E9指令
			bRet = pMainDlg->mPEMake.AddPatch((STu8*)strName.GetBuffer(0), pPatch, dwSize, offset, nopbytes);
		}
		else
		{
			//添加JMP OEP
			bRet = pMainDlg->mPEMake.AddPatchAuto2OEP((STu8*)strName.GetBuffer(0), pPatch, dwSize, nopbytes);
		}
		if (bRet)
			CDialogEx::OnOK();
		else
			CDialogEx::OnCancel();
		return;
	}
	CDialogEx::OnCancel();
}

STu32 CAddPatch::MemofOffset(const STu8 *data, const STu32 data_len, const STu8 *pbyte,const STu32 pbyte_len)
{
	bool ok = false;
	int i, j;
	for (i = 0; i <= data_len - pbyte_len; i++)
	{
		if (data[i] == pbyte[0] && data[i + pbyte_len - 1] == pbyte[pbyte_len - 1])
		{
			for (j = 1; j<pbyte_len - 1; j++)
			{
				if (pbyte[j] != 0x3f && pbyte[j] != data[i + j])break;
			}
			if (j == pbyte_len - 1) { ok = true; break; }
		}
	}
	if (ok)
		return i;
	else
		return -1;

}

BOOL CAddPatch::InitDisaDate(STu8 *pPatch, STu32 dwSize)
{	
	//先清除数据

	mList.DeleteAllItems();

	CProBarThread pProBarThread;
	pProBarThread.Create();
	pProBarThread.SetProValue(50);

	ULONGLONG offset=0;//用于反汇编地址偏移
	unsigned int mode =0;
	//判断机器位数
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

CString CAddPatch::GetApplicationPath()
{
	TCHAR filename[_MAX_PATH];
	TCHAR drive[_MAX_DRIVE];
	TCHAR path[_MAX_PATH];

	GetModuleFileName(AfxGetInstanceHandle(), filename, MAX_PATH);
	_tsplitpath_s(filename, drive, _MAX_DRIVE, path, _MAX_PATH, NULL, 0, NULL, 0);

	CString strLocation(drive);
	strLocation += path;

	return strLocation;
}

void CAddPatch::LoadShellCodes(std::list<ShellCode> &codes)
{
	//加载shellcode
	CString strPath = GetApplicationPath();
	strPath += _T("shellcode\\");
	strPath += _T("*.bin");
	CFileFind find;
	//查找bin文件
	BOOL bIsFind = find.FindFile(strPath);
	while (bIsFind)
	{
		bIsFind = find.FindNextFile();

		if (find.IsDots())
			continue;
		else if (find.IsDirectory())
			continue;
		else
		{
			CString strFileName = find.GetFileName();
			CString strFile = strPath;
			strFile.Replace(_T("*.bin"), strFileName);
			ShellCode code;
			code.strBinFile = strFile;

			CFile file;
			file.Open(code.strBinFile, CFile::modeRead);
			STu32 size = file.GetLength();
			STu8 *buffer = new STu8[size];
			file.Read(buffer, size);
			code.bin.append(buffer, size);
			delete[] buffer;
			buffer = NULL;
			file.Close();
			codes.push_back(code);
		}
	}
	find.Close();
	//查找exe文件
	strPath = GetApplicationPath();
	strPath += _T("shellcode\\");
	strPath += _T("*.exe");
	bIsFind = find.FindFile(strPath);
	while (bIsFind)
	{
		bIsFind = find.FindNextFile();

		if (find.IsDots())
			continue;
		else if (find.IsDirectory())
			continue;
		else
		{
			CString strFileName = find.GetFileName();
			CString strFile = strPath;
			strFile.Replace(_T("*.exe"), strFileName);
			ShellCode code;
			code.strBinFile = strFile;

			HMODULE handle=::LoadLibrary(strFile);
			if (handle)
			{
				CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
				if (pMainDlg->mPEMake.FindCodeByPeFile((STu8*)handle, -1, code.bin))
				{
					codes.push_back(code);
				}
				FreeLibrary(handle);
			}
		}
	}
	find.Close();
}

void CAddPatch::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	ByteBuffer *buffer = NULL;
	buffer = (ByteBuffer*)mBinFile.GetItemDataPtr(mBinFile.GetCurSel());
	if (buffer != NULL)
	{
		STu8 *pPatch = (STu8*)(buffer->contents());
		STu32 dwSize = buffer->size();
		InitDisaDate(pPatch, dwSize);
	}
}

//取消
void CAddPatch::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CAddPatch::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		mJmpCode.EnableWindow(FALSE);
		mJmpCode.SetWindowTextA("E9F0F0F0F0");
	}
	else if (IsDlgButtonChecked(IDC_RADIO2))
	{
		mJmpCode.EnableWindow(TRUE);
		mJmpCode.SetWindowTextA("E9F0F0F0F0");
	}
}
