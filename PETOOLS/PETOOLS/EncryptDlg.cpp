// EncryptDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "EncryptDlg.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"


// CEncryptDlg �Ի���

IMPLEMENT_DYNAMIC(CEncryptDlg, CDialogEx)

CEncryptDlg::CEncryptDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncryptDlg::IDD, pParent)
{

}

CEncryptDlg::~CEncryptDlg()
{
}

void CEncryptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, mTabCtrl);
}


BEGIN_MESSAGE_MAP(CEncryptDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CEncryptDlg::OnSelchangeTab1)
	ON_MESSAGE(MSG_SAVE, &CEncryptDlg::OnMsgSave)
END_MESSAGE_MAP()


// CEncryptDlg ��Ϣ�������


BOOL CEncryptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	/*

	CPETOOLSDlg *pMainDlg=dynamic_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	pMainDlg->mPeProtect.CopyPeCtx(pMainDlg->mPeProtect.mNewCtx,pMainDlg->mPeProtect.mBaseCtx);

	mTabCtrl.InsertItem(0,"��ʽһ");  //��Ӳ���һѡ� 
	mTabCtrl.InsertItem(1,"��ʽ��");  //��Ӳ�����ѡ� 
	mTabCtrl.InsertItem(2,"��ʽ��");    //��ӽ��ѡ�

	CRect rec;
	mTabCtrl.GetClientRect(&rec);//���TAB�ؼ�������
	
    rec.left += 1;
    rec.top += 23;
    rec.right -= 1;
	rec.bottom -= 3;

	mpage1.Create(IDD_DIALOG6,this);
	mpage1.MoveWindow(&rec);
	mpage1.ShowWindow(SW_SHOW);

	mpage2.Create(IDD_DIALOG7,this);
	mpage2.MoveWindow(&rec);
	mpage2.ShowWindow(SW_HIDE);

	*/
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CEncryptDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(mTabCtrl.GetCurSel())
    {
		case 0:
			{
				mpage1.ShowWindow(SW_SHOW);
				mpage2.ShowWindow(SW_HIDE);
			}break;
		case 1:
			 {
				mpage1.ShowWindow(SW_HIDE);
				mpage2.ShowWindow(SW_SHOW);
			 }break;
      default:
		  {
		  }
            break;
    }
	*pResult = 0;
}

//�����ļ�
afx_msg LRESULT CEncryptDlg::OnMsgSave(WPARAM wParam, LPARAM lParam)
{
	/*
	CPETOOLSDlg *pMainDlg=dynamic_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CFileDialog dlg(FALSE,"exe",pMainDlg->mPeProtect.mNewCtx.path.c_str(),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"TXT Files(*.exe)|*.exe|All Files(*.*)|*.*");
   ///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���  
	if(dlg.DoModal()==IDOK)  
	{
		CFile mFile(dlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
		mFile.Write(pMainDlg->mPeProtect.mNewCtx.pVirMem,pMainDlg->mPeProtect.mNewCtx.size);
		mFile.Close();
		AfxMessageBox("���ɹ�");
		EndDialog(IDOK);
	}
	*/
	return 0;
}
