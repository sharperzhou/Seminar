
// Exercise_1_4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_1_4.h"
#include "Exercise_1_4Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_1_4Dlg 对话框




CExercise_1_4Dlg::CExercise_1_4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_1_4Dlg::IDD, pParent)
    , m_iRadio(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_1_4Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_NAME_RD, m_iRadio);
}

BEGIN_MESSAGE_MAP(CExercise_1_4Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_CONTROL_RANGE(BN_CLICKED, IDC_NAME_RD, IDC_SEX_RD, OnCheckRadioButton)
END_MESSAGE_MAP()


// CExercise_1_4Dlg 消息处理程序

BOOL CExercise_1_4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    CComboBox *pCombo = (CComboBox*) GetDlgItem(IDC_SEX_CB);
    pCombo->AddString(_T("男"));
    pCombo->AddString(_T("女"));
    pCombo->SetCurSel(0);
    pCombo->EnableWindow(FALSE);

    GetDlgItem(IDC_NAME_EDT)->SetFocus();

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_1_4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExercise_1_4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExercise_1_4Dlg::OnCheckRadioButton(UINT uId)
{
    switch (uId)
    {
    case IDC_NAME_RD:
        GetDlgItem(IDC_SEX_CB)->EnableWindow(FALSE);
        GetDlgItem(IDC_NAME_EDT)->EnableWindow(TRUE);
        GetDlgItem(IDC_NAME_EDT)->SetFocus();
        break;

    case IDC_SEX_RD:
        GetDlgItem(IDC_SEX_CB)->EnableWindow(TRUE);
        GetDlgItem(IDC_NAME_EDT)->EnableWindow(FALSE);
        GetDlgItem(IDC_SEX_CB)->SetFocus();
        break;

    default:
        break;
    }
}

