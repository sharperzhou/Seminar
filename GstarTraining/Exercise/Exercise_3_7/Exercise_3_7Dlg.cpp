
// Exercise_3_7Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_3_7.h"
#include "Exercise_3_7Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_3_7Dlg 对话框




CExercise_3_7Dlg::CExercise_3_7Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_3_7Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_3_7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExercise_3_7Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_INSTALL_BTN, &CExercise_3_7Dlg::OnBnClickedInstallBtn)
    ON_BN_CLICKED(IDC_UNINSTALL_BTN, &CExercise_3_7Dlg::OnBnClickedUninstallBtn)
END_MESSAGE_MAP()


// CExercise_3_7Dlg 消息处理程序

BOOL CExercise_3_7Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_3_7Dlg::OnPaint()
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
HCURSOR CExercise_3_7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise_3_7Dlg::OnBnClickedInstallBtn()
{
    HKEY hKey;
    int iRet;
    TCHAR szThisFileName[MAX_PATH];
    do {
        iRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
            0, KEY_WRITE, &hKey);
        if (ERROR_SUCCESS != iRet) {
            AfxMessageBox(_T("打开注册表Run项失败！"), MB_ICONERROR);
            break;
        }

        iRet = RegSetValueEx(hKey, _T("Exercise_3_7"), 0, REG_SZ,
            (const BYTE*) szThisFileName,
            GetModuleFileName(NULL, szThisFileName, MAX_PATH)*sizeof(TCHAR));
        if (ERROR_SUCCESS != iRet) {
            AfxMessageBox(_T("设置Exercise_3_7启动项失败！"), MB_ICONERROR);
            break;
        }

        AfxMessageBox(_T("Exercise_3_7启动项安装成功！"));
    } while (FALSE);

    RegCloseKey(hKey);
}


void CExercise_3_7Dlg::OnBnClickedUninstallBtn()
{
    int iRet;
    HKEY hKey;
    do {
        iRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
            0, KEY_QUERY_VALUE | KEY_WRITE, &hKey);
        if (ERROR_SUCCESS != iRet) {
            AfxMessageBox(_T("打开注册表Run项失败！"), MB_ICONERROR);
            break;
        }

        DWORD dwData, dwType;
        iRet = RegQueryValueEx(hKey, _T("Exercise_3_7"), 0, &dwType, NULL, &dwData);
        if (ERROR_SUCCESS != iRet) {
            AfxMessageBox(_T("Exercise_3_7启动项不存在，无需卸载！"));
            break;
        }

        iRet = RegDeleteValue(hKey, _T("Exercise_3_7"));
        if (ERROR_SUCCESS == iRet)
            AfxMessageBox(_T("Exercise_3_7启动项卸载成功！"));
        else
            AfxMessageBox(_T("Exercise_3_7启动项卸载失败！"), MB_ICONERROR);

    } while (FALSE);

    RegCloseKey(hKey);
    
    //iRet = RegDeleteKeyValue(HKEY_LOCAL_MACHINE,
    //    _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
    //    _T("Exercise_3_7"));
}
