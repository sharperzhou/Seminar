
// Exercise_2_3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_2_3.h"
#include "Exercise_2_3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_2_3Dlg 对话框




CExercise_2_3Dlg::CExercise_2_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_2_3Dlg::IDD, pParent)
    , m_strFontName(_T("宋体")), m_clr(RGB(0,0,0)), m_clrBrush(m_clr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_2_3Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_FONTNAME_STATIC, m_strFontName);
    DDX_Control(pDX, IDC_RESULT_STATIC, m_ResultCtl);
}

BEGIN_MESSAGE_MAP(CExercise_2_3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_SETFONT_BTN, &CExercise_2_3Dlg::OnBnClickedSetfontBtn)
    ON_BN_CLICKED(IDC_SETCLR_BTN, &CExercise_2_3Dlg::OnBnClickedSetclrBtn)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CExercise_2_3Dlg 消息处理程序

BOOL CExercise_2_3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    CFont *pFont = m_ResultCtl.GetFont();
    LOGFONT lf;
    pFont->GetLogFont(&lf);
    _tcscpy(lf.lfFaceName, m_strFontName);
    m_Font.CreateFontIndirect(&lf);
    m_ResultCtl.SetFont(&m_Font);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_2_3Dlg::OnPaint()
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
HCURSOR CExercise_2_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise_2_3Dlg::OnBnClickedSetfontBtn()
{
    LOGFONT lf;
    m_Font.GetLogFont(&lf);
    CFontDialog fontDlg(&lf);
    fontDlg.m_cf.rgbColors = m_clr;
    
    if (IDOK == fontDlg.DoModal()) {
        //字体
        m_Font.DeleteObject();
        m_Font.CreateFontIndirect(fontDlg.m_cf.lpLogFont);
        m_strFontName = fontDlg.m_cf.lpLogFont->lfFaceName;
        m_ResultCtl.SetFont(&m_Font);
        UpdateData(FALSE);

        //颜色
        m_clr = fontDlg.GetColor();
        m_clrBrush.DeleteObject();
        m_clrBrush.CreateSolidBrush(m_clr);
        
        m_ResultCtl.Invalidate();
        GetDlgItem(IDC_CLR_STATIC)->Invalidate();
    }
}


void CExercise_2_3Dlg::OnBnClickedSetclrBtn()
{
    CColorDialog clrDlg(m_clr);
    if (IDOK == clrDlg.DoModal()) {
        m_clr = clrDlg.m_cc.rgbResult;
        m_clrBrush.DeleteObject();
        m_clrBrush.CreateSolidBrush(m_clr);
        m_ResultCtl.Invalidate();
        GetDlgItem(IDC_CLR_STATIC)->Invalidate();
    }
}


HBRUSH CExercise_2_3Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何特性

    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    switch (pWnd->GetDlgCtrlID()) {
    case IDC_CLR_STATIC:
        hbr = (HBRUSH) m_clrBrush.GetSafeHandle();
        break;
    case IDC_RESULT_STATIC:
        pDC->SetTextColor(m_clr);
    default:
        break;
    }

    return hbr;
}
