
// Exercise_4_1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_4_1.h"
#include "Exercise_4_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_4_1Dlg 对话框




CExercise_4_1Dlg::CExercise_4_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_4_1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_4_1Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_listbox);
}

BEGIN_MESSAGE_MAP(CExercise_4_1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CExercise_4_1Dlg 消息处理程序

BOOL CExercise_4_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_listbox.AddString(_T("SendMessage1"));
    m_listbox.AddString(_T("SendMessage2"));
    m_listbox.AddString(_T("SendMessage3"));
    m_listbox.AddString(_T("SendMessage4"));
    m_listbox.AddString(_T("SendMessage5"));
    m_listbox.AddString(_T("SendMessage6"));

    m_listbox.AddItemIconColor(RGB(255,0,0));
    m_listbox.AddItemIconColor(RGB(255,255,0));
    m_listbox.AddItemIconColor(RGB(255,0,255));
    m_listbox.AddItemIconColor(RGB(0,255,0));
    m_listbox.AddItemIconColor(RGB(0,255,255));
    m_listbox.AddItemIconColor(RGB(0,0,255));

    m_listbox.SetIconWidth(20);
    m_listbox.SetHighlightColor(RGB(204,232,255));

    m_listbox.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_4_1Dlg::OnPaint()
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
HCURSOR CExercise_4_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

