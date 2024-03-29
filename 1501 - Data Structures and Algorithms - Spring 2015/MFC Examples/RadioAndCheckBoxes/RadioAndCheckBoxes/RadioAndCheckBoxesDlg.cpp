
// RadioAndCheckBoxesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadioAndCheckBoxes.h"
#include "RadioAndCheckBoxesDlg.h"
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


// CRadioAndCheckBoxesDlg dialog




CRadioAndCheckBoxesDlg::CRadioAndCheckBoxesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRadioAndCheckBoxesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Radio = 0;
}

void CRadioAndCheckBoxesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Radio(pDX, IDC_RADIO1, m_RadioChoice);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
}

BEGIN_MESSAGE_MAP(CRadioAndCheckBoxesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RADIO, &CRadioAndCheckBoxesDlg::OnBnClickedButtonRadio)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CRadioAndCheckBoxesDlg::OnBnClickedButtonCheck)
END_MESSAGE_MAP()


// CRadioAndCheckBoxesDlg message handlers

BOOL CRadioAndCheckBoxesDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRadioAndCheckBoxesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRadioAndCheckBoxesDlg::OnPaint()
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
HCURSOR CRadioAndCheckBoxesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRadioAndCheckBoxesDlg::OnBnClickedButtonRadio()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString Message;
	Message.Format(L"Radio button number %d is selected.", m_Radio+1);
	AfxMessageBox(Message, MB_ICONINFORMATION);
	UpdateData(false);

}


void CRadioAndCheckBoxesDlg::OnBnClickedButtonCheck()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString Message;
	if (m_Check1 == TRUE)
	{
		Message.Format(L"Check button 1 is selected.");
		AfxMessageBox(Message, MB_ICONINFORMATION);
	}
	if (m_Check2 == TRUE)
	{
		Message.Format(L"Check button 2 is selected.");
		AfxMessageBox(Message, MB_ICONINFORMATION);
	}
	if (m_Check3 == TRUE)
	{
		Message.Format(L"Check button 3 is selected.");
		AfxMessageBox(Message, MB_ICONINFORMATION);
	}
	UpdateData(false);
}
