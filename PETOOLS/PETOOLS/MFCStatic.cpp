// MFCStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "MFCStatic.h"
#include "PETOOLSDlg.h"


// MFCStatic
CToolTipCtrl *m_pContentTip;

IMPLEMENT_DYNAMIC(MFCStatic, CStatic)

MFCStatic::MFCStatic()
{
}

MFCStatic::~MFCStatic()
{
}

BEGIN_MESSAGE_MAP(MFCStatic, CStatic)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

void MFCStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//TCHAR Buffer[MAX_PATH]={0};
	//this->GetWindowText(Buffer,sizeof(Buffer));
	CPETOOLSDlg *m_dd=static_cast<CPETOOLSDlg *>(AfxGetMainWnd());
	//m_dd->m_Status.SetText(this->Title,1,0);
	CStatic::OnMouseMove(nFlags, point);
}

void MFCStatic::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPETOOLSDlg *m_dd=static_cast<CPETOOLSDlg *>(AfxGetMainWnd());
	m_dd->m_Status.SetText("",1,0);
	CStatic::OnMouseLeave();
}

void MFCStatic::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	long wl = GetWindowLong(this->m_hWnd, GWL_STYLE);
	SetWindowLong(this->m_hWnd, GWL_STYLE, wl| SS_NOTIFY); 
	CStatic::PreSubclassWindow();
}
