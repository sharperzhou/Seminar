
// Exercise_3_2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_3_2.h"
#include "Exercise_3_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_3_2Dlg 对话框




CExercise_3_2Dlg::CExercise_3_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_3_2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_3_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExercise_3_2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CExercise_3_2Dlg 消息处理程序

BOOL CExercise_3_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    //ULARGE_INTEGER uliFreeBytesAvailableToCaller = {0};
    ULARGE_INTEGER uliTotalNumberOfBytes = {0};
    ULARGE_INTEGER uliTotalNumberOfFreeBytes = {0};

    //DWORD diskInfo = GetLogicalDrives();
    //int diskCount = 0;
    //while (diskInfo) {
    //    if (1 & diskInfo)
    //        ++diskCount;

    //    diskInfo >>= 1;
    //}

    BOOL bRet = GetDiskFreeSpaceEx(NULL, NULL,
        &uliTotalNumberOfBytes, &uliTotalNumberOfFreeBytes);

    CString strFree, strTotal;
    if (bRet) {
        FormatString(uliTotalNumberOfFreeBytes.QuadPart, strFree);
        FormatString(uliTotalNumberOfBytes.QuadPart, strTotal);

        strFree += _T(" 字节");
        strTotal += _T(" 字节");
    }
    else {
        strFree = _T("N/A 字节");
        strTotal = _T("N/A 字节");
    }
    
    SetDlgItemText(IDC_FREE_STATIC, strFree);
    SetDlgItemText(IDC_TOTAL_STATIC, strTotal);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_3_2Dlg::OnPaint()
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
HCURSOR CExercise_3_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExercise_3_2Dlg::FormatString(ULONGLONG ullNumber, CString &strResult)
{
    strResult.Empty();

    CString strBuf;

    do {
        strBuf.Format(_T("%d"), ullNumber % 1000);
        strResult = strBuf + strResult;
        if (ullNumber /= 1000)
            strResult = _T(",") + strResult;
    } while (ullNumber);
    
}

