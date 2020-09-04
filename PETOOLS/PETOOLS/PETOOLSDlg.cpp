
// PETOOLSDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETOOLS.h"
#include "PETOOLSDlg.h"
#include "afxdialogex.h"
#include"DisaDialog.h"
#include"ProBarThread.h"
#include"AddSectionDlg.h"
#include"AddPatch.h"
#include"EncryptDlg.h"
#include<LogLib\DebugLog.h>
#include<MiniDump.h>


//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


// CPETOOLSDlg �Ի���

CPETOOLSDlg *MainDlg;

CPETOOLSDlg::CPETOOLSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPETOOLSDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pFrameDlg = NULL;
	pPosCalcDlg = NULL;
}
CPETOOLSDlg::~CPETOOLSDlg()
{
	if (pFrameDlg != NULL) 
	{
		delete pFrameDlg;
		pFrameDlg = NULL;
	}
	if (pPosCalcDlg != NULL)
	{
		delete pPosCalcDlg;
		pPosCalcDlg = NULL;
	}
}

void CPETOOLSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_Edit1);
	DDX_Control(pDX, IDC_MFCBUTTON1, m_Button1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, m_Edit2);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_STATIC5, m_Static5);
	DDX_Control(pDX, IDC_STATIC6, m_Static6);
	DDX_Control(pDX, IDC_STATIC7, m_Static7);
	DDX_Control(pDX, IDC_STATIC8, m_Static8);
	DDX_Control(pDX, IDC_MFCEDITBROWSE3, m_Edit3);
	DDX_Control(pDX, IDC_MFCEDITBROWSE4, m_Edit4);
	DDX_Control(pDX, IDC_MFCBUTTON2, m_Button2);
	DDX_Control(pDX, IDC_COMBOBOXEX1, m_ComboBox1);
	DDX_Control(pDX, IDC_STATIC9, m_Static9);
	DDX_Control(pDX, IDC_STATIC10, m_Static10);
	DDX_Control(pDX, IDC_STATIC11, m_Static11);
	DDX_Control(pDX, IDC_STATIC12, m_Static12);
	DDX_Control(pDX, IDC_STATIC13, m_Static13);
	DDX_Control(pDX, IDC_STATIC14, m_Static14);
	DDX_Control(pDX, IDC_STATIC15, m_Static15);
	DDX_Control(pDX, IDC_STATIC16, m_Static16);
	DDX_Control(pDX, IDC_STATIC17, m_Static17);
	DDX_Control(pDX, IDC_STATIC18, m_Static18);
	DDX_Control(pDX, IDC_STATIC19, m_Static19);
	DDX_Control(pDX, IDC_STATIC20, m_Static20);
	DDX_Control(pDX, IDC_STATIC21, m_Static21);
	DDX_Control(pDX, IDC_STATIC22, m_Static22);
	DDX_Control(pDX, IDC_STATIC23, m_Static23);
	DDX_Control(pDX, IDC_STATIC24, m_Static24);
	DDX_Control(pDX, IDC_STATIC25, m_Static25);
	DDX_Control(pDX, IDC_STATIC26, m_Static26);
	DDX_Control(pDX, IDC_STATIC27, m_Static27);
	DDX_Control(pDX, IDC_STATIC28, m_Static28);
	DDX_Control(pDX, IDC_STATIC29, m_Static29);
	DDX_Control(pDX, IDC_STATIC30, m_Static30);
	DDX_Control(pDX, IDC_STATIC31, m_Static31);
	DDX_Control(pDX, IDC_STATIC32, m_Static32);
	DDX_Control(pDX, IDC_STATIC33, m_Static33);
	DDX_Control(pDX, IDC_STATIC34, m_Static34);
	DDX_Control(pDX, IDC_STATIC35, m_Static35);
	DDX_Control(pDX, IDC_STATIC36, m_Static36);
	DDX_Control(pDX, IDC_STATIC37, m_Static37);
	DDX_Control(pDX, IDC_STATIC38, m_Static38);
	DDX_Control(pDX, IDC_STATIC39, m_Static39);
	DDX_Control(pDX, IDC_STATIC40, m_Static40);
	DDX_Control(pDX, IDC_STATIC41, m_Static41);
	DDX_Control(pDX, IDC_STATIC42, m_Static42);
	DDX_Control(pDX, IDC_STATIC43, m_Static43);
	DDX_Control(pDX, IDC_STATIC44, m_Static44);
	DDX_Control(pDX, IDC_STATIC45, m_Static45);
	DDX_Control(pDX, IDC_STATIC46, m_Static46);
	DDX_Control(pDX, IDC_STATIC47, m_Static47);
	DDX_Control(pDX, IDC_STATIC48, m_Static48);
	DDX_Control(pDX, IDC_STATIC49, m_Static49);
	DDX_Control(pDX, IDC_STATIC50, m_Static50);
	DDX_Control(pDX, IDC_STATIC51, m_Static51);
	DDX_Control(pDX, IDC_STATIC52, m_Static52);
	DDX_Control(pDX, IDC_STATIC53, m_Static53);
	DDX_Control(pDX, IDC_STATIC54, m_Static54);
	DDX_Control(pDX, IDC_STATIC55, m_Static55);
	DDX_Control(pDX, IDC_STATIC56, m_Static56);
	DDX_Control(pDX, IDC_MFCEDITBROWSE5, m_Edit5);
	DDX_Control(pDX, IDC_MFCEDITBROWSE6, m_Edit6);
	DDX_Control(pDX, IDC_MFCEDITBROWSE7, m_Edit7);
	DDX_Control(pDX, IDC_MFCEDITBROWSE8, m_Edit8);
	DDX_Control(pDX, IDC_MFCEDITBROWSE9, m_Edit9);
	DDX_Control(pDX, IDC_MFCEDITBROWSE10, m_Edit10);
	DDX_Control(pDX, IDC_MFCEDITBROWSE11, m_Edit11);
	DDX_Control(pDX, IDC_MFCEDITBROWSE12, m_Edit12);
	DDX_Control(pDX, IDC_MFCEDITBROWSE13, m_Edit13);
	DDX_Control(pDX, IDC_MFCEDITBROWSE14, m_Edit14);
	DDX_Control(pDX, IDC_MFCEDITBROWSE15, m_Edit15);
	DDX_Control(pDX, IDC_MFCEDITBROWSE16, m_Edit16);
	DDX_Control(pDX, IDC_MFCEDITBROWSE17, m_Edit17);
	DDX_Control(pDX, IDC_MFCEDITBROWSE18, m_Edit18);
	DDX_Control(pDX, IDC_MFCEDITBROWSE19, m_Edit19);
	DDX_Control(pDX, IDC_MFCEDITBROWSE20, m_Edit20);
	DDX_Control(pDX, IDC_MFCEDITBROWSE21, m_Edit21);
	DDX_Control(pDX, IDC_MFCEDITBROWSE22, m_Edit22);
	DDX_Control(pDX, IDC_MFCEDITBROWSE23, m_Edit23);
	DDX_Control(pDX, IDC_MFCEDITBROWSE24, m_Edit24);
	DDX_Control(pDX, IDC_MFCEDITBROWSE25, m_Edit25);
	DDX_Control(pDX, IDC_MFCEDITBROWSE26, m_Edit26);
	DDX_Control(pDX, IDC_MFCEDITBROWSE27, m_Edit27);
	DDX_Control(pDX, IDC_MFCEDITBROWSE28, m_Edit28);
	DDX_Control(pDX, IDC_MFCEDITBROWSE29, m_Edit29);
	DDX_Control(pDX, IDC_MFCEDITBROWSE30, m_Edit30);
	DDX_Control(pDX, IDC_MFCEDITBROWSE31, m_Edit31);
	DDX_Control(pDX, IDC_MFCEDITBROWSE32, m_Edit32);
	DDX_Control(pDX, IDC_MFCEDITBROWSE33, m_Edit33);
	DDX_Control(pDX, IDC_MFCEDITBROWSE34, m_Edit34);
	DDX_Control(pDX, IDC_MFCEDITBROWSE35, m_Edit35);
	DDX_Control(pDX, IDC_MFCEDITBROWSE36, m_Edit36);
	DDX_Control(pDX, IDC_MFCEDITBROWSE37, m_Edit37);
	DDX_Control(pDX, IDC_MFCEDITBROWSE38, m_Edit38);
	DDX_Control(pDX, IDC_MFCEDITBROWSE39, m_Edit39);
	DDX_Control(pDX, IDC_MFCEDITBROWSE40, m_Edit40);
	DDX_Control(pDX, IDC_MFCEDITBROWSE41, m_Edit41);
	DDX_Control(pDX, IDC_MFCEDITBROWSE42, m_Edit42);
	DDX_Control(pDX, IDC_MFCEDITBROWSE43, m_Edit43);
	DDX_Control(pDX, IDC_MFCEDITBROWSE44, m_Edit44);
	DDX_Control(pDX, IDC_MFCEDITBROWSE45, m_Edit45);
	DDX_Control(pDX, IDC_MFCEDITBROWSE46, m_Edit46);
	DDX_Control(pDX, IDC_MFCEDITBROWSE47, m_Edit47);
	DDX_Control(pDX, IDC_MFCEDITBROWSE48, m_Edit48);
	DDX_Control(pDX, IDC_MFCEDITBROWSE49, m_Edit49);
	DDX_Control(pDX, IDC_MFCEDITBROWSE50, m_Edit50);
	DDX_Control(pDX, IDC_MFCEDITBROWSE51, m_Edit51);
	DDX_Control(pDX, IDC_MFCBUTTON3, m_Button3);
	DDX_Control(pDX, IDC_MFCBUTTON4, m_Button4);
	DDX_Control(pDX, IDC_COMBOBOXEX2, m_ComboBox2);
}

BEGIN_MESSAGE_MAP(CPETOOLSDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CPETOOLSDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CPETOOLSDlg::OnBnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CPETOOLSDlg::OnBnClickedMfcbutton4)
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX1, &CPETOOLSDlg::OnCbnSelchangeComboboxex1)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX2, &CPETOOLSDlg::OnCbnSelchangeComboboxex2)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CPETOOLSDlg::OnBnClickedMfcbutton2)
	ON_COMMAND(ID_32771, &CPETOOLSDlg::OnOpen)
	ON_COMMAND(ID_Disa, &CPETOOLSDlg::OnDisa)
	ON_COMMAND(ID_RESET, &CPETOOLSDlg::OnReset)
	ON_COMMAND(ID_32778, &CPETOOLSDlg::OnClsRelocData)
	ON_COMMAND(ID_32779, &CPETOOLSDlg::OnEncryptImportTable)
	ON_COMMAND(ID_32780, &CPETOOLSDlg::OnTest)
	ON_MESSAGE(WM_UPDATEUI, &CPETOOLSDlg::OnUpdateUi)
	ON_COMMAND(ID_32781, &CPETOOLSDlg::OnSaveFile)
	ON_COMMAND(ID_32782, &CPETOOLSDlg::OnSaveAs)
	ON_COMMAND(ID_32783, &CPETOOLSDlg::OnAddPatch)
	ON_COMMAND(ID_Menu32784, &CPETOOLSDlg::OnAddSection)
	ON_COMMAND(ID_32785, &CPETOOLSDlg::OnEncrypt)
	ON_COMMAND(ID_32786, &CPETOOLSDlg::OnPosCalc)
	ON_COMMAND(ID_32787, &CPETOOLSDlg::OnHexEditView)
END_MESSAGE_MAP()


// CPETOOLSDlg ��Ϣ�������

BOOL CPETOOLSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//���ñ��������ַ���
	setlocale(LC_ALL,"chs");
	//��ʼ��ȫ�ֱ���
	::MainDlg=this;
	//��װ�쳣��
	if(!this->SetDumpFunc())
	{
		//���öԻ�����־
		DebugLog("Dump�߳�����ʧ��");
		return FALSE;
	}

	DebugLog("Dump�߳��������");
	
	if(!this->SetDlgUI())
	{
		//���öԻ�����־
		DebugLog("UI���ô���ʧ��");
		return FALSE;
	}
	DebugLog("���Ի���UI�������");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPETOOLSDlg::OnPaint()
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
HCURSOR CPETOOLSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�����������Ի����UI
BOOL CPETOOLSDlg::SetDlgUI(void)
{
	//��ʼ��MainFrame UI����
	int x=0,y=0,height=0,width=0;
	TCHAR TextDisplay[MAX_PATH]={0};
	height=mIni.GetIntKey("configure.ini","MainFrame","height");
	width=mIni.GetIntKey("configure.ini","MainFrame","width");
	RECT rect={0};
	this->GetWindowRect(&rect);
	this->MoveWindow(rect.left,rect.top,width,height,TRUE);

	//��ʼ������ؼ�UI
	this->SetControlUI("configure.ini",&this->m_Static1,"Static1");
	this->SetControlUI("configure.ini",&this->m_Static2,"Static2");
	this->SetControlUI("configure.ini",&this->m_Static3,"Static3");
	this->SetControlUI("configure.ini",&this->m_Static4,"Static4");
	this->SetControlUI("configure.ini",&this->m_Static5,"Static5");
	this->SetControlUI("configure.ini",&this->m_Static6,"Static6");
	this->SetControlUI("configure.ini",&this->m_Static7,"Static7");
	this->SetControlUI("configure.ini",&this->m_Static8,"Static8");
	this->SetControlUI("configure.ini",&this->m_Static9,"Static9");
	this->SetControlUI("configure.ini",&this->m_Static10,"Static10");
	this->SetControlUI("configure.ini",&this->m_Static11,"Static11");
	this->SetControlUI("configure.ini",&this->m_Static12,"Static12");
	this->SetControlUI("configure.ini",&this->m_Static13,"Static13");
	this->SetControlUI("configure.ini",&this->m_Static14,"Static14");
	this->SetControlUI("configure.ini",&this->m_Static15,"Static15");
	this->SetControlUI("configure.ini",&this->m_Static16,"Static16");
	this->SetControlUI("configure.ini",&this->m_Static17,"Static17");
	this->SetControlUI("configure.ini",&this->m_Static18,"Static18");
	this->SetControlUI("configure.ini",&this->m_Static19,"Static19");
	this->SetControlUI("configure.ini",&this->m_Static20,"Static20");
	this->SetControlUI("configure.ini",&this->m_Static21,"Static21");
	this->SetControlUI("configure.ini",&this->m_Static22,"Static22");
	this->SetControlUI("configure.ini",&this->m_Static23,"Static23");
	this->SetControlUI("configure.ini",&this->m_Static24,"Static24");
	this->SetControlUI("configure.ini",&this->m_Static25,"Static25");
	this->SetControlUI("configure.ini",&this->m_Static26,"Static26");
	this->SetControlUI("configure.ini",&this->m_Static27,"Static27");
	this->SetControlUI("configure.ini",&this->m_Static28,"Static28");
	this->SetControlUI("configure.ini",&this->m_Static29,"Static29");
	this->SetControlUI("configure.ini",&this->m_Static30,"Static30");
	this->SetControlUI("configure.ini",&this->m_Static31,"Static31");
	this->SetControlUI("configure.ini",&this->m_Static32,"Static32");
	this->SetControlUI("configure.ini",&this->m_Static33,"Static33");
	this->SetControlUI("configure.ini",&this->m_Static34,"Static34");
	this->SetControlUI("configure.ini",&this->m_Static35,"Static35");
	this->SetControlUI("configure.ini",&this->m_Static36,"Static36");
	this->SetControlUI("configure.ini",&this->m_Static37,"Static37",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static38,"Static38",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static39,"Static39",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static40,"Static40",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static41,"Static41",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static42,"Static42",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static43,"Static43",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static44,"Static44",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static45,"Static45",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static46,"Static46",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static47,"Static47");
	this->SetControlUI("configure.ini",&this->m_Static48,"Static48");
	this->SetControlUI("configure.ini",&this->m_Static49,"Static49");
	this->SetControlUI("configure.ini",&this->m_Static50,"Static50");
	this->SetControlUI("configure.ini",&this->m_Static51,"Static51");
	this->SetControlUI("configure.ini",&this->m_Static52,"Static52");
	this->SetControlUI("configure.ini",&this->m_Static53,"Static53",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static54,"Static54",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static55,"Static55",FALSE);
	this->SetControlUI("configure.ini",&this->m_Static56,"Static56",FALSE);

	this->SetControlUI("configure.ini",&this->m_Edit1,"Edit1",TRUE);
	this->m_Edit1.SetWindowText("D:\\calc.exe");

	this->SetControlUI("configure.ini",&this->m_Edit2,"Edit2",FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit3,"Edit3",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit4,"Edit4",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit5,"Edit5",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit6,"Edit6",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit7,"Edit7",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit8,"Edit8",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit9,"Edit9",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit10,"Edit10",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit11,"Edit11",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit12,"Edit12",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit13,"Edit13",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit14,"Edit14",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit15,"Edit15",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit16,"Edit16",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit17,"Edit17",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit18,"Edit18",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit19,"Edit19",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit20,"Edit20",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit21,"Edit21",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit22,"Edit22",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit23,"Edit23",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit24,"Edit24",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit25,"Edit25",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit26,"Edit26",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit27,"Edit27",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit28,"Edit28",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit29,"Edit29",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit30,"Edit30",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit31,"Edit31",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit32,"Edit32",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit33,"Edit33",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit34,"Edit34",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit35,"Edit35",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit36,"Edit36",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit37,"Edit37",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit38,"Edit38",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit39,"Edit39",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit40,"Edit40",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit41,"Edit41",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit42,"Edit42",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit43,"Edit43",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit44,"Edit44",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit45,"Edit45",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit46,"Edit46",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit47,"Edit47",TRUE);
	this->SetControlUI("configure.ini",&this->m_Edit48,"Edit48",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit49,"Edit49",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit50,"Edit50",TRUE,FALSE);
	this->SetControlUI("configure.ini",&this->m_Edit51,"Edit51",TRUE,FALSE);

	this->SetControlUI("configure.ini",&this->m_Button1,"Button1");
	this->SetControlUI("configure.ini",&this->m_Button2,"Button2");
	this->SetControlUI("configure.ini",&this->m_Button3,"Button3>>");
	this->SetControlUI("configure.ini",&this->m_Button4,"Button4>>");

	this->SetControlUI("configure.ini",&this->m_ComboBox1,"ComboBox1");
	this->SetControlUI("configure.ini",&this->m_ComboBox2,"ComboBox2");
	//����״̬��
	this->m_Status.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM,CRect(0,0,0,0), this, IDC_STATUSBARCTRL);
	this->m_Status.SetUI();

	return TRUE;
}

//��������Dump�߳�
BOOL CPETOOLSDlg::SetDumpFunc(void)
{
	CMiniDump::EnableAutoDump(true);
	return TRUE;
}

//������ť�¼��������
void CPETOOLSDlg::OnBnClickedMfcbutton1()
{
	//��ս���
	this->Reset();
	
	//����������
	//CProBarThread pProBarThread;
	//pProBarThread.Create();

	//pProBarThread.SetProValue(0);

	//��Ҫ�ȴ��̵߳ȴ����
	if(mPEMake.isAnalysised())
	{
		mPEMake.PEUnload();
	}

	CString m_Path;
	this->m_Edit1.GetWindowText(m_Path);
	if(m_Path.GetLength()==0)
	{
		::MessageBox(this->m_hWnd,"��ѡ��Ҫ�������ļ�","����",MB_OK);
		return;
	}
	//pProBarThread.SetProValue(20);

	//�����ļ�
	if(!mPEMake.PELoadFile(m_Path.GetBuffer(0),"r"))     //ֻ����ʽ���ļ�
	{
		DebugLog("PeStruct��ʼ��ʧ��!");
		return;
	}

	//��ʼ����
	DebugLog("��ʼ����PE�ļ�");

	if(!mPEMake.CheckPESig())
	{
		DebugLog("PE�ļ�����");
		return;
	}

	if(mPEMake.Analysis())
	{
		DebugLog("PE�ļ��������");
		mPEMake.SetAnalysised(true);
	}else
	{
		DebugLog("PE����ʧ��");
		return;
	} 

	//pProBarThread.SetProValue(50);
	DebugLog("��ʼ���öԻ���ؼ���ֵ");

	if(this->SetCtrlContent())
	{
		DebugLog("�Ի���ֵ�������");
	}else
	{
		DebugLog("�Ի���ֵ����ʧ��");
		return;
	}
	//pProBarThread.SetProValue(100);

}

void CPETOOLSDlg::SetControlUI(TCHAR pFile[],MFCStatic *m_Static,TCHAR *m_tag,BOOL isVisible)
{
	int x=0,y=0,height=0,width=0;
	TCHAR TextDisplay[MAX_PATH]={0};
	x=mIni.GetIntKey(pFile,m_tag,"x");
	y=mIni.GetIntKey(pFile,m_tag,"y");
	height=mIni.GetIntKey(pFile,m_tag,"height");
	width=mIni.GetIntKey(pFile,m_tag,"width");
	m_Static->MoveWindow(x,y,width,height,TRUE);
	ZeroMemory(TextDisplay,sizeof(TextDisplay));
	mIni.GetStrKey(pFile,m_tag,"text",TextDisplay);
	m_Static->SetWindowText(TextDisplay);
	ZeroMemory(TextDisplay,sizeof(TextDisplay));
	mIni.GetStrKey(pFile,m_tag,"title",TextDisplay);
	memcpy_s(m_Static->Title,sizeof(m_Static->Title),TextDisplay,sizeof(TextDisplay));
	isVisible?m_Static->ShowWindow(SW_SHOW):m_Static->ShowWindow(SW_HIDE);
}

void CPETOOLSDlg::SetControlUI(TCHAR pFile[],MFCEdit *m_Edit,TCHAR *m_tag,BOOL isEnable,BOOL isVisible)
{
	int x=0,y=0,height=0,width=0;
	x=mIni.GetIntKey(pFile,m_tag,"x");
	y=mIni.GetIntKey(pFile,m_tag,"y");
	height=mIni.GetIntKey(pFile,m_tag,"height");
	width=mIni.GetIntKey(pFile,m_tag,"width");
	m_Edit->MoveWindow(x,y,width,height,TRUE);
	isEnable?m_Edit->EnableWindow(TRUE):m_Edit->EnableWindow(FALSE);
	isVisible?m_Edit->ShowWindow(SW_SHOW):m_Edit->ShowWindow(SW_HIDE);
}

void CPETOOLSDlg::SetControlUI(TCHAR pFile[],CMFCButton *m_Button,TCHAR *m_tag)
{
	int x=0,y=0,height=0,width=0;
	TCHAR TextDisplay[MAX_PATH]={0};
	x=mIni.GetIntKey(pFile,m_tag,"x");
	y=mIni.GetIntKey(pFile,m_tag,"y");
	height=mIni.GetIntKey(pFile,m_tag,"height");
	width=mIni.GetIntKey(pFile,m_tag,"width");
	m_Button->MoveWindow(x,y,width,height,TRUE);
	ZeroMemory(TextDisplay,sizeof(TextDisplay));
	mIni.GetStrKey(pFile,m_tag,"text",TextDisplay);
	m_Button->SetWindowText(TextDisplay);
}

void CPETOOLSDlg::SetControlUI(TCHAR pFile[],CWnd *m_Ctrl,TCHAR *m_tag,BOOL isVisible)
{
	int x=0,y=0,height=0,width=0;
	x=mIni.GetIntKey(pFile,m_tag,"x");
	y=mIni.GetIntKey(pFile,m_tag,"y");
	height=mIni.GetIntKey(pFile,m_tag,"height");
	width=mIni.GetIntKey(pFile,m_tag,"width");
	m_Ctrl->MoveWindow(x,y,width,height,TRUE);
	isVisible?m_Ctrl->ShowWindow(SW_SHOW):m_Ctrl->ShowWindow(SW_HIDE);
}

//�����л�
void CPETOOLSDlg::OnBnClickedMfcbutton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR Buffer[20]={0};
	this->m_Button3.GetWindowText(Buffer,sizeof(Buffer));
	if(_tcscmp(Buffer,"�л�>>")==0)
	{
		this->m_Button3.SetWindowText("�л�<<");
		for(int i=this->m_Static17.GetDlgCtrlID(),j=this->m_Edit12.GetDlgCtrlID();i<=this->m_Static36.GetDlgCtrlID();i++,j++)
		{
			MFCStatic *m_Static=static_cast<MFCStatic *>(this->GetDlgItem(i));
			m_Static->ShowWindow(SW_HIDE);
			MFCEdit *m_Edit=static_cast<MFCEdit *>(this->GetDlgItem(j));
			m_Edit->ShowWindow(SW_HIDE);
		}
		for(int i=this->m_Static37.GetDlgCtrlID(),j=this->m_Edit32.GetDlgCtrlID();i<=this->m_Static46.GetDlgCtrlID();i++,j++)
		{
			MFCStatic *m_Static=static_cast<MFCStatic *>(this->GetDlgItem(i));
			m_Static->ShowWindow(SW_SHOW);
			MFCEdit *m_Edit=static_cast<MFCEdit *>(this->GetDlgItem(j));
			m_Edit->ShowWindow(SW_SHOW);
		}
	}else
	{
		this->m_Button3.SetWindowText("�л�>>");

		for(int i=this->m_Static17.GetDlgCtrlID(),j=this->m_Edit12.GetDlgCtrlID();i<=this->m_Static36.GetDlgCtrlID();i++,j++)
		{
			MFCStatic *m_Static=static_cast<MFCStatic *>(this->GetDlgItem(i));
			m_Static->ShowWindow(SW_SHOW);
			MFCEdit *m_Edit=static_cast<MFCEdit *>(this->GetDlgItem(j));
			m_Edit->ShowWindow(SW_SHOW);
		}
		for(int i=this->m_Static37.GetDlgCtrlID(),j=this->m_Edit32.GetDlgCtrlID();i<=this->m_Static46.GetDlgCtrlID();i++,j++)
		{
			MFCStatic *m_Static=static_cast<MFCStatic *>(this->GetDlgItem(i));
			m_Static->ShowWindow(SW_HIDE);
			MFCEdit *m_Edit=static_cast<MFCEdit *>(this->GetDlgItem(j));
			m_Edit->ShowWindow(SW_HIDE);
		}
	}
}

//�����л�
void CPETOOLSDlg::OnBnClickedMfcbutton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR Buffer[20]={0};
	this->m_Button4.GetWindowText(Buffer,sizeof(Buffer));
	if(_tcscmp(Buffer,"�л�>>")==0)
	{
		this->m_Button4.SetWindowText("�л�<<");
		for(int i=this->m_Static47.GetDlgCtrlID(),j=this->m_Edit42.GetDlgCtrlID();i<=this->m_Static52.GetDlgCtrlID();i++,j++)
		{
			MFCStatic *m_Static=static_cast<MFCStatic *>(this->GetDlgItem(i));
			m_Static->ShowWindow(SW_HIDE);
			MFCEdit *m_Edit=static_cast<MFCEdit *>(this->GetDlgItem(j));
			m_Edit->ShowWindow(SW_HIDE);
		}
		for(int i=this->m_Static53.GetDlgCtrlID(),j=this->m_Edit48.GetDlgCtrlID();i<=this->m_Static56.GetDlgCtrlID();i++,j++)
		{
			MFCStatic *m_Static=static_cast<MFCStatic *>(this->GetDlgItem(i));
			m_Static->ShowWindow(SW_SHOW);
			MFCEdit *m_Edit=static_cast<MFCEdit *>(this->GetDlgItem(j));
			m_Edit->ShowWindow(SW_SHOW);
		}
	}else
	{
		this->m_Button4.SetWindowText("�л�>>");

		for(int i=this->m_Static47.GetDlgCtrlID(),j=this->m_Edit42.GetDlgCtrlID();i<=this->m_Static52.GetDlgCtrlID();i++,j++)
		{
			MFCStatic *m_Static=static_cast<MFCStatic *>(this->GetDlgItem(i));
			m_Static->ShowWindow(SW_SHOW);
			MFCEdit *m_Edit=static_cast<MFCEdit *>(this->GetDlgItem(j));
			m_Edit->ShowWindow(SW_SHOW);
		}
		for(int i=this->m_Static53.GetDlgCtrlID(),j=this->m_Edit48.GetDlgCtrlID();i<=this->m_Static56.GetDlgCtrlID();i++,j++)
		{
			MFCStatic *m_Static=static_cast<MFCStatic *>(this->GetDlgItem(i));
			m_Static->ShowWindow(SW_HIDE);
			MFCEdit *m_Edit=static_cast<MFCEdit *>(this->GetDlgItem(j));
			m_Edit->ShowWindow(SW_HIDE);
		}
	}
}

BOOL CPETOOLSDlg::SetCtrlContent()
{
	
	CString strFormat;
	strFormat.Format("0X%X",mPEMake.mPeCtx.pe.mDosHeader.e_lfanew);
	m_Edit2.SetWindowText(strFormat);

	strFormat.Format("0X%04X", mPEMake.mPeCtx.pe.mNtHeader.FileHeader.Machine);
	m_Edit5.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.FileHeader.NumberOfSections);
	m_Edit6.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.FileHeader.TimeDateStamp);
	m_Edit7.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.FileHeader.PointerToSymbolTable);
	m_Edit8.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.FileHeader.NumberOfSymbols);
	m_Edit9.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.FileHeader.SizeOfOptionalHeader);
	m_Edit10.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.FileHeader.Characteristics);
	m_Edit11.SetWindowText(strFormat);

	strFormat.Format("0X%04X", mPEMake.mPeCtx.pe.wMagic);
	m_Edit12.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.MajorLinkerVersion);
	m_Edit13.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.MinorLinkerVersion);
	m_Edit14.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfCode);
	m_Edit15.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfInitializedData);
	m_Edit16.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfUninitializedData);
	m_Edit17.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.AddressOfEntryPoint);
	m_Edit18.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.BaseOfCode);
	m_Edit19.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.BaseOfData);
	m_Edit20.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.ImageBase);
	m_Edit21.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SectionAlignment);
	m_Edit22.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.FileAlignment);
	m_Edit23.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.MajorOperatingSystemVersion);
	m_Edit24.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.MinorOperatingSystemVersion);
	m_Edit25.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.MajorImageVersion);
	m_Edit26.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.MinorImageVersion);
	m_Edit27.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.MajorSubsystemVersion);
	m_Edit28.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.MinorSubsystemVersion);
	m_Edit29.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.Win32VersionValue);
	m_Edit30.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfImage);
	m_Edit31.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfHeaders);
	m_Edit32.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.CheckSum);
	m_Edit33.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.Subsystem);
	m_Edit34.SetWindowText(strFormat);

	strFormat.Format("0X%04X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DllCharacteristics);
	m_Edit35.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfStackReserve);
	m_Edit36.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfStackCommit);
	m_Edit37.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfHeapReserve);
	m_Edit38.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.SizeOfStackCommit);
	m_Edit39.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.LoaderFlags);
	m_Edit40.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.NumberOfRvaAndSizes);
	m_Edit41.SetWindowText(strFormat);

	//��������Ŀ¼��Ŀ
	m_ComboBox1.ResetContent();
	for(int i=0;i<IMAGE_NUMBEROF_DIRECTORY_ENTRIES;i++)
	{
		COMBOBOXEXITEM item;
		item.mask = CBEIF_TEXT;
		item.iItem = i;
		switch (i)
		{
		case 0:
			item.pszText = "������"; break;
		case 1:
			item.pszText = "�����"; break;
		case 2:
			item.pszText = "��Դ��"; break;
		case 3:
			item.pszText = "�쳣��"; break;
		case 4:
			item.pszText = "��ȫ"; break;
		case 5:
			item.pszText = "�ض�λ��"; break;
		case 6:
			item.pszText = "����"; break;
		case 7:
			item.pszText = "��Ȩ"; break;
		case 8:
			item.pszText = "ȫ��ָ��"; break;
		case 9:
			item.pszText = "TLS��"; break;
		case 10:
			item.pszText = "��������"; break;
		case 11:
			item.pszText = "�󶨵����"; break;
		case 12:
			item.pszText = "IAT"; break;
		case 13:
			item.pszText = "�ӳٵ����"; break;
		case 14:
			item.pszText = "CLR����ʱ"; break;
		case 15:
			item.pszText = "ϵͳ����"; break;
		}
		this->m_ComboBox1.InsertItem(&item);
	}
	m_ComboBox1.SetCurSel(0);
	OnCbnSelchangeComboboxex1();
	//�������οؼ�����
	this->m_ComboBox2.ResetContent();
	for(int i=0;i<mPEMake.mPeCtx.pe.mNtHeader.FileHeader.NumberOfSections;i++)
	{
		COMBOBOXEXITEM item;
		item.mask = CBEIF_TEXT;
		item.iItem = i;
		strFormat.Format("SECTION HEADER #%d",i+1);
		item.pszText=strFormat.GetBuffer(0);
		m_ComboBox2.InsertItem(&item);
	}
	m_ComboBox2.SetCurSel(0);
	OnCbnSelchangeComboboxex2();
	
	return TRUE;
}

void CPETOOLSDlg::OnCbnSelchangeComboboxex1()
{
	
	int dwIndex=m_ComboBox1.GetCurSel();
	CString strFormat;
	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[dwIndex].VirtualAddress);
	m_Edit3.SetWindowText(strFormat);
	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[dwIndex].Size);
	m_Edit4.SetWindowText(strFormat);
	
}

void CPETOOLSDlg::OnCbnSelchangeComboboxex2()
{
	
	// ��ʼ����������Ϣ��ṹ
	int dwIndex=m_ComboBox2.GetCurSel();

	CString strFormat;
	strFormat.Format("%s", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].Name);
	m_Edit42.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].Misc.VirtualSize);
	this->m_Edit43.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].VirtualAddress);
	this->m_Edit44.SetWindowText(strFormat);

	strFormat.Format("0X%X", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].SizeOfRawData);
	this->m_Edit45.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].PointerToRawData);
	this->m_Edit46.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].PointerToRelocations);
	this->m_Edit47.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].PointerToLinenumbers);
	this->m_Edit48.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].NumberOfRelocations);
	this->m_Edit49.SetWindowText(strFormat);

	strFormat.Format("%d", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].NumberOfLinenumbers);
	this->m_Edit50.SetWindowText(strFormat);

	strFormat.Format("0X%08X", mPEMake.mPeCtx.pe.mSectionsVector[dwIndex].Characteristics);
	this->m_Edit51.SetWindowText(strFormat);
	
}

void CPETOOLSDlg::Reset()
{
	//�����еĿؼ����ݺ�״̬��ԭ
	EnumChildWindows(this->m_hWnd,CPETOOLSDlg::EnumChildProc,(LPARAM)this);
	//mPEMakeж��
	mPEMake.PEUnload();
}

//������Ŀ¼
void CPETOOLSDlg::OnBnClickedMfcbutton2()
{
	if(!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	int dwIndex=m_ComboBox1.GetCurSel();
	DWORD m_Size= mPEMake.mPeCtx.pe.mNtHeader.OptionalHeader.DataDirectory[dwIndex].Size;
	if(m_Size==0) 
	{
		AfxMessageBox("N/A");
		return;
	}
	if (pFrameDlg == NULL)
	{
		pFrameDlg = new DialogFirst(this);
		pFrameDlg->Create(IDD_DIALOG1, this);
	}
	pFrameDlg->Init(dwIndex);
	pFrameDlg->ShowWindow(SW_SHOW);

	//ģ̬��ʾ
	//DialogFirst mFrameDlg(this);
	//mFrameDlg.SetArgu(dwIndex);
	//mFrameDlg.DoModal();
	
}

BOOL CALLBACK CPETOOLSDlg::EnumChildProc(HWND hwnd,LPARAM lParam)
{
	CPETOOLSDlg *MainDlg=static_cast<CPETOOLSDlg *>((PVOID)lParam);
	CWnd *Wnd=MainDlg->GetDlgItem(::GetDlgCtrlID(hwnd));
	if(Wnd==NULL) return TRUE;
	if(Wnd->GetRuntimeClass()==RUNTIME_CLASS(MFCEdit))
	{
		if(::GetDlgCtrlID(hwnd)!=MainDlg->m_Edit1.GetDlgCtrlID())
		{
			Wnd->SetWindowText("");
		}
	}else if(Wnd->GetRuntimeClass()==RUNTIME_CLASS(CComboBoxEx))
	{
		CComboBoxEx *cbo=static_cast<CComboBoxEx *>(Wnd);
		cbo->ResetContent();
	}
	return TRUE;
}

//�˵�-��
void CPETOOLSDlg::OnOpen()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���  
	if(dlg.DoModal()==IDOK)  
		this->m_Edit1.SetWindowText(dlg.GetPathName());
}
//�˵�-�����
void CPETOOLSDlg::OnDisa()
{
	
	if(!this->mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	CDisaDialog DDia(this);
	DDia.DoModal();
	
}
//�˵�-����
void CPETOOLSDlg::OnReset()
{
	
	mPEMake.PEUnload();
	//�����еĿؼ����ݺ�״̬��ԭ
	EnumChildWindows(this->m_hWnd,CPETOOLSDlg::EnumChildProc,(LPARAM)this);
	
}

//�˵�-����-ȥ�ض�λ��
void CPETOOLSDlg::OnClsRelocData()
{
	
	 //TODO: �ڴ���������������
	if(!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	if(mPEMake.mPeCtx.pe.mRelocsVector.size()==0)
	{
		AfxMessageBox("���ض�λ��");
		return;
	}

	if(mPEMake.ClsRelocDataDirectory())
	{
		OnSaveAs();
	}

	DebugLog("�˵�-����-ȥ�ض�λ��:ȥ���ɹ�!");
	//���½���
	this->SendMessage(WM_UPDATEUI,NULL,NULL);
	MessageBox("�ض�λ��ȥ���ɹ�!");

	//���ַ����׶ˣ����ΪDLL�����޷����ص�ȱʡ��ַ��������޷������ض�λ����
	//���õķ����ǶԴ������ض�λ��������±�����㣬�ο���Windows PE��P182��
	
}

//�˵�-����-���������
void CPETOOLSDlg::OnEncryptImportTable()
{
	// TODO: �ڴ���������������

	if (!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	if (mPEMake.mPeCtx.pe.mImportsVector.size() == 0)
	{
		AfxMessageBox("�޵����");
		return;
	}

	mPEMake.EncryptImportTable();
	DebugLog("�˵�-����-��������:���ܳɹ�!");
	//���½���
	this->SendMessage(WM_UPDATEUI,NULL,NULL);
	MessageBox("�������ܳɹ�!");
}

//�˵�-����-����
void CPETOOLSDlg::OnTest()
{
	 //TODO: �ڴ���������������
	if(!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
}


afx_msg LRESULT CPETOOLSDlg::OnUpdateUi(WPARAM wParam, LPARAM lParam)
{
	//��տؼ�����
	EnumChildWindows(this->m_hWnd,CPETOOLSDlg::EnumChildProc,(LPARAM)this);
	//��������
	if(this->SetCtrlContent())
	{
		DebugLog("�Ի���ֵ�������");
	}else
	{
		DebugLog("�Ի���ֵ����ʧ��");
	}
	return 0;
}

//�����ļ�
void CPETOOLSDlg::OnSaveFile()
{
	if(!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	// TODO: �ڴ���������������
	if(IDYES==MessageBox("�Ƿ񱣴��ļ�","����",MB_YESNO|MB_ICONQUESTION))
	{
		CFile mFile(mPEMake.mPeCtx.path.c_str(),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		mFile.SetLength(0);
		mFile.Write(mPEMake.mPeCtx.pVirMem, mPEMake.mPeCtx.size);
		mFile.Close();
	}
}

//���Ϊ
void CPETOOLSDlg::OnSaveAs()
{
	if(!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	CFileDialog dlg(FALSE,"exe", mPEMake.mPeCtx.path.c_str(),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"TXT Files(*.exe)|*.exe|All Files(*.*)|*.*");
   ///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���  
	if(dlg.DoModal()==IDOK)  
	{
		CFile mFile(dlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
		mFile.Write(mPEMake.mPeCtx.pVirMem, mPEMake.mPeCtx.size);
		mFile.Close();
		AfxMessageBox("���ɹ�");
	}
	
}

//��Ӳ�������
void CPETOOLSDlg::OnAddPatch()
{
	//�����������
	if(!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	CAddPatch mDlg(this);
	if(mDlg.DoModal()==IDOK)  
	{
		OnSaveAs();
	}
}

//������ι���
void CPETOOLSDlg::OnAddSection()
{
	// TODO: �ڴ���������������
	if(!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	CAddSectionDlg mDlg(this);
	if(mDlg.DoModal()==IDOK)  
	{
		OnSaveAs();
	}
	else
		AfxMessageBox("���ʧ��!");
}

//����
void CPETOOLSDlg::OnEncrypt()
{
	if(!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	CEncryptDlg mDlg(this);
	mDlg.DoModal();
	
}

//λ�ü�����
void CPETOOLSDlg::OnPosCalc()
{
	// TODO: �ڴ���������������
	if (!mPEMake.isAnalysised())
	{
		AfxMessageBox("���ȷ���PE�ļ�");
		return;
	}
	if (pPosCalcDlg == NULL)
	{
		pPosCalcDlg = new CPosCalcDlg(this);
		pPosCalcDlg->Create(IDD_DIALOG8, this);
	}
	pPosCalcDlg->ShowWindow(SW_SHOW);
}

//ʮ���������
void CPETOOLSDlg::OnHexEditView()
{
	Create16EditWindow((unsigned char *)(mPEMake.mPeCtx.pVirMem), mPEMake.mPeCtx.size, 0, 0);
}
