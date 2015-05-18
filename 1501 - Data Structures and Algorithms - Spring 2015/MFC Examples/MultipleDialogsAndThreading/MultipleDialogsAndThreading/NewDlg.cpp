// NewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultipleDialogsAndThreading.h"
#include "NewDlg.h"
#include "afxdialogex.h"
#include <vector>
using std::vector;

extern vector<CString> Data;
// CNewDlg dialog

IMPLEMENT_DYNAMIC(CNewDlg, CDialogEx)

CNewDlg::CNewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewDlg::IDD, pParent)
{

}

CNewDlg::~CNewDlg()
{
}

void CNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_ListControl);
}


BEGIN_MESSAGE_MAP(CNewDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CNewDlg::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()


// CNewDlg message handlers


void CNewDlg::OnBnClickedButtonUpdate()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	for (unsigned int i=0; i<Data.size(); i++)
		m_ListControl.AddString(Data[i]);

	UpdateData(false);
}
