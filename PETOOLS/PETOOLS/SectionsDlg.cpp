// SectionsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "SectionsDlg.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"


// SectionsDlg �Ի���

IMPLEMENT_DYNAMIC(SectionsDlg, CDialogEx)

SectionsDlg::SectionsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG10, pParent)
{

}

SectionsDlg::~SectionsDlg()
{
}

void SectionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(SectionsDlg, CDialogEx)
END_MESSAGE_MAP()


// SectionsDlg ��Ϣ�������


BOOL SectionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	TCHAR  column[][MAX_HEADLENGTH] = { "����","VOffset","VSize","ROffset" ,"RSize","��־"};
	this->m_List1.SetHeaders(column, sizeof(column) / sizeof(*column));

	CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(AfxGetMainWnd());

	for (int i = 0; i<pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector.size(); i++)
	{
		CString strFormat;
		strFormat.Format("%s", pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector[i].Name);
		this->m_List1.InsertItem(i, strFormat);
		strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector[i].VirtualAddress);
		this->m_List1.SetItemText(i, 1, strFormat);
		strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector[i].Misc.VirtualSize);
		this->m_List1.SetItemText(i, 2, strFormat);
		strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector[i].PointerToRawData);
		this->m_List1.SetItemText(i, 3, strFormat);
		strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector[i].SizeOfRawData);
		this->m_List1.SetItemText(i, 4, strFormat);
		strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mSectionsVector[i].Characteristics);
		this->m_List1.SetItemText(i, 5, strFormat);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
