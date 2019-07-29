// MFCEdit.cpp : 实现文件
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


// MFCEdit 消息处理程序
void MFCEdit::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	long wl = GetWindowLong(this->m_hWnd, GWL_STYLE);   //获得Edit Box的窗口风格
	SetWindowLong(this->m_hWnd, GWL_STYLE, wl | ((ES_CENTER|ES_RIGHT)&~ES_MULTILINE)); //设置Edit Box新风格
	CMFCEditBrowseCtrl::PreSubclassWindow();
}
