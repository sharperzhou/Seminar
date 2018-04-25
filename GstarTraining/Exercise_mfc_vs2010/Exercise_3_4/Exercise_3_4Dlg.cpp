
// Exercise_3_4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_3_4.h"
#include "Exercise_3_4Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_3_4Dlg 对话框




CExercise_3_4Dlg::CExercise_3_4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_3_4Dlg::IDD, pParent)
    , m_strText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_3_4Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDT, m_strText);
}

BEGIN_MESSAGE_MAP(CExercise_3_4Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_SORT_BTN, &CExercise_3_4Dlg::OnBnClickedSortBtn)
END_MESSAGE_MAP()


// CExercise_3_4Dlg 消息处理程序

BOOL CExercise_3_4Dlg::OnInitDialog()
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

void CExercise_3_4Dlg::OnPaint()
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
HCURSOR CExercise_3_4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CExercise_3_4Dlg::OnBnClickedSortBtn()
{
    UpdateData(TRUE);
    CArray<double> dArray;
    SplitStringToDoubleArray(m_strText, _T(" "), dArray);
    SortDoubleArray(dArray);

    m_strText.Empty();
    CString strBuf;
    int count = dArray.GetCount();
    for (int i = 0; i < count; ++i) {
        if (i <= count)
            strBuf.Format(_T("%f "), dArray[i]); 
        else
            strBuf.Format(_T("%f"), dArray[i]);

        m_strText += strBuf;
    }
    UpdateData(FALSE);
}

void CExercise_3_4Dlg::SplitStringToDoubleArray(LPCTSTR szSrc, LPCTSTR szDelim, CArray<double> &dArray)
{
    TCHAR *szBuf = new TCHAR[_tcslen(szSrc) + 1];
    _tcscpy(szBuf, szSrc);
    TCHAR *ptr = _tcstok(szBuf, szDelim);
    dArray.RemoveAll();
    while (ptr) {
        dArray.Add(_ttof(ptr));
        ptr = _tcstok(NULL, szDelim);
    }

    delete[] szBuf;
}

void CExercise_3_4Dlg::SortDoubleArray(CArray<double> &dArray)
{
    int i = 0, j = 0, count = dArray.GetCount();
    double temp;
    for (j = 0; j < count -1; ++j)
        for (i = 0; i < count - j - 1; ++i)
            if (dArray[i] > dArray[i + 1]) {
                temp = dArray[i], dArray[i] = dArray[i + 1],
                    dArray[i + 1] = temp;
            }
}
