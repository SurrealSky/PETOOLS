// AddPatch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "AddPatch.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"
#include"ProBarThread.h"
#include<disasm/disasm.h>


// CAddPatch �Ի���

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
}


BEGIN_MESSAGE_MAP(CAddPatch, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddPatch::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddPatch::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK2, &CAddPatch::OnBnClickedOk2)
END_MESSAGE_MAP()


// CAddPatch ��Ϣ�������


BOOL CAddPatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mNameEdit.SetLimitText(8);
	mNameEdit.SetWindowTextA(".xxx");
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

	//����shellcodes
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
	ByteBuffer *buffer = NULL;
	buffer=(ByteBuffer*)mBinFile.GetItemDataPtr(mBinFile.GetCurSel());
	if (buffer != NULL)
	{
		STu8 *pPatch = (STu8*)(buffer->contents());
		STu32 dwSize = buffer->size();
		bool bRet = pMainDlg->mPEMake.AddPatchAuto2OEP((STu8*)strName.GetBuffer(0), pPatch, dwSize);
		if (bRet)
			CDialogEx::OnOK();
		else
			CDialogEx::OnCancel();
		return;
	}
	CDialogEx::OnCancel();
}

BOOL CAddPatch::InitDisaDate(STu8 *pPatch, STu32 dwSize)
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
	//����shellcode
	CString strPath = GetApplicationPath();
	strPath += _T("shellcode\\");
	strPath += _T("*.bin");
	CFileFind find;
	//����bin�ļ�
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
	//����exe�ļ�
	strPath = GetApplicationPath();
	strPath += _T("shellcode\\");
	strPath += _T("*.exe");
	//����bin�ļ�
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

			HANDLE handle=::LoadLibrary(strFile);
			CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
			if (pMainDlg->mPEMake.FindCodeByPeFile((STu8*)handle, -1, code.bin))
			{
				codes.push_back(code);
			}

	/*		CFile file;
			file.Open(code.strBinFile, CFile::modeRead);
			STu32 size = file.GetLength();
			STu8 *buffer = new STu8[size];
			file.Read(buffer, size);
			CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());
			if (pMainDlg->mPEMake.FindCodeByPeFile(buffer, size, code.bin))
			{
				codes.push_back(code);
			}
			delete[] buffer;
			buffer = NULL;*/
			//file.Close();
		}
	}
	find.Close();
}

void CAddPatch::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ByteBuffer *buffer = NULL;
	buffer = (ByteBuffer*)mBinFile.GetItemDataPtr(mBinFile.GetCurSel());
	if (buffer != NULL)
	{
		STu8 *pPatch = (STu8*)(buffer->contents());
		STu32 dwSize = buffer->size();
		InitDisaDate(pPatch, dwSize);
	}
}

//ȡ��
void CAddPatch::OnBnClickedOk2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
