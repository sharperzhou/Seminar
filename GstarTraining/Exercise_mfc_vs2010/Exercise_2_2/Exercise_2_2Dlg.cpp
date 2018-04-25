
// Exercise_2_2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_2_2.h"
#include "Exercise_2_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_2_2Dlg 对话框




CExercise_2_2Dlg::CExercise_2_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_2_2Dlg::IDD, pParent)
    , m_iSpeed(30), m_hbrCtl(RGB(0,0,0))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    //初始化RGB值
    for (int i = 0; i < 3; ++i)
        m_iColor[i] = 0;
}

void CExercise_2_2Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExercise_2_2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_HSCROLL()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CExercise_2_2Dlg 消息处理程序

BOOL CExercise_2_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    ((CScrollBar*) GetDlgItem(IDC_R_SCRBAR))->SetScrollRange(0, 255);
    ((CScrollBar*) GetDlgItem(IDC_G_SCRBAR))->SetScrollRange(0, 255);
    ((CScrollBar*) GetDlgItem(IDC_B_SCRBAR))->SetScrollRange(0, 255);

    CSliderCtrl *pSlider = (CSliderCtrl*) GetDlgItem(IDC_SPEED_SLIDER);
    pSlider->SetRange(1,100);
    pSlider->SetPos(m_iSpeed);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_2_2Dlg::OnPaint()
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
HCURSOR CExercise_2_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CExercise_2_2Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (pScrollBar->GetDlgCtrlID() == IDC_SPEED_SLIDER) {
        m_iSpeed = ((CSliderCtrl*) pScrollBar)->GetPos();
        this->SetDlgItemInt(IDC_SPEEDVAL_STATIC, m_iSpeed, FALSE);
    }
    else {
        int i = pScrollBar->GetDlgCtrlID() - IDC_R_SCRBAR;
        switch (nSBCode) {
        case SB_LINELEFT: m_iColor[i] -= 1; break;
        case SB_LINERIGHT: m_iColor[i] += 1; break;
        case SB_PAGELEFT: m_iColor[i] -= m_iSpeed; break;
        case SB_PAGERIGHT: m_iColor[i] += m_iSpeed; break;
        case SB_LEFT: m_iColor[i] = 0; break;
        case SB_RIGHT: m_iColor[i] = 255; break;

        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            m_iColor[i] = nPos;
            break;

        default:
            break;
        }

        m_iColor[i] = max(0, min(m_iColor[i], 255));
        pScrollBar->SetScrollPos(m_iColor[i]);
        this->SetDlgItemInt(i + IDC_RVAL_STATIC, m_iColor[i], FALSE);
        GetDlgItem(IDC_CTL_STATIC)->InvalidateRect(NULL);
    }

    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

HBRUSH CExercise_2_2Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何特性

    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    if (pWnd->GetDlgCtrlID() == IDC_CTL_STATIC) {
        m_hbrCtl.DeleteObject();
        m_hbrCtl.CreateSolidBrush(RGB(m_iColor[0], m_iColor[1], m_iColor[2]));
        return (HBRUSH) m_hbrCtl.GetSafeHandle();
    }

    return hbr;
}
