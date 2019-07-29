// MFCStatic.cpp : ʵ���ļ�
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//TCHAR Buffer[MAX_PATH]={0};
	//this->GetWindowText(Buffer,sizeof(Buffer));
	CPETOOLSDlg *m_dd=static_cast<CPETOOLSDlg *>(AfxGetMainWnd());
	//m_dd->m_Status.SetText(this->Title,1,0);
	CStatic::OnMouseMove(nFlags, point);
}

void MFCStatic::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPETOOLSDlg *m_dd=static_cast<CPETOOLSDlg *>(AfxGetMainWnd());
	m_dd->m_Status.SetText("",1,0);
	CStatic::OnMouseLeave();
}

void MFCStatic::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	long wl = GetWindowLong(this->m_hWnd, GWL_STYLE);
	SetWindowLong(this->m_hWnd, GWL_STYLE, wl| SS_NOTIFY); 
	CStatic::PreSubclassWindow();
}
