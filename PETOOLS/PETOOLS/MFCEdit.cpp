// MFCEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "MFCEdit.h"
#include<afxeditbrowsectrl.h>


// MFCEdit

IMPLEMENT_DYNAMIC(MFCEdit,CEdit)

MFCEdit::MFCEdit()
{

}

MFCEdit::~MFCEdit()
{
}


BEGIN_MESSAGE_MAP(MFCEdit, CMFCEditBrowseCtrl)
END_MESSAGE_MAP()


// MFCEdit ��Ϣ�������
void MFCEdit::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	long wl = GetWindowLong(this->m_hWnd, GWL_STYLE);   //���Edit Box�Ĵ��ڷ��
	SetWindowLong(this->m_hWnd, GWL_STYLE, wl | ((ES_CENTER|ES_RIGHT)&~ES_MULTILINE)); //����Edit Box�·��
	CMFCEditBrowseCtrl::PreSubclassWindow();
}
