
// Exercise_4_2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_4_2.h"
#include "Exercise_4_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_4_2Dlg 对话框

int CALLBACK EnumFontFamExProc(
    const LOGFONT    *lpelfe,
    const TEXTMETRIC *lpntme,
    DWORD      FontType,
    LPARAM     lParam
    );


CExercise_4_2Dlg::CExercise_4_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_4_2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_4_2Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO, m_Combo);
}

BEGIN_MESSAGE_MAP(CExercise_4_2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_CBN_SELCHANGE(IDC_COMBO, &CExercise_4_2Dlg::OnCbnSelchangeCombo)
END_MESSAGE_MAP()


// CExercise_4_2Dlg 消息处理程序

BOOL CExercise_4_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    HDC hdc = ::GetDC(GetSafeHwnd());
    LOGFONT lf = {0};
    lf.lfCharSet = DEFAULT_CHARSET;


    ::EnumFontFamiliesEx(hdc, &lf, EnumFontFamExProc, (LPARAM) &m_Combo, 0);

    ::ReleaseDC(GetSafeHwnd(), hdc);

    m_Combo.SetCurSel(0);
    CString strBuf;
    m_Combo.GetLBText(0, strBuf);
    SetFontAndFontName(IDC_SHOW_STATIC, strBuf);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_4_2Dlg::OnPaint()
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
HCURSOR CExercise_4_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExercise_4_2Dlg::SetFontAndFontName(int iCtrlId, LPCTSTR szFontName)
{
    CWnd *pCtrl = GetDlgItem(iCtrlId);
    ASSERT(pCtrl);

    LOGFONT lf = {0};
    CFont newFont;
    CFont *pFont = pCtrl->GetFont();
    pFont->GetLogFont(&lf);
    _tcscpy(lf.lfFaceName, szFontName);
    newFont.CreateFontIndirect(&lf);
    pCtrl->SetFont(&newFont);
    pCtrl->SetWindowText(szFontName);
}

int CALLBACK EnumFontFamExProc(const LOGFONT *lpelfe, const TEXTMETRIC *lpntme, DWORD FontType, LPARAM  lParam)
{
    CComboBox *pCombo = (CComboBox *) lParam;
    pCombo->AddString(lpelfe->lfFaceName);

    return TRUE;
}



void CExercise_4_2Dlg::OnCbnSelchangeCombo()
{
    // TODO: 在此添加控件通知处理程序代码
    CString strBuf;
    m_Combo.GetLBText(m_Combo.GetCurSel(), strBuf);
    SetFontAndFontName(IDC_SHOW_STATIC, strBuf);
}
