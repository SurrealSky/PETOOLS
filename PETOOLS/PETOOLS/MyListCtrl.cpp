// MyListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyListCtrl.h"
#include "DialogFirst.h"
#include "PETOOLSDlg.h"

// MyListCtrl


IMPLEMENT_DYNAMIC(MyListCtrl, CMFCListCtrl)

MyListCtrl::MyListCtrl()
{

}

MyListCtrl::~MyListCtrl()
{
}

BEGIN_MESSAGE_MAP(MyListCtrl, CMFCListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &MyListCtrl::OnLvnColumnclick)
	ON_NOTIFY_REFLECT(NM_CLICK, &MyListCtrl::OnNMClick)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &MyListCtrl::OnLvnItemchanged)
END_MESSAGE_MAP()

// MyListCtrl ��Ϣ�������

void MyListCtrl::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	LONG   lStyle; 
	lStyle=GetWindowLong(this->m_hWnd,GWL_STYLE);//��ȡ��ǰ�������� 
	lStyle   &=   ~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	lStyle|=(LVS_REPORT);   //������ʾ��ʽΪ����ʽ 
	SetWindowLong(this->m_hWnd,GWL_STYLE,lStyle);//���ô�������

	this->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	CMFCListCtrl::PreSubclassWindow();
}

void MyListCtrl::SetHeaders(TCHAR Array[][MAX_HEADLENGTH],int number)
{
	this->DeleteAllItems();
	CRect rect;
	this->GetWindowRect(&rect);
	for(int i=0;i<number;i++)
	{
		LVCOLUMN co;
		co.mask=LVCF_TEXT|LVCF_FMT|LVCF_WIDTH;
		co.fmt=LVCFMT_CENTER;
		co.cx=rect.Width()/number;
		co.pszText=Array[i];
		co.cchTextMax=sizeof(co.pszText);
		co.iSubItem=i;
		co.iOrder=i;
		this->InsertColumn(i,&co);
	}
}

int CALLBACK MyListCtrl::ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	DATA* pV=static_cast<DATA*>((PVOID)lParamSort); 
     
	int col=pV->m_nSortedCol;//���������ݸ�col,�����жϵ���˵ڼ���  
    //ȡ����ַ���  

	int nItem1,nItem2;
	LVFINDINFO FindInfo;
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=lParam1;
	nItem1=pV->Ctrl->FindItem(&FindInfo,-1);
	FindInfo.lParam=lParam2;
	nItem2=pV->Ctrl->FindItem(&FindInfo,-1);

	if((nItem1==-1)||(nItem2==-1))
	{
	   return 0;
	}
    CString strItem1, strItem2;
	strItem1=pV->Ctrl->GetItemText(lParam1,col);  
    strItem2=pV->Ctrl->GetItemText(lParam2,col);//���Ҫ�Ƚϵ��ַ�
    int iCompRes=0;
    switch(pV->m_nSortedCol) 
    { 
		case(1):
		case(2):
			{
				if(strItem1.CompareNoCase(strItem2)>0)
					iCompRes=1;
				else if(strItem1.CompareNoCase(strItem2)==0)
					iCompRes=0;
				else
					iCompRes=-1;
			}break;
		default: 
			{
				//Ĭ������
				if(StrToInt(strItem1)>StrToInt(strItem2))
					iCompRes=1;
				else if(StrToInt(strItem1)==StrToInt(strItem2))
					iCompRes=0;
				else
					iCompRes=-1;
			}
			break; 
    } 
    ////���ݵ�ǰ������ʽ���е��� 
    if(pV->m_fAsc) 
        return iCompRes; 
    else 
        return iCompRes*-1; 
}

void MyListCtrl::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);  
	DATA da={0};
	da.Ctrl=this;
	//��������ʽ
    if( pNMLV->iSubItem == da.m_nSortedCol ) 
        da.m_fAsc = !da.m_fAsc; 
    else 
    { 
        da.m_fAsc = TRUE; 
        da.m_nSortedCol = pNMLV->iSubItem; 
    } 

	int    i=this->GetItemCount();                //   �����亯���ǹؼ�Ŷ��������
    while(i--) this->SetItemData(i,i);   
    //���������� 
    this->SortItems( MyListCtrl::ListCompare,(DWORD_PTR)&da);
	*pResult = 0;
}

void MyListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	*pResult = 0;	
}

void MyListCtrl::Clear()
{
	this->DeleteAllItems();
	//ɾ���ؼ���ͷ
	int cols=this->GetHeaderCtrl().GetItemCount();
	for(int i=cols-1;i>=0;i--)
	{
		this->DeleteColumn(i);
	}
}

void MyListCtrl::SetStyle(DWORD style)
{

	LONG   lStyle; 
	lStyle=GetWindowLong(this->m_hWnd,GWL_STYLE);//��ȡ��ǰ��������  
	lStyle|=(style);
	SetWindowLong(this->m_hWnd,GWL_STYLE,lStyle);//���ô�������
	 
	//this->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
}

void MyListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	const char *name = this->GetParent()->GetRuntimeClass()->m_lpszClassName;
	if (strcmp(name, "DialogFirst") != 0)
	{
		*pResult = 0;
		return;
	}
	
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem == -1) return;
	int dwIndex = StrToInt(this->GetItemText(pNMItemActivate->iItem, 0)) - 1;
	//�ڼ���
	DialogFirst *dlg = static_cast<DialogFirst *>(this->GetParent());
	CPETOOLSDlg *pMainDlg = static_cast<CPETOOLSDlg*>(dlg->GetParent());
	switch (dlg->dwArgu)
	{
		case IMAGE_DIRECTORY_ENTRY_IMPORT:
		{
			if (this->GetDlgCtrlID() == dlg->m_List3.GetDlgCtrlID())  return;

			//���õڶ���ListCtrl����,����Ҫ���
			dlg->m_List3.DeleteAllItems();
			//�������
			for (int i = 0; i<pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[dwIndex].mThunksVector.size(); i++)
			{
				CString strFormat;
				strFormat.Format("%d", i + 1);
				dlg->m_List3.InsertItem(i, strFormat);

				//ThunkRVA
				strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[dwIndex].mThunksVector[i].ThunkRVA);
				dlg->m_List3.SetItemText(i, 1, strFormat);

				//ThunkFOA
				strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[dwIndex].mThunksVector[i].ThunkFOA);
				dlg->m_List3.SetItemText(i, 2, strFormat);

				//Thunkֵ
	#ifdef PE_MODEL
				strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[dwIndex].mThunksVector[i].AddrFunc);
	#else
				strFormat.Format("%16X", pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[dwIndex].mThunksVector[i].AddrFunc);
	#endif
				dlg->m_List3.SetItemText(i, 3, strFormat);

				//���
				strFormat.Format("%04X", pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[dwIndex].mThunksVector[i].Ordinal);
				dlg->m_List3.SetItemText(i, 4, strFormat);

				//API����
				if(pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[dwIndex].mThunksVector[i].strFuncName.length()<1)
					strFormat.Format("%XH", pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[dwIndex].mThunksVector[i].Ordinal);
				else
					strFormat.Format("%s", pMainDlg->mPEMake.mPeCtx.pe.mImportsVector[dwIndex].mThunksVector[i].strFuncName.c_str());
				dlg->m_List3.SetItemText(i, 5, strFormat);
			}
		}break;
		case IMAGE_DIRECTORY_ENTRY_BASERELOC:
		{
			if (this->GetDlgCtrlID() == dlg->m_List3.GetDlgCtrlID())  return;
			dlg->m_List3.DeleteAllItems();

			for (int i = 0; i<pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector[dwIndex].mSnVector.size(); i++)
			{
				CString strFormat;
				strFormat.Format("%d", i + 1);
				dlg->m_List3.InsertItem(i, strFormat);

				strFormat.Format("0x%08X", pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector[dwIndex].mBaseRelocation.VirtualAddress
					+ pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector[dwIndex].mSnVector[i].wValue);
				dlg->m_List3.SetItemText(i, 1, strFormat);

				strFormat.Format("0x%08X", pMainDlg->mPEMake.RvaToFoa(pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector[dwIndex].mBaseRelocation.VirtualAddress
					+ pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector[dwIndex].mSnVector[i].wValue));
				dlg->m_List3.SetItemText(i, 2, strFormat);

				strFormat.Format("0x%02X", pMainDlg->mPEMake.mPeCtx.pe.mRelocsVector[dwIndex].mSnVector[i].cType);
				dlg->m_List3.SetItemText(i, 3, strFormat);
			}
		}break;
		case IMAGE_DIRECTORY_ENTRY_RESOURCE:
		{
			if (this->GetDlgCtrlID() == dlg->m_List3.GetDlgCtrlID())  return;
			dlg->m_List3.DeleteAllItems();
			for (int i = 0; i<pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector.size(); i++)
			{
				CString strFormat;
				strFormat.Format("%d", i + 1);
				dlg->m_List3.InsertItem(i, strFormat);

				if (pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector[i].wId == 0)
				{
					_bstr_t t = pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector[i].wstrId.c_str();
					char* pchar = (char*)t;
					std::string strTemp = pchar;
					dlg->m_List3.SetItemText(i, 1, strTemp.c_str());
				}
				else
				{
					strFormat.Format("%d", pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector[i].wId);
					dlg->m_List3.SetItemText(i, 1, strFormat);
				}

				if (pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector[i].wLua == 0)
				{
					_bstr_t t = pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector[i].wstrLua.c_str();
					char* pchar = (char*)t;
					std::string strTemp = pchar;
					dlg->m_List3.SetItemText(i, 2, strTemp.c_str());
				}
				else
				{
					strFormat.Format("%d", pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector[i].wLua);
					dlg->m_List3.SetItemText(i, 2, strFormat);
				}

				strFormat.Format("0x%08X", pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector[i].mDataEntry.OffsetToData);
				dlg->m_List3.SetItemText(i, 3, strFormat);

				strFormat.Format("0x%08X", pMainDlg->mPEMake.RvaToFoa(pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector[i].mDataEntry.OffsetToData));
				dlg->m_List3.SetItemText(i, 4, strFormat);

				strFormat.Format("0x%X", pMainDlg->mPEMake.mPeCtx.pe.mResourcesVector[dwIndex].mEntryDatasVector[i].mDataEntry.Size);
				dlg->m_List3.SetItemText(i, 5, strFormat);
			}
		}break;
		case IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT:
		{
			if (this->GetDlgCtrlID() == dlg->m_List3.GetDlgCtrlID())  return;
			//���õڶ���ListCtrl����,����Ҫ���
			dlg->m_List3.DeleteAllItems();

			for (int i = 0; i<pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[dwIndex].mThunksVector.size(); i++)
			{
				CString strFormat;
				strFormat.Format("%d", i + 1);
				dlg->m_List3.InsertItem(i, strFormat);

				strFormat.Format("%s", pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[dwIndex].mThunksVector[i].strFuncName.c_str());
				dlg->m_List3.SetItemText(i, 1, strFormat);

				strFormat.Format("%d", pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[dwIndex].mThunksVector[i].Ordinal);
				dlg->m_List3.SetItemText(i, 2, strFormat);
	#ifdef PE_MODEL
				strFormat.Format("%08X", pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[dwIndex].mThunksVector[i].AddrFunc);
	#else
				strFormat.Format("%16X", pMainDlg->mPEMake.mPeCtx.pe.mDelaysVector[dwIndex].mThunksVector[i].AddrFunc);
	#endif
				dlg->m_List3.SetItemText(i, 3, strFormat);
			}
		}break;
	}

	*pResult = 0;
}
