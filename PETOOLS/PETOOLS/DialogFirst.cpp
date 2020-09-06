// DialogFirst.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogFirst.h"
#include "afxdialogex.h"
#include "MyResource.h"
#include"PETOOLSDlg.h"

// DialogFirst �Ի���

IMPLEMENT_DYNAMIC(DialogFirst, CDialogEx)

DialogFirst::DialogFirst(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogFirst::IDD, pParent)
{
}

DialogFirst::~DialogFirst()
{
}

void DialogFirst::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC57, m_Static4);
	DDX_Control(pDX, IDC_STATIC58, m_Static5);
	DDX_Control(pDX, IDC_STATIC59, m_Static6);
	DDX_Control(pDX, IDC_STATIC5, m_Static7);
	DDX_Control(pDX, IDC_STATIC6, m_Static8);
	DDX_Control(pDX, IDC_STATIC60, m_Static9);
	DDX_Control(pDX, IDC_STATIC61, m_Static10);
	DDX_Control(pDX, IDC_STATIC62, m_Static11);
	DDX_Control(pDX, IDC_STATIC63, m_Static12);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_Edit1);
	DDX_Control(pDX, IDC_MFCEDITBROWSE52, m_Edit2);
	DDX_Control(pDX, IDC_MFCEDITBROWSE53, m_Edit3);
	DDX_Control(pDX, IDC_MFCEDITBROWSE54, m_Edit4);
	DDX_Control(pDX, IDC_MFCEDITBROWSE55, m_Edit5);
	DDX_Control(pDX, IDC_MFCEDITBROWSE56, m_Edit6);
	DDX_Control(pDX, IDC_MFCEDITBROWSE57, m_Edit7);
	DDX_Control(pDX, IDC_MFCEDITBROWSE58, m_Edit8);
	DDX_Control(pDX, IDC_MFCEDITBROWSE59, m_Edit9);
	DDX_Control(pDX, IDC_MFCEDITBROWSE60, m_Edit10);
	DDX_Control(pDX, IDC_MFCEDITBROWSE61, m_Edit11);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Control(pDX, IDC_LIST3, m_List3);
	DDX_Control(pDX, IDC_LIST4, m_List4);
	DDX_Control(pDX, IDC_LIST6, m_List6);
	DDX_Control(pDX, IDC_LIST5, m_List5);
}


BEGIN_MESSAGE_MAP(DialogFirst, CDialogEx)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// DialogFirst ��Ϣ�������


BOOL DialogFirst::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void DialogFirst::Init(int mArgu)
{
	dwArgu=mArgu;
	mUiVisible.isDelayImport=false;
	mUiVisible.isExport=false;
	mUiVisible.isImport=false;
	mUiVisible.isReloc=false;
	mUiVisible.isResource=false;
	SetDlgUI();
}

BOOL DialogFirst::SetDlgUI()
{
	//�жϵ�ǰ�ĶԻ������ͣ�������������
	char Argu[128]={0};
	switch(dwArgu)
	{
		case IMAGE_DIRECTORY_ENTRY_EXPORT:
			{
				memcpy_s(Argu,sizeof(Argu),"Dialog1",sizeof(Argu));
				mUiVisible.isExport=true;
			}break;
		case IMAGE_DIRECTORY_ENTRY_IMPORT:
			{
				memcpy_s(Argu,sizeof(Argu),"Dialog2",sizeof(Argu));
				mUiVisible.isImport=true;
			}break;
		case IMAGE_DIRECTORY_ENTRY_BASERELOC:
			{
				memcpy_s(Argu,sizeof(Argu),"Dialog3",sizeof(Argu));
				mUiVisible.isReloc=true;
			}break;
		case IMAGE_DIRECTORY_ENTRY_RESOURCE:
			{
				memcpy_s(Argu,sizeof(Argu),"Dialog4",sizeof(Argu));
				mUiVisible.isResource=true;
			}break;
		case IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT:
			{
				memcpy_s(Argu,sizeof(Argu),"Dialog5",sizeof(Argu));
				mUiVisible.isDelayImport=true;
			}break;
		default:
			{
				memcpy_s(Argu,sizeof(Argu),"DefaultDialog",sizeof(Argu));
			}break;
	}

	////����MainFrame���
	int x=0,y=0,height=0,width=0;
	char TextDisplay[MAX_PATH]={0};
	height=m_Ini.GetIntKey("configure.ini",Argu,"height");
	width=m_Ini.GetIntKey("configure.ini",Argu,"width");
	x=(GetSystemMetrics(SM_CXSCREEN)-width)/2;
	y=(GetSystemMetrics(SM_CYSCREEN)-height)/2;
	this->MoveWindow(x,y,width,height,TRUE);
	this->m_Ini.GetStrKey("configure.ini",Argu,"title",TextDisplay);
	this->SetWindowText(TextDisplay);


	//����UI����
	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(AfxGetMainWnd());


	pMainDlg->SetControlUI("configure.ini",&this->m_Static1,"D1Static1",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static2,"D1Static2",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static3,"D1Static3",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static4,"D1Static4",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static5,"D1Static5",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static6,"D1Static6",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static7,"D1Static7",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static8,"D1Static8",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static9,"D1Static9",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static10,"D1Static10",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static11,"D1Static11",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Static12,"D1Static12",mUiVisible.isExport);

	pMainDlg->SetControlUI("configure.ini",&this->m_Edit1,"D1Edit1",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit2,"D1Edit2",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit3,"D1Edit3",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit4,"D1Edit4",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit5,"D1Edit5",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit6,"D1Edit6",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit7,"D1Edit7",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit8,"D1Edit8",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit9,"D1Edit9",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit10,"D1Edit10",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_Edit11,"D1Edit11",TRUE,mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_List1,"D1ListBox1",mUiVisible.isExport);
	pMainDlg->SetControlUI("configure.ini",&this->m_List2,"D1ListBox2",mUiVisible.isImport);
	pMainDlg->SetControlUI("configure.ini",&this->m_List3,"D1ListBox3",mUiVisible.isImport|mUiVisible.isReloc|mUiVisible.isResource|mUiVisible.isDelayImport);
	pMainDlg->SetControlUI("configure.ini",&this->m_List4,"D1ListBox4",mUiVisible.isReloc);
	pMainDlg->SetControlUI("configure.ini",&this->m_List5,"D1ListBox5",mUiVisible.isDelayImport);
	pMainDlg->SetControlUI("configure.ini",&this->m_List6,"D1ListBox6",mUiVisible.isResource);


	switch(dwArgu)
	{
		case IMAGE_DIRECTORY_ENTRY_IMPORT:
			{
				this->m_List3.Clear();
				TCHAR  _column[][MAX_HEADLENGTH]={"���","ThunkRVA","ThunkFOA","Thunkֵ(RVA)","���","��������"};
				this->m_List3.SetHeaders(_column,sizeof(_column)/sizeof(*_column));
			}break;
		case IMAGE_DIRECTORY_ENTRY_BASERELOC:
			{
				this->m_List3.Clear();
				TCHAR  _column[][MAX_HEADLENGTH]={"���","���ݵ�ַ(RVA)","���ݵ�ַ(FOA)","����"};
				this->m_List3.SetHeaders(_column,sizeof(_column)/sizeof(*_column));
			}break;
		case IMAGE_DIRECTORY_ENTRY_RESOURCE:
			{
				this->m_List3.Clear();
				TCHAR  _column[][MAX_HEADLENGTH]={"���","��ԴID","��������(ID)","���ݵ�ַ(RVA)","���ݵ�ַ(FOA)","���ݴ�С(Bytes)"};
				this->m_List3.SetHeaders(_column,sizeof(_column)/sizeof(*_column));
			}break;
		case IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT:
			{
				this->m_List3.Clear();
				TCHAR  _column[][MAX_HEADLENGTH]={"���","��������","���","������ַ(RVA)"};
				this->m_List3.SetHeaders(_column,sizeof(_column)/sizeof(*_column));
			}break;
		default:
			{
				this->m_List3.Clear();
			}break;
	}
	//�����߳�
	_beginthreadex(NULL,NULL,DialogFirst::WorkThreadProc,this,NULL,NULL);

	return TRUE;
}

BOOL DialogFirst::SetExportCtrl()
{
	this->m_List1.Clear();
	char  column[][MAX_HEADLENGTH]={"���","������","������ַ(RVA)","������ַ(FOA)"};
	this->m_List1.SetHeaders(column,sizeof(column)/sizeof(*column));

	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(m_pParentWnd);
	//�������
	for(int i=0;i<pMainDlg->mPEMake.mPeCtx.pe.mExport.mOrdinalFuncsVector.size();i++)
	{
		CString strFormat;
		strFormat.Format("%d",i+1);
		this->m_List1.InsertItem(i,strFormat);

		this->m_List1.SetItemText(i,1,pMainDlg->mPEMake.mPeCtx.pe.mExport.mOrdinalFuncsVector[i].strFuncName.c_str());

#ifdef PE_MODEL
		strFormat.Format("%08X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mOrdinalFuncsVector[i].Func);
#else
		strFormat.Format("%16X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mOrdinalFuncsVector[i].Func);
#endif
		this->m_List1.SetItemText(i,2,strFormat);

#ifdef PE_MODEL
		strFormat.Format("%08X",pMainDlg->mPEMake.RvaToFoa(pMainDlg->mPEMake.mPeCtx.pe.mExport.mOrdinalFuncsVector[i].Func));
#else
		strFormat.Format("%16X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mOrdinalFuncsVector[i].Func);
#endif
		this->m_List1.SetItemText(i,3,strFormat);

	}	
	
	return TRUE;
}

BOOL DialogFirst::SetImportCtrl()
{
	////�������õ�һ��ListCtrl����
	this->m_List2.Clear();
	char  column[][MAX_HEADLENGTH]={"���","DLL����","��1(RVA)","ʱ���","ǰ���ṹ","��2(RVA)"};
	this->m_List2.SetHeaders(column,sizeof(column)/sizeof(*column));

	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(m_pParentWnd);
	for(int i=0;i<pMainDlg->mPEMake.mPeCtx.pe.mImportsVector.size();i++)
	{
		CString ctrFormat;
		ctrFormat.Format("%d",i+1);
		this->m_List2.InsertItem(i,ctrFormat);

		ctrFormat.Format("%s",pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[i].strDllName.c_str());
		this->m_List2.SetItemText(i,1,ctrFormat);

		ctrFormat.Format("%08X",pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[i].mDescriptor.OriginalFirstThunk);
		this->m_List2.SetItemText(i,2,ctrFormat);

		ctrFormat.Format("%08X",pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[i].mDescriptor.TimeDateStamp);
		this->m_List2.SetItemText(i,3,ctrFormat);

		ctrFormat.Format("%08X",pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[i].mDescriptor.ForwarderChain);
		this->m_List2.SetItemText(i,4,ctrFormat);

		ctrFormat.Format("%08X",pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[i].mDescriptor.FirstThunk);
		this->m_List2.SetItemText(i,5,ctrFormat);
	}
	
	return TRUE;
}

BOOL DialogFirst::SetReloc()
{
	this->m_List4.Clear();
	char  column[][MAX_HEADLENGTH]={"���","ҳ���ַ(RVA)","ҳ���ַ(FOA)","���ݿ��С"};
	this->m_List4.SetHeaders(column,sizeof(column)/sizeof(*column));

	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(m_pParentWnd);
	for(int i=0;i<pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector.size();i++)
	{
		CString strFormat;
		strFormat.Format("%d",i+1);
		this->m_List4.InsertItem(i,strFormat);
		strFormat.Format("0x%08X",pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector[i].mBaseRelocation.VirtualAddress);
		this->m_List4.SetItemText(i,1,strFormat);
		strFormat.Format("0x%08X",pMainDlg->mPEMake.RvaToFoa(pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector[i].mBaseRelocation.VirtualAddress));
		this->m_List4.SetItemText(i,2,strFormat);
		strFormat.Format("0x%X",pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector[i].mBaseRelocation.SizeOfBlock);
		this->m_List4.SetItemText(i,3,strFormat);
	}
	
	return TRUE;
}

BOOL DialogFirst::SetResource()
{	
	this->m_List6.Clear();
	char  column[][MAX_HEADLENGTH]={"���","��Դ����"};
	this->m_List6.SetHeaders(column,sizeof(column)/sizeof(*column));

	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(m_pParentWnd);
	for(int i=0;i<pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector.size();i++)
	{
		CString strFormat;
		strFormat.Format("%d",i+1);
		this->m_List6.InsertItem(i,strFormat);
		if(pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[i].dwType==0)
		{
			_bstr_t t = pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[i].wstrType.c_str();
			char* pchar = (char*)t;
			std::string strTemp = pchar;
			this->m_List6.SetItemText(i,1,strTemp.c_str());
		}else
		{
			strFormat.Format("0x%X",pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[i].dwType);
			this->m_List6.SetItemText(i,1,strFormat);
		}
	}
	return TRUE;
}

BOOL DialogFirst::SetRelay()
{
	this->m_List5.Clear();
	char  column[][MAX_HEADLENGTH]={"���","DLL����","����","�ӳٵ���IAT(RVA)","�ӳٵ���INT(RVA)","ʱ���"};
	this->m_List5.SetHeaders(column,sizeof(column)/sizeof(*column));
	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(m_pParentWnd);

	for(int i=0;i<pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector.size();i++)
	{
		CString strFormat;
		strFormat.Format("%d",i+1);
		this->m_List5.InsertItem(i,strFormat);

		strFormat.Format("%s",pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[i].strDllName.c_str());
		this->m_List5.SetItemText(i,1,strFormat);

		strFormat.Format("%08X",pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[i].mDescriptor.grAttrs);
		this->m_List5.SetItemText(i,2,strFormat);

		strFormat.Format("%08X",pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[i].mDescriptor.rvaIAT);
		this->m_List5.SetItemText(i,3,strFormat);

		strFormat.Format("%08X",pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[i].mDescriptor.rvaINT);
		this->m_List5.SetItemText(i,4,strFormat);

		strFormat.Format("%08X",pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[i].mDescriptor.dwTimeStamp);
		this->m_List5.SetItemText(i,5,strFormat);
	}
	return TRUE;
}

unsigned int __stdcall DialogFirst::WorkThreadProc(void *lpParameter)
{
	
	DialogFirst *Dialog=static_cast<DialogFirst *>(lpParameter);
	CPETOOLSDlg *pMainDlg=static_cast<CPETOOLSDlg*>(Dialog->m_pParentWnd);
	CString strFormat;
	if(Dialog->dwArgu==IMAGE_DIRECTORY_ENTRY_EXPORT)
	{
		if(pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.NumberOfFunctions==0)
		{
			return FALSE;
		}

		Dialog->m_Edit1.SetWindowText(pMainDlg->mPEMake.mPeCtx.pe.mExport.strDllName.c_str());
		
		strFormat.Format("0X%X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.NumberOfFunctions);
		Dialog->m_Edit2.SetWindowText(strFormat);

		strFormat.Format("0X%X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.NumberOfNames);
		Dialog->m_Edit3.SetWindowText(strFormat);

		strFormat.Format("0X%08X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.AddressOfFunctions);
		Dialog->m_Edit4.SetWindowText(strFormat);

		strFormat.Format("0X%X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.Base);
		Dialog->m_Edit5.SetWindowText(strFormat);

		strFormat.Format("0X%08X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.AddressOfNames);
		Dialog->m_Edit6.SetWindowText(strFormat);

		strFormat.Format("0X%08X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.AddressOfNameOrdinals);
		Dialog->m_Edit7.SetWindowText(strFormat);

		strFormat.Format("0X%08X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.Characteristics);
		Dialog->m_Edit8.SetWindowText(strFormat);

		strFormat.Format("%d",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.MajorVersion);
		Dialog->m_Edit9.SetWindowText(strFormat);

		strFormat.Format("%d",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.MinorVersion);
		Dialog->m_Edit10.SetWindowText(strFormat);

		strFormat.Format("0X%08X",pMainDlg->mPEMake.mPeCtx.pe.mExport.mDirectorys.TimeDateStamp);
		Dialog->m_Edit11.SetWindowText(strFormat);
		//����ListCtrl����
		Dialog->SetExportCtrl();
	}else if(Dialog->dwArgu==IMAGE_DIRECTORY_ENTRY_IMPORT)
	{
		if(pMainDlg->mPEMake.mPeCtx.pe.mImportsVector.size()==0)
		{
			return FALSE;
		}
		//����ListCtrl����
		Dialog->SetImportCtrl();
	}else if(Dialog->dwArgu==IMAGE_DIRECTORY_ENTRY_BASERELOC)
	{
		if(pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector.size()==0)
		{
			return FALSE;
		}
		Dialog->SetReloc();
	}else if(Dialog->dwArgu==IMAGE_DIRECTORY_ENTRY_RESOURCE)
	{
		if(pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector.size()==0)
		{
			return FALSE;
		}
		Dialog->SetResource();
	}else if(Dialog->dwArgu==IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT)
	{
		if(pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector.size()==0)
		{
			return FALSE;
		}
		Dialog->SetRelay();
	}else
	{
		//Dialog->CloseWindow();
		AfxMessageBox("N/A");
		return FALSE;
	}
	
	return TRUE;
}

void DialogFirst::Reset()
{
	//�����еĿؼ����ݺ�״̬��ԭ
	EnumChildWindows(this->m_hWnd,DialogFirst::EnumChildProc,(LPARAM)this);
	return;
}

BOOL CALLBACK DialogFirst::EnumChildProc(HWND hwnd,LPARAM lParam)
{
	DialogFirst *DlgFirst=static_cast<DialogFirst *>((PVOID)lParam);
	CWnd *Wnd=DlgFirst->GetDlgItem(::GetDlgCtrlID(hwnd));
	if(Wnd==NULL) return TRUE;
	BOOL isVisible=Wnd->ShowWindow(SW_HIDE);
	if(isVisible==FALSE)
	{
		return TRUE;
	}else
	{
		Wnd->ShowWindow(SW_SHOWNORMAL);
	}
	if(Wnd->GetRuntimeClass()==RUNTIME_CLASS(MFCEdit))
	{
		Wnd->SetWindowText("");
	}else if(Wnd->GetRuntimeClass()==RUNTIME_CLASS(MyListCtrl))
	{
		MyListCtrl *LCtrl=static_cast<MyListCtrl *>(Wnd);
		LCtrl->DeleteAllItems();
	}
	return TRUE;
}
