// MFCStatus.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "MFCStatus.h"


// MFCStatus

IMPLEMENT_DYNAMIC(MFCStatus, CStatusBarCtrl)

MFCStatus::MFCStatus()
{

}

MFCStatus::~MFCStatus()
{
}
BEGIN_MESSAGE_MAP(MFCStatus, CStatusBarCtrl)
END_MESSAGE_MAP()

void MFCStatus::SetUI()
{
	this->EnableAutomation();
	CRect rect;
	this->GetWindowRect(&rect);
	
	const int nParts = 4;
	int widths[nParts] = { 100, 600, -1 };
	this->SetParts(nParts, widths);
	this->SetText("״̬:Ready",0,0);
	//����״̬��

	this->GetClientRect(&rect);
	rect.left=600;
	rect.left+=2;
	rect.top+=2;
	rect.bottom-=2;
	rect.right-=2;
	this->m_progres.Create(WS_CHILD | WS_VISIBLE,rect,this,IDC_PROGRESS1);
	this->m_progres.SetRange32(0,100);
	this->m_progres.SetPos(0);
}


