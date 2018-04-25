
// Exercise_3_8Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_3_8.h"
#include "Exercise_3_8Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_3_8Dlg 对话框

#define WM_UPDATEVALUE (WM_USER + 100)


CExercise_3_8Dlg::CExercise_3_8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_3_8Dlg::IDD, pParent)
    , m_iThreadIndex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    for (int i = 0; i < 3; ++i)
        m_nId[i] = i + IDC_THRD1_STATIC;
}

void CExercise_3_8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExercise_3_8Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_MESSAGE(WM_UPDATEVALUE, &CExercise_3_8Dlg::OnUpdateValue)
    ON_WM_DESTROY()
END_MESSAGE_MAP()


// CExercise_3_8Dlg 消息处理程序

BOOL CExercise_3_8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    SetTimer(1, 1000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_3_8Dlg::OnPaint()
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
HCURSOR CExercise_3_8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

ULONG CExercise_3_8Dlg::m_ulData = 0;
CMutex CExercise_3_8Dlg::m_mutex;
BOOL CExercise_3_8Dlg::m_bDestroy = FALSE;

UINT CExercise_3_8Dlg::ThreadFun(LPVOID pParam)
{
    int *pId = (int*) pParam;
    while (TRUE) {
        WaitForSingleObject(m_mutex.m_hObject, INFINITE);
        if (!m_bDestroy) {
            InterlockedIncrement(&m_ulData);
            ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATEVALUE, 0, (LPARAM) *pId);
            Sleep(3000);
        }
        else {
            m_mutex.Unlock();
            break;
        }
        m_mutex.Unlock();
    }
    
    return 0;
}


void CExercise_3_8Dlg::OnTimer(UINT_PTR nIDEvent)
{
    SetDlgItemText(m_nId[m_iThreadIndex], _T("启动"));
    m_thread[m_iThreadIndex] = AfxBeginThread(ThreadFun, (LPVOID) &m_nId[m_iThreadIndex]);
    
    if (++m_iThreadIndex >= 3)
        KillTimer(1);

    CDialogEx::OnTimer(nIDEvent);
}

LRESULT CExercise_3_8Dlg::OnUpdateValue(WPARAM wParam, LPARAM lParam)
{
    SetDlgItemInt(IDC_NUM_EDT, m_ulData, FALSE);
    SetDlgItemText(IDC_THRD1_STATIC, IDC_THRD1_STATIC == lParam ? _T("运行") : _T("等待"));
    SetDlgItemText(IDC_THRD2_STATIC, IDC_THRD2_STATIC == lParam ? _T("运行") : _T("等待"));
    SetDlgItemText(IDC_THRD3_STATIC, IDC_THRD3_STATIC == lParam ? _T("运行") : _T("等待"));
    return 0;
}


void CExercise_3_8Dlg::OnDestroy()
{
    CDialogEx::OnDestroy();

    // TODO: 在此处添加消息处理程序代码
    m_bDestroy = TRUE;
    HANDLE hThread[] = {m_thread[0]->m_hThread,
        m_thread[1]->m_hThread, m_thread[2]->m_hThread};

    WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
}
