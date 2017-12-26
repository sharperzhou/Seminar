
// Exercise_2_5Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_2_5.h"
#include "Exercise_2_5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_2_5Dlg 对话框




CExercise_2_5Dlg::CExercise_2_5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_2_5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    personInfo[0].iAge = 45, personInfo[0].strName = _T("张三"), personInfo[0].strSex = _T("男");
    personInfo[1].iAge = 30, personInfo[1].strName = _T("李四"), personInfo[1].strSex = _T("男");
}

void CExercise_2_5Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_INFO_TREE, m_treeInfo);
}

BEGIN_MESSAGE_MAP(CExercise_2_5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(NM_CLICK, IDC_INFO_TREE, &CExercise_2_5Dlg::OnNMClickInfoTree)
END_MESSAGE_MAP()


// CExercise_2_5Dlg 消息处理程序

BOOL CExercise_2_5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    HTREEITEM hPatent, hChild;
    hPatent = m_treeInfo.InsertItem(_T("高2001班"));

    hChild = m_treeInfo.InsertItem(personInfo[0].strName, hPatent);
    m_treeInfo.SetItemData(hChild, (DWORD_PTR) &personInfo[0]);
    hChild = m_treeInfo.InsertItem(personInfo[1].strName, hPatent);
    m_treeInfo.SetItemData(hChild, (DWORD_PTR) &personInfo[1]);

    m_treeInfo.InsertItem(_T("高2002班"));

    m_treeInfo.Expand(hPatent, TVE_EXPAND);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_2_5Dlg::OnPaint()
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
HCURSOR CExercise_2_5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise_2_5Dlg::OnNMClickInfoTree(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码

    CPoint pt;
    UINT uFlag = 0;
    GetCursorPos(&pt);
    m_treeInfo.ScreenToClient(&pt);
    HTREEITEM hItemSel = m_treeInfo.GetSelectedItem();
    HTREEITEM hItemHistTest = m_treeInfo.HitTest(pt, &uFlag);

    if (hItemHistTest) {
        if (hItemHistTest == hItemSel) return;

        if (TVHT_ONITEM & uFlag) {
            PersonInfo *pPersonInfo = (PersonInfo*) m_treeInfo.GetItemData(hItemHistTest);
            CEdit *pEdtName = (CEdit*) GetDlgItem(IDC_NAME_EDT);
            CEdit *pEdtSex = (CEdit*) GetDlgItem(IDC_SEX_EDT);
            CEdit *pEdtAge = (CEdit*) GetDlgItem(IDC_AGE_EDT);
            if (pPersonInfo) {
                pEdtName->SetWindowText(pPersonInfo->strName);
                pEdtSex->SetWindowText(pPersonInfo->strSex);
                CString strBuf;
                strBuf.Format(_T("%d"), pPersonInfo->iAge);
                pEdtAge->SetWindowText(strBuf);
            }
            else {
                pEdtName->SetWindowText(_T(""));
                pEdtSex->SetWindowText(_T(""));
                pEdtAge->SetWindowText(_T(""));
            }
        }
    }

    *pResult = 0;
}
