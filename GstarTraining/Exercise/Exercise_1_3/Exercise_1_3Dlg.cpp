
// Exercise_1_3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_1_3.h"
#include "Exercise_1_3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExercise_1_3Dlg 对话框


CExercise_1_3Dlg::CExercise_1_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_1_3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_1_3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CURITEM_STATIC, m_CurItem);
	DDX_Control(pDX, IDC_CATALOG_COMBO, m_Catalog);
	DDX_Control(pDX, IDC_LIST_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CExercise_1_3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_CBN_SELCHANGE(IDC_CATALOG_COMBO, &CExercise_1_3Dlg::OnCbnSelchangeCatalogCombo)
    ON_LBN_SELCHANGE(IDC_LIST_LIST, &CExercise_1_3Dlg::OnLbnSelchangeListList)
END_MESSAGE_MAP()


// CExercise_1_3Dlg 消息处理程序

BOOL CExercise_1_3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

    InitData();


    m_Catalog.SetCurSel(0);
    OnCbnSelchangeCatalogCombo();
    m_List.SetCurSel(0);
    OnLbnSelchangeListList();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_1_3Dlg::OnPaint()
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
HCURSOR CExercise_1_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExercise_1_3Dlg::InitData()
{
    m_ArrayFruit.Add(_T("波罗"));
    m_ArrayFruit.Add(_T("梨"));
    m_ArrayFruit.Add(_T("猕猴桃"));
    m_ArrayFruit.Add(_T("苹果"));
    m_ArrayStudyMaterial.Add(_T("钢笔"));
    m_ArrayStudyMaterial.Add(_T("笔记本"));
    m_ArrayStudyMaterial.Add(_T("橡皮"));

    m_Catalog.AddString(_T("水果"));
    m_Catalog.AddString(_T("学习用品"));

    m_Catalog.SetItemDataPtr(0, (void*) &m_ArrayFruit);
    m_Catalog.SetItemDataPtr(1, (void*) &m_ArrayStudyMaterial);
}

void CExercise_1_3Dlg::OnCbnSelchangeCatalogCombo()
{
    m_List.ResetContent();
    CArray<CString> *pListItem = (CArray<CString> *) (m_Catalog.GetItemDataPtr(m_Catalog.GetCurSel()));
    int iCount = pListItem->GetCount();
    for (int i = 0; i < iCount; ++i)
        m_List.AddString(pListItem->GetAt(i));

    m_List.SetCurSel(0);
    OnLbnSelchangeListList();
}


void CExercise_1_3Dlg::OnLbnSelchangeListList()
{
    CString str;
    m_List.GetText(m_List.GetCurSel(), str);
    m_CurItem.SetWindowText(str);
}
