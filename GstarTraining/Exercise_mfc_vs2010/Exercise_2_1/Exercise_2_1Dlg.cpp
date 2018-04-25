
// Exercise_2_1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_2_1.h"
#include "Exercise_2_1Dlg.h"
#include "afxdialogex.h"
#include "Calculation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_2_1Dlg 对话框




CExercise_2_1Dlg::CExercise_2_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_2_1Dlg::IDD, pParent)
    , m_iOper(0)
    , m_dVal1(0)
    , m_dVal2(0)
    , m_dResult(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_2_1Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_ADD_RD, m_iOper);
    DDX_Text(pDX, IDC_VALUE1_EDT, m_dVal1);
    DDX_Text(pDX, IDC_VALUE2_EDT, m_dVal2);
    DDX_Text(pDX, IDC_RESULT_STATIC, m_dResult);
}

BEGIN_MESSAGE_MAP(CExercise_2_1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_CALC_BTN, &CExercise_2_1Dlg::OnBnClickedCalcBtn)
END_MESSAGE_MAP()


// CExercise_2_1Dlg 消息处理程序

BOOL CExercise_2_1Dlg::OnInitDialog()
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

void CExercise_2_1Dlg::OnPaint()
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
HCURSOR CExercise_2_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise_2_1Dlg::OnBnClickedCalcBtn()
{
    GetDlgItem(IDC_RESULT_STATIC)->SetWindowText(_T("0"));
    UpdateData(TRUE);
    CCalculation calculation(m_dVal1, m_dVal2);
    switch (m_iOper) {
    case 0:
        calculation.Add(m_dResult);
        break;
    case 1:
        calculation.Subtract(m_dResult);
        break;
    case 2:
        calculation.Multiply(m_dResult);
        break;
    case 3:
        if (!calculation.Divide(m_dResult)) {
            AfxMessageBox(_T("计算出错，除数不能为零！"));
            GetDlgItem(IDC_RESULT_STATIC)->SetWindowText(_T("N/A"));
            return;
        }
        else break;
    default:
        break;
    }
    UpdateData(FALSE);
}


void CExercise_2_1Dlg::OnOK()
{
    // TODO: 在此添加专用代码和/或调用基类
    EndDialog(IDOK);

    //CDialogEx::OnOK();
}
