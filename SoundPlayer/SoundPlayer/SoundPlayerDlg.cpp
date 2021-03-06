
// SoundPlayerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SoundPlayer.h"
#include <MMSystem.h>
#include "SoundPlayerDlg.h"
#include "afxdialogex.h"
#include "CWMPControls3.h"
#include "CWMPPlaylist.h"
#include "CWMPMedia3.h"
#include "CWMPMediaCollection2.h"

#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSoundPlayerDlg 对话框



CSoundPlayerDlg::CSoundPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOUNDPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSoundPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MEDIA_PLAYER, m_wmpPlayer);
}

BEGIN_MESSAGE_MAP(CSoundPlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_COMMAND(ID_OPEN, &CSoundPlayerDlg::OnOpen)
    ON_COMMAND(ID_MCILEN, &CSoundPlayerDlg::OnMcilen)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CSoundPlayerDlg, CDialogEx)
    ON_EVENT(CSoundPlayerDlg, IDC_MEDIA_PLAYER, 5101, CSoundPlayerDlg::PlayStateChangeMediaPlayer, VTS_I4)
END_EVENTSINK_MAP()


// CSoundPlayerDlg 消息处理程序

BOOL CSoundPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_hAccel = ::LoadAccelerators(NULL, MAKEINTRESOURCE(IDR_ACCELERATOR));
    CMenu menu;
    menu.LoadMenu(IDR_MENU);
    SetMenu(&menu);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSoundPlayerDlg::OnPaint()
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
HCURSOR CSoundPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSoundPlayerDlg::OnOpen()
{
    // TODO: 在此添加命令处理程序代码
    CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
        _T("所有文件(*.*)|*.*||"));
    if (IDOK == dlg.DoModal()) {
        CString strFileName = dlg.GetPathName();

        CWMPMedia3 media = m_wmpPlayer.newMedia(strFileName);
        CWMPPlaylist playList = m_wmpPlayer.get_currentPlaylist();
        playList.clear();
        playList.appendItem(media);


        CString strWndText;
        strWndText += _T("Sound Player - [");
        strWndText += media.get_sourceURL();
        strWndText += _T("] [");
        strWndText += media.get_durationString();
        strWndText += _T("]");
        SetWindowText(strWndText);

        if (IDYES == AfxMessageBox(_T("文件已打开，是否立即播放？"), MB_YESNO | MB_ICONINFORMATION)) {
            CWMPControls3 controller = m_wmpPlayer.get_controls();
            controller.play();
        }
    }
}

BOOL CSoundPlayerDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
        if (m_hAccel != NULL && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
            return TRUE;

    return CDialogEx::PreTranslateMessage(pMsg);
}

void CSoundPlayerDlg::PlayStateChangeMediaPlayer(long NewState)
{
    // TODO: 在此处添加消息处理程序代码
    if (NewState == 8) {
        if (IDYES == AfxMessageBox(_T("播放完毕，是否关闭窗口？"), MB_YESNO | MB_ICONINFORMATION))
            OnOK();
    }     
}


void CSoundPlayerDlg::OnMcilen()
{
    // TODO: 在此添加命令处理程序代码
    CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
        _T("所有文件(*.*)|*.*||"));
    if (IDOK == dlg.DoModal()) {
        CString strFileName = dlg.GetPathName();
            
        CWMPMedia3 media = m_wmpPlayer.newMedia(strFileName);

        CString strRet;
        strRet.Format(_T("播放长度为 %s"), media.get_durationString());
        
        MessageBox(strRet, _T("计算结果"));
    }
}
