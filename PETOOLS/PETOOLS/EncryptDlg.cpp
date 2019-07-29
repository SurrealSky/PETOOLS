// EncryptDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "EncryptDlg.h"
#include "afxdialogex.h"
#include"PETOOLSDlg.h"


// CEncryptDlg 对话框

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


// CEncryptDlg 消息处理程序


BOOL CEncryptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	/*

	CPETOOLSDlg *pMainDlg=dynamic_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	pMainDlg->mPeProtect.CopyPeCtx(pMainDlg->mPeProtect.mNewCtx,pMainDlg->mPeProtect.mBaseCtx);

	mTabCtrl.InsertItem(0,"方式一");  //添加参数一选项卡 
	mTabCtrl.InsertItem(1,"方式二");  //添加参数二选项卡 
	mTabCtrl.InsertItem(2,"方式三");    //添加结果选项卡

	CRect rec;
	mTabCtrl.GetClientRect(&rec);//获得TAB控件的坐标
	
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
	// 异常: OCX 属性页应返回 FALSE
}

void CEncryptDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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

//保存文件
afx_msg LRESULT CEncryptDlg::OnMsgSave(WPARAM wParam, LPARAM lParam)
{
	/*
	CPETOOLSDlg *pMainDlg=dynamic_cast<CPETOOLSDlg*>(AfxGetMainWnd());
	CFileDialog dlg(FALSE,"exe",pMainDlg->mPeProtect.mNewCtx.path.c_str(),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"TXT Files(*.exe)|*.exe|All Files(*.*)|*.*");
   ///TRUE为OPEN对话框，FALSE为SAVE AS对话框  
	if(dlg.DoModal()==IDOK)  
	{
		CFile mFile(dlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
		mFile.Write(pMainDlg->mPeProtect.mNewCtx.pVirMem,pMainDlg->mPeProtect.mNewCtx.size);
		mFile.Close();
		AfxMessageBox("另存成功");
		EndDialog(IDOK);
	}
	*/
	return 0;
}
