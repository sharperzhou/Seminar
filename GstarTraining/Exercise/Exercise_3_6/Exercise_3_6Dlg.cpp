
// Exercise_3_6Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_3_6.h"
#include "Exercise_3_6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_3_6Dlg 对话框

#define WM_NOTIFYICON (WM_USER + 100)



CExercise_3_6Dlg::CExercise_3_6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_3_6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    memset(&m_nid, 0, sizeof(NOTIFYICONDATA));
}

void CExercise_3_6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExercise_3_6Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_MESSAGE(WM_NOTIFYICON, &CExercise_3_6Dlg::OnNotifyIcon)
    ON_WM_DESTROY()
    ON_COMMAND(ID_SHOW, &CExercise_3_6Dlg::OnShow)
    ON_COMMAND(ID_EXIT, &CExercise_3_6Dlg::OnExit)
    ON_BN_CLICKED(IDOK, &CExercise_3_6Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CExercise_3_6Dlg 消息处理程序

BOOL CExercise_3_6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_nid.cbSize = sizeof(NOTIFYICONDATA);
    m_nid.uID = IDR_MAINFRAME;
    m_nid.hWnd = GetSafeHwnd();
    m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
    _tcscpy(m_nid.szTip, _T("托盘提示内容"));
    m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    m_nid.uCallbackMessage = WM_NOTIFYICON;

    Shell_NotifyIcon(NIM_ADD, &m_nid);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_3_6Dlg::OnPaint()
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
HCURSOR CExercise_3_6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CExercise_3_6Dlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
    if (IDR_MAINFRAME != wParam)
        return 1;

    switch (lParam) {
    case WM_LBUTTONUP:
            SetForegroundWindow();
            ShowWindow(SW_SHOWNORMAL);
        break;

    case WM_RBUTTONUP:
        {
            CMenu menu;
            menu.LoadMenu(IDR_MENU);
            CPoint point;
            GetCursorPos(&point);
            CMenu *pSubMenu = menu.GetSubMenu(0);
            SetForegroundWindow(); //解决托盘菜单不消失
            pSubMenu->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this);
            PostMessage(WM_NULL,0,0); //解决托盘菜单不消失
            menu.DestroyMenu();
        }

    default:
        break;
    }
    return 0;
}



void CExercise_3_6Dlg::OnDestroy()
{
    CDialogEx::OnDestroy();

    // TODO: 在此处添加消息处理程序代码

    Shell_NotifyIcon(NIM_DELETE, &m_nid);
}


void CExercise_3_6Dlg::OnShow()
{
    SetForegroundWindow();
    ShowWindow(SW_SHOWNORMAL);
}


void CExercise_3_6Dlg::OnExit()
{
    PostQuitMessage(0);
}


void CExercise_3_6Dlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    //if (IDYES == MessageBox(_T("最小化到右下角托盘吗？否则直接退出。"),
    //    NULL, MB_YESNO | MB_ICONQUESTION)) {
            ShowWindow(SW_HIDE);
            m_nid.uFlags |= NIF_INFO;
            m_nid.uTimeout = 1000;
            m_nid.dwInfoFlags = 1;
            _tcscpy(m_nid.szInfo, _T("已最小化到托盘"));
            _tcscpy(m_nid.szInfoTitle, _T("托盘提示"));
            Shell_NotifyIcon(NIM_MODIFY, &m_nid);
            return;
    //}

    CDialogEx::OnOK();
}
