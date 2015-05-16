
// MFCClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCClientDlg dialog




CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Port = 6000;
	m_IP = _T("127.0.0.1");
	m_Status = _T("Disconnected");
	m_A_img = 0.0f;
	m_A_real = 0.0f;
	m_B_img = 0.0f;
	m_B_real = 0.0f;
	m_Result_img = 0.0f;
	m_Result_real = 0.0f;
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_Port);
	DDV_MinMaxInt(pDX, m_Port, 200, 65535);
	DDX_Text(pDX, IDC_EDIT_SERVERIP, m_IP);
	DDV_MaxChars(pDX, m_IP, 255);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_Status);
	DDV_MaxChars(pDX, m_Status, 20);
	DDX_Text(pDX, IDC_EDIT_AIMG, m_A_img);
	DDX_Text(pDX, IDC_EDIT_AREAL, m_A_real);
	DDX_Text(pDX, IDC_EDIT_BIMG, m_B_img);
	DDX_Text(pDX, IDC_EDIT_BREAL, m_B_real);
	DDX_Text(pDX, IDC_EDIT_RESULTIMG, m_Result_img);
	DDX_Text(pDX, IDC_EDIT_RESULTREAL, m_Result_real);
}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMFCClientDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUBTRACT, &CMFCClientDlg::OnBnClickedButtonSubtract)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CMFCClientDlg::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CMFCClientDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDOK, &CMFCClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCClientDlg message handlers

BOOL CMFCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// Create Client Socket.
	ClientObj.CreateSocket(TCPSOCKET);
	ClientObj.SetSocketOptions();

	// Initialise and bind Client address.
	ClientObj.InitialiseAddress(6001);
	ClientObj.Bind();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCClientDlg::OnBnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_Status == "Connected!")
	{
		AfxMessageBox(_T("Already connected to Server!"));
		return;
	}
	// Connect to Server. Server name/IP and port are provided as arguments.
	// Conversion of CString into char array.
	const size_t StringSize = 256;
	size_t CharactersConverted = 0;
	char ServerIP[StringSize];
	wcstombs_s(&CharactersConverted, ServerIP, m_IP.GetLength()+1, m_IP, _TRUNCATE);

	int Check = ClientObj.Connect(ServerIP, m_Port);
	if (Check == -1)
	{
		AfxMessageBox(_T("Cannot connect to Server!"), MB_ICONSTOP);
		
	}
	else
	{
		AfxMessageBox(_T("Connected to Server!"), MB_ICONINFORMATION);
		m_Status = "Connected!";
	}
	UpdateData(false);
}


void CMFCClientDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_Status != "Connected!")
	{
		AfxMessageBox(_T("Not connected to Server!"), MB_ICONSTOP);
		return;
	}
	int choice = 1;
	Complex A;
	Complex B;
	Complex Result;
	A.real = m_A_real;
	A.img = m_A_img;
	B.real = m_B_real;
	B.img = m_B_img;
	ClientObj.Send((void*)&choice, sizeof(int));
	ClientObj.Send((void*)&A, sizeof(Complex));
	ClientObj.Send((void*)&B, sizeof(Complex));
	ClientObj.Receive((void*)&Result, sizeof(Complex));
	m_Result_real = Result.real;
	m_Result_img = Result.img;
	UpdateData(false);
}


void CMFCClientDlg::OnBnClickedButtonSubtract()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_Status != "Connected!")
	{
		AfxMessageBox(_T("Not connected to Server!"), MB_ICONSTOP);
		return;
	}
	int choice = 2;
	Complex A;
	Complex B;
	Complex Result;
	A.real = m_A_real;
	A.img = m_A_img;
	B.real = m_B_real;
	B.img = m_B_img;
	ClientObj.Send((void*)&choice, sizeof(int));
	ClientObj.Send((void*)&A, sizeof(Complex));
	ClientObj.Send((void*)&B, sizeof(Complex));
	ClientObj.Receive((void*)&Result, sizeof(Complex));
	m_Result_real = Result.real;
	m_Result_img = Result.img;
	UpdateData(false);
}


void CMFCClientDlg::OnBnClickedButtonMultiply()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_Status != "Connected!")
	{
		AfxMessageBox(_T("Not connected to Server!"), MB_ICONSTOP);
		return;
	}
	int choice = 3;
	Complex A;
	Complex B;
	Complex Result;
	A.real = m_A_real;
	A.img = m_A_img;
	B.real = m_B_real;
	B.img = m_B_img;
	ClientObj.Send((void*)&choice, sizeof(int));
	ClientObj.Send((void*)&A, sizeof(Complex));
	ClientObj.Send((void*)&B, sizeof(Complex));
	ClientObj.Receive((void*)&Result, sizeof(Complex));
	m_Result_real = Result.real;
	m_Result_img = Result.img;
	UpdateData(false);
}


void CMFCClientDlg::OnBnClickedButtonDivide()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_Status != "Connected!")
	{
		AfxMessageBox(_T("Not connected to Server!"), MB_ICONSTOP);
		return;
	}
	int choice = 4;
	Complex A;
	Complex B;
	Complex Result;
	A.real = m_A_real;
	A.img = m_A_img;
	B.real = m_B_real;
	B.img = m_B_img;
	ClientObj.Send((void*)&choice, sizeof(int));
	ClientObj.Send((void*)&A, sizeof(Complex));
	ClientObj.Send((void*)&B, sizeof(Complex));
	ClientObj.Receive((void*)&Result, sizeof(Complex));
	m_Result_real = Result.real;
	m_Result_img = Result.img;
	UpdateData(false);
}


void CMFCClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int choice = 5;
	ClientObj.Send((void*)&choice, sizeof(int));
	ClientObj.CloseClientSocket();
	CDialogEx::OnOK();
}


void CMFCClientDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	int choice = 5;
	ClientObj.Send((void*)&choice, sizeof(int));
	ClientObj.CloseClientSocket();
	CDialogEx::OnCancel();
}
