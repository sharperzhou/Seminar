
// Exercise_4_4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_4_4.h"
#include "Exercise_4_4Dlg.h"
#include "afxdialogex.h"
#include "DBAccess.h"
#include "AddInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_4_4Dlg 对话框




CExercise_4_4Dlg::CExercise_4_4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_4_4Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_4_4Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LISTVIEW, m_LV);
}

BEGIN_MESSAGE_MAP(CExercise_4_4Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_ADD_BTN, &CExercise_4_4Dlg::OnBnClickedAddBtn)
    ON_BN_CLICKED(IDC_REMOVE_BTN, &CExercise_4_4Dlg::OnBnClickedRemoveBtn)
END_MESSAGE_MAP()


// CExercise_4_4Dlg 消息处理程序

BOOL CExercise_4_4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_LV.InsertColumn(0, _T("地址"), LVCFMT_LEFT, 60);
    m_LV.InsertColumn(0, _T("年龄"), LVCFMT_LEFT, 40);
    m_LV.InsertColumn(0, _T("性别"), LVCFMT_LEFT, 40);
    m_LV.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, 60);
    m_LV.InsertColumn(0, _T("编号"), LVCFMT_LEFT, 40);

    m_LV.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    QueryData();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_4_4Dlg::OnPaint()
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
HCURSOR CExercise_4_4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CExercise_4_4Dlg::QueryData()
{
    m_LV.DeleteAllItems();

    DBAccess dbAccess;
    CAdoRecordSet recordSet;
    if (!dbAccess.executeQuery(_T("SELECT * FROM PERSONINFO"), recordSet))
        return FALSE;

    CString strBuf;
    recordSet.MoveLast();
    while (!recordSet.IsBOF()) {
        recordSet.GetCollect(_T("ID"), strBuf);
        m_LV.InsertItem(0, strBuf);
        recordSet.GetCollect(_T("UserName"), strBuf);
        m_LV.SetItemText(0, 1, strBuf);
        recordSet.GetCollect(_T("Sex"), strBuf);
        m_LV.SetItemText(0, 2, strBuf);
        recordSet.GetCollect(_T("Age"), strBuf);
        m_LV.SetItemText(0, 3, strBuf);
        recordSet.GetCollect(_T("Addr"), strBuf);
        m_LV.SetItemText(0, 4, strBuf);
        recordSet.MovePrevious();
    }

    recordSet.Close();

    return TRUE;
}



void CExercise_4_4Dlg::OnBnClickedAddBtn()
{
    CAddInfoDlg addInfoDlg;
    if (IDOK == addInfoDlg.DoModal()) {
        CString sql(_T("INSERT INTO PersonInfo(UserName,Sex,Age,Addr) VALUES(\'"));
        sql += addInfoDlg.m_strName;
        sql += _T("\',\'");
        sql += addInfoDlg.m_strSex;
        sql += _T("\',\'");
        sql += addInfoDlg.m_strAge;
        sql += _T("\',\'");
        sql += addInfoDlg.m_strAddr;
        sql += _T("\')");

        DBAccess dbAccess;
        if (dbAccess.executeNonQuery(sql) > 0) {
            AfxMessageBox(_T("成功添加一条用户信息！"));
            QueryData();
        }
        else
            AfxMessageBox(_T("用户信息添加失败！"));
    }
}


void CExercise_4_4Dlg::OnBnClickedRemoveBtn()
{
    // TODO: 在此添加控件通知处理程序代码
    int iRowId = m_LV.GetSelectionMark();
    if (-1 == iRowId) return;

    CString strPersonId = m_LV.GetItemText(iRowId, 0);
    {
        DBAccess dbAccess;
        CString sql;
        sql.Format(_T("DELETE FROM PersonInfo WHERE ID=%d"), _ttoi(strPersonId));
        dbAccess.executeNonQuery(sql);
    }

    QueryData();
}
