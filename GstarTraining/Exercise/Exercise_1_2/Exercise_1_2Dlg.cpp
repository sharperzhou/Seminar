
// Exercise_1_2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_1_2.h"
#include "Exercise_1_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_1_2Dlg 对话框




CExercise_1_2Dlg::CExercise_1_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_1_2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_1_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STUINFOFIELD_LIST, m_StuInfoField);
	DDX_Control(pDX, IDC_REPORTFIELD_LIST, m_ReportField);
}

BEGIN_MESSAGE_MAP(CExercise_1_2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_BTN, &CExercise_1_2Dlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_REMOVE_BTN, &CExercise_1_2Dlg::OnBnClickedRemoveBtn)
	ON_BN_CLICKED(IDC_ADDALL_BTN, &CExercise_1_2Dlg::OnBnClickedAddallBtn)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CExercise_1_2Dlg::OnBnClickedClearBtn)
END_MESSAGE_MAP()


// CExercise_1_2Dlg 消息处理程序

BOOL CExercise_1_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_StuInfoField.AddString(_T("地址"));
	m_StuInfoField.AddString(_T("电话"));
	m_StuInfoField.AddString(_T("姓名"));
	m_StuInfoField.AddString(_T("性别"));
	m_StuInfoField.AddString(_T("学号"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_1_2Dlg::OnPaint()
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
HCURSOR CExercise_1_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise_1_2Dlg::OnBnClickedAddBtn()
{
	int index = m_StuInfoField.GetCurSel();
	if (-1 == index) return;

    CString strStuInfoField, strReportField;
    m_StuInfoField.GetText(index, strStuInfoField);

    int count = m_ReportField.GetCount();

    for (int i = 0; i < count; ++i) {
        m_ReportField.GetText(i, strReportField);
        if (strReportField == strStuInfoField) {
            AfxMessageBox(_T("所选字段已添加！"), MB_ICONWARNING);
            return;
        }
    }

    m_ReportField.AddString((LPCTSTR) strStuInfoField);
}


void CExercise_1_2Dlg::OnBnClickedRemoveBtn()
{
	m_ReportField.DeleteString(m_ReportField.GetCurSel());
}


void CExercise_1_2Dlg::OnBnClickedAddallBtn()
{
    m_ReportField.ResetContent();
	int count = m_StuInfoField.GetCount();
	for (int i = 0; i < count; ++i) {
		CString str;
		m_StuInfoField.GetText(i, str);
		m_ReportField.AddString((LPCTSTR) str);
	}
}


void CExercise_1_2Dlg::OnBnClickedClearBtn()
{
	//int count = m_ReportField.GetCount();
	//for (int i = count - 1; i >= 0; --i) {
	//	m_ReportField.DeleteString(i);
	//}
    m_ReportField.ResetContent();
}
