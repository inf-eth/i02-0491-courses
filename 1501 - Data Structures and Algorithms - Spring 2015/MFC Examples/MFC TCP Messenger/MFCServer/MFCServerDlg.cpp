
// MFCServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCServer.h"
#include "MFCServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT AcceptorThread(void*);
UINT ReceiverThread(void*);

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


// CMFCServerDlg dialog




CMFCServerDlg::CMFCServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCServerDlg::IDD, pParent)
	, m_Status(_T("Not Connected"))
	, m_Client_IP(_T(""))
	, m_Client_Port(0)
	, m_Input(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_Status);
	DDX_Text(pDX, IDC_EDIT_CLIENT_IP, m_Client_IP);
	DDX_Text(pDX, IDC_EDIT_CLIENT_PORT, m_Client_Port);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_Input);
	//  DDX_Text(pDX, IDC_RICHEDIT_OUTPUT, m_Output);
	DDX_Control(pDX, IDC_RICHEDIT_OUTPUT, m_RichEdit_Output_Control);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_Status_Control);
	DDX_Control(pDX, IDC_EDIT_CLIENT_IP, m_Client_IP_Control);
	DDX_Control(pDX, IDC_EDIT_CLIENT_PORT, m_Client_Port_Control);
}

BEGIN_MESSAGE_MAP(CMFCServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCServerDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDOK, &CMFCServerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCServerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCServerDlg message handlers

BOOL CMFCServerDlg::OnInitDialog()
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

	AfxBeginThread(AcceptorThread, (void*)this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCServerDlg::OnPaint()
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
HCURSOR CMFCServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCServerDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_Input == "")
		return;
	if (m_Status == "Not Connected")
	{
		AfxMessageBox(L"Not connected!", MB_ICONSTOP);
		return;
	}

	CString Input;
	Input = L"Server: " + m_Input + L"\r\n";
	AppendToOutput(Input);
	int choice = 1;
	ServerObj.Send((void*)&choice, sizeof(int));
	const size_t StringSize = 512;
	size_t CharactersConverted = 0;
	char Message[StringSize];
	wcstombs_s(&CharactersConverted, Message, m_Input.GetLength()+1, m_Input, _TRUNCATE);
	ServerObj.Send((void*)&Message, sizeof(Message));
	m_Input = L"";
	UpdateData(false);
}


void CMFCServerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_Status == "Connected")
	{
		int choice = -1;
		ServerObj.Send((void*)&choice, sizeof(int));
		while (m_Status == "Connected")
		{
		}
		ServerObj.CloseServerSocket();
		ServerObj.CloseClientSocket();
	}
	UpdateData(false);
	CDialogEx::OnOK();
}


void CMFCServerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_Status == "Connected")
	{
		int choice = -1;
		ServerObj.Send((void*)&choice, sizeof(int));
		while (m_Status == "Connected")
		{
		}
		ServerObj.CloseServerSocket();
		ServerObj.CloseClientSocket();
	}
	UpdateData(false);
	CDialogEx::OnCancel();
}


UINT AcceptorThread(void* Arg)
{
	CMFCServerDlg* ServerDlgPtr = (CMFCServerDlg*)Arg;

	ServerDlgPtr->ServerObj.CloseServerSocket();
	ServerDlgPtr->ServerObj.CloseClientSocket();
	// Create Server socket and set socket options.
	ServerDlgPtr->ServerObj.CreateSocket(TCPSOCKET);		// No argument means TCPSOCKET
	ServerDlgPtr->ServerObj.SetSocketOptions();
	// Initialise Server address struct and bind it with Server's socket.
	ServerDlgPtr->ServerObj.InitialiseAddress(6000);
	ServerDlgPtr->ServerObj.Bind();
	// Listen for incoming connections.
	ServerDlgPtr->ServerObj.Listen();
	// Accept any incoming connections.
	ServerDlgPtr->ServerObj.Accept();

	ServerDlgPtr->m_Status = "Connected";
	ServerDlgPtr->m_Status_Control.SetWindowTextW(L"Connected");
	CString ClientIP(ServerDlgPtr->ServerObj.GetClientIP());
	ServerDlgPtr->m_Client_Port = ServerDlgPtr->ServerObj.GetClientPort();
	ServerDlgPtr->m_Client_IP_Control.SetWindowTextW(ClientIP);
	CString ClientPort;
	ClientPort.Format(L"%d", ServerDlgPtr->m_Client_Port);
	ServerDlgPtr->m_Client_Port_Control.SetWindowTextW(ClientPort);

	AfxBeginThread(ReceiverThread, Arg);
	return 0;
}

UINT ReceiverThread(void* Arg)
{
	CMFCServerDlg* ServerDlgPtr = (CMFCServerDlg*)Arg;
	while (true)
	{
		int choice;
		int check = ServerDlgPtr->ServerObj.Receive((void*)&choice, sizeof(int));
		if (check == -1)
		{
			ServerDlgPtr->m_Status = "Not Connected";
			ServerDlgPtr->m_Status_Control.SetWindowTextW(L"Not Connected");
			AfxBeginThread(AcceptorThread, Arg);
			return 0;
		}
		if (choice == 1)
		{
			char Buffer[512];
			ServerDlgPtr->ServerObj.Receive((void*)&Buffer, sizeof(Buffer));
			CString Input(Buffer);
			Input = L"Client: " + Input + L"\r\n";
			ServerDlgPtr->AppendToOutput(Input);
		}
		if (choice == -1)
		{
			int choice1 = -2;
			ServerDlgPtr->ServerObj.Send((void*)&choice1, sizeof(int));
			ServerDlgPtr->m_Status = "Not Connected";
			ServerDlgPtr->m_Status_Control.SetWindowTextW(L"Not Connected");
			AfxBeginThread(AcceptorThread, Arg);
			return 0;
		}
		if (choice == -2)
		{
			ServerDlgPtr->m_Status = "Not Connected";
			ServerDlgPtr->m_Status_Control.SetWindowTextW(L"Not Connected");
			AfxBeginThread(AcceptorThread, Arg);
			return 0;
		}
	}
	return 0;
}

// Taken from: http://www.codeproject.com/Articles/12093/Using-RichEditCtrl-to-Display-Formatted-Logs
int CMFCServerDlg::AppendToOutput(CString Input)
{
	long nVisible = 0;
	long nInsertionPoint = 0;

	// Set insertion point to end of text
	nInsertionPoint = m_RichEdit_Output_Control.GetWindowTextLength();
	m_RichEdit_Output_Control.SetSel(nInsertionPoint, -1);

	// Replace selection. Because we have nothing
	// selected, this will simply insert
	// the string at the current caret position.
	m_RichEdit_Output_Control.ReplaceSel(Input);

	// Get number of currently visible lines or maximum number of visible lines
	// (We must call GetNumVisibleLines() before the first call to LineScroll()!)
	nVisible = GetNumVisibleLines();

	// Now this is the fix of CRichEditCtrl's abnormal behaviour when used
	// in an application not based on dialogs. Checking the focus prevents
	// us from scrolling when the CRichEditCtrl does so automatically,
	// even though ES_AUTOxSCROLL style is NOT set.
	if (&m_RichEdit_Output_Control != m_RichEdit_Output_Control.GetFocus())
	{
		m_RichEdit_Output_Control.LineScroll(INT_MAX);
		m_RichEdit_Output_Control.LineScroll(1 - nVisible);
	}

	return 0;
}


int CMFCServerDlg::GetNumVisibleLines(void)
{
	CRect rect;
	long nFirstChar, nLastChar;
	long nFirstLine, nLastLine;

	// Get client rect of rich edit control
	m_RichEdit_Output_Control.GetClientRect(rect);

	// Get character index close to upper left corner
	nFirstChar = m_RichEdit_Output_Control.CharFromPos(CPoint(0, 0));

	// Get character index close to lower right corner
	nLastChar = m_RichEdit_Output_Control.CharFromPos(CPoint(rect.right, rect.bottom));
	if (nLastChar < 0)
	{
		nLastChar = m_RichEdit_Output_Control.GetTextLength();
	}

	// Convert to lines
	nFirstLine = m_RichEdit_Output_Control.LineFromChar(nFirstChar);
	nLastLine  = m_RichEdit_Output_Control.LineFromChar(nLastChar);

	return (nLastLine - nFirstLine);
}
