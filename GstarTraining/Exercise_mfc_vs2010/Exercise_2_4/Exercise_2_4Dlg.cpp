
// Exercise_2_4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_2_4.h"
#include "Exercise_2_4Dlg.h"
#include "afxdialogex.h"
#include "UserInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_2_4Dlg 对话框




CExercise_2_4Dlg::CExercise_2_4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_2_4Dlg::IDD, pParent)
    , m_strName(_T("")), m_strSex(_T("")), m_iAge(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_2_4Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExercise_2_4Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_SHOW_BTN, &CExercise_2_4Dlg::OnBnClickedShowBtn)
END_MESSAGE_MAP()


// CExercise_2_4Dlg 消息处理程序

BOOL CExercise_2_4Dlg::OnInitDialog()
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

void CExercise_2_4Dlg::OnPaint()
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
HCURSOR CExercise_2_4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise_2_4Dlg::OnBnClickedShowBtn()
{
    
    CUserInfoDlg userInfoDlg;
    CString str;
    CEdit *pInfo = (CEdit*) GetDlgItem(IDC_INFO_EDT);
    pInfo->GetWindowText(str);

    if (!str.IsEmpty()) {
        CStringArray strArray;
        SplitString((LPCTSTR) str, _T("-"), strArray);
        if (strArray.GetCount() >= 3) {
            userInfoDlg.m_strName = m_strName = strArray[0];
            userInfoDlg.m_strSex = m_strSex = strArray[1];
            userInfoDlg.m_iAge = m_iAge = _ttoi((LPCTSTR) strArray[2]);
        }
    }

    if (IDOK == userInfoDlg.DoModal()) {
        if (userInfoDlg.m_strName.IsEmpty() || userInfoDlg.m_strSex.IsEmpty()) {
            str.Empty();
        }
        else {
            m_strName = userInfoDlg.m_strName;
            m_strSex = userInfoDlg.m_strSex;
            m_iAge = userInfoDlg.m_iAge;
            str.Format(_T("%s-%s-%d"), m_strName, m_strSex, m_iAge);
        }

        pInfo->SetWindowText(str);
    }
}

void CExercise_2_4Dlg::SplitString(LPCTSTR szSrc, LPCTSTR szDelim, CStringArray &strArray)
{
    LPTSTR szTemp = new TCHAR[_tcslen(szSrc) + 1];
    _tcscpy(szTemp, szSrc);

    LPTSTR ptr = _tcstok(szTemp, szDelim);
    strArray.RemoveAll();
    while (ptr) {
        strArray.Add(ptr);
        ptr = _tcstok(NULL, szDelim);
    }
    delete[] szTemp;
}
