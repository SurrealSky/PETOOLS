
// PEMakeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEMake.h"
#include "PEMakeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPEMakeDlg �Ի���




CPEMakeDlg::CPEMakeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPEMakeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEMakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, tbFilePath);
	DDX_Control(pDX, IDC_EDIT1, mDisplay);
}

BEGIN_MESSAGE_MAP(CPEMakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CPEMakeDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_BUTTON1, &CPEMakeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPEMakeDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPEMakeDlg ��Ϣ�������

BOOL CPEMakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	tbFilePath.SetWindowTextA("D:\\calc.exe");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPEMakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPEMakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPEMakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//���ļ�
void CPEMakeDlg::OnBnClickedMfcbutton1()
{
	//��Ҫ�ȴ��̵߳ȴ����
	if(mPEMake.isAnalysised())
	{
		mPEMake.PEUnload();
	}
	CString m_Path;
	tbFilePath.GetWindowText(m_Path);
	if(m_Path.GetLength()==0)
	{
		::MessageBox(this->m_hWnd,"��ѡ��Ҫ�������ļ�","����",MB_OK);
		return;
	}
	//�����ļ�
	if(!mPEMake.PELoadFile(m_Path.GetBuffer(0),"r"))     //ֻ����ʽ���ļ�
	{
		::MessageBox(this->m_hWnd,"�ļ�����ʧ��","����",MB_OK);
		return;
	}

	if(!mPEMake.CheckPESig())
	{
		::MessageBox(this->m_hWnd,"PE�ļ�����","����",MB_OK);
		return;
	}

	if(mPEMake.Analysis())
	{
		mPEMake.SetAnalysised(true);
	}else
	{
		mPEMake.SetAnalysised(false);
		return;
	}
	mDisplay.SetWindowTextA("�������");
}

//����
void CPEMakeDlg::OnBnClickedButton1()
{
	bool bRet=mPEMake.Protect2A();
	if(bRet)
	{
		mPEMake.mPeCtx.path.append(".protect.exe");
		CFile mFile(mPEMake.mPeCtx.path.c_str(),CFile::modeCreate|CFile::modeReadWrite);
		mFile.Write(mPEMake.mPeCtx.pVirMem,mPEMake.mPeCtx.size);
		mFile.Close();
		mDisplay.SetWindowTextA("�����ɹ�");
	}else
		mDisplay.SetWindowTextA("����ʧ��");
}

//�˳�
void CPEMakeDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->OnOK();
}
