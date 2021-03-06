
// TreeCtrlRecursionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "TreeCtrlRecursion.h"
#include "TreeCtrlRecursionDlg.h"
#include "afxdialogex.h"

#include <queue>
#include <stack>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTreeCtrlRecursionDlg 对话框



CTreeCtrlRecursionDlg::CTreeCtrlRecursionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TREECTRLRECURSION_DIALOG, pParent)
    , m_nOption(0)
    , m_strFind(_T(""))
    , m_uIndent(2)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeCtrlRecursionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE, m_tree);
    DDX_Control(pDX, IDC_EDIT_LOG, m_editlogger);
    DDX_Radio(pDX, IDC_RD_FIND, m_nOption);
    DDX_Text(pDX, IDC_EDIT_FIND, m_strFind);
    DDX_Text(pDX, IDC_EDIT_INDENT, m_uIndent);
	DDV_MinMaxUInt(pDX, m_uIndent, 0, 8);
}

BEGIN_MESSAGE_MAP(CTreeCtrlRecursionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_RESET, &CTreeCtrlRecursionDlg::OnBnClickedBtnReset)
    ON_BN_CLICKED(IDC_BTN_EXECUTE, &CTreeCtrlRecursionDlg::OnBnClickedBtnExecute)
    ON_BN_CLICKED(IDC_BTN_CLEAR, &CTreeCtrlRecursionDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CTreeCtrlRecursionDlg 消息处理程序

BOOL CTreeCtrlRecursionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    InitTree();

    GetDlgItem(IDC_EDIT_FIND)->SetFocus();
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTreeCtrlRecursionDlg::OnPaint()
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
HCURSOR CTreeCtrlRecursionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTreeCtrlRecursionDlg::InitTree()
{
    auto hRoot1 = m_tree.InsertItem(_T("Root1"));
    auto hRoot2 = m_tree.InsertItem(_T("Root2"));
    m_tree.InsertItem(_T("Root3"));

    auto hSubRoot1 = m_tree.InsertItem(_T("SubRoot1"), hRoot1);
    auto hSubRoot2 = m_tree.InsertItem(_T("SubRoot2"), hSubRoot1);
    auto hSubRoot3 = m_tree.InsertItem(_T("SubRoot3"), hRoot2);

    m_tree.InsertItem(_T("Leaf1"), hRoot1);
    m_tree.InsertItem(_T("Leaf2"), hSubRoot1);
    m_tree.InsertItem(_T("Leaf3"), hSubRoot2);
    m_tree.InsertItem(_T("Leaf4"), hSubRoot3);

    m_tree.Expand(hRoot1, TVE_EXPAND);
    m_tree.Expand(hRoot2, TVE_EXPAND);
    m_tree.Expand(hSubRoot1, TVE_EXPAND);
    m_tree.Expand(hSubRoot2, TVE_EXPAND);
    m_tree.Expand(hSubRoot3, TVE_EXPAND);
}

HTREEITEM CTreeCtrlRecursionDlg::findItem(LPCTSTR szItemName, HTREEITEM hBegin, HTREEITEM hEnd)
{
    auto hItem = hBegin ? hBegin : m_tree.GetRootItem();
    HTREEITEM hFind = NULL;

    while (hItem && hItem != hEnd) {
        
        auto strText = m_tree.GetItemText(hItem);
        putLog(_T("当前节点：") + strText);

        if (!strText.Compare(szItemName)) {
            hFind = hItem;
            break;
        }

        if (m_tree.ItemHasChildren(hItem)) {
            auto hChild = m_tree.GetChildItem(hItem);
            hFind = findItem(szItemName, hChild, hEnd);
            if (hFind)
                break;
        }

        hItem = m_tree.GetNextSiblingItem(hItem);
    }

    return hFind;
}

void CTreeCtrlRecursionDlg::deleteItems(HTREEITEM hBegin, HTREEITEM hEnd)
{
    auto hItem = hBegin ? hBegin : m_tree.GetRootItem();

    while (hItem && hItem != hEnd) {
        
        if (m_tree.ItemHasChildren(hItem)) {
            auto hChild = m_tree.GetChildItem(hItem);
            deleteItems(hChild, hEnd);
        }

        auto hDel = hItem; // 暂存要删除的节点

        hItem = m_tree.GetNextSiblingItem(hItem);

        auto strText = m_tree.GetItemText(hDel);
        putLog(_T("正在删除节点：") + strText);
        m_tree.DeleteItem(hDel);
    }
}

void CTreeCtrlRecursionDlg::printItems(HTREEITEM hBegin, HTREEITEM hEnd,
    UINT uIndent, UINT uCurIndent)
{
    auto hItem = hBegin ? hBegin : m_tree.GetRootItem();

    while (hItem && hItem != hEnd) {
        auto strItemText = m_tree.GetItemText(hItem);
        CString strIndent(_T('.'), uCurIndent * uIndent);
        putLog(strIndent + strItemText);

        if (m_tree.ItemHasChildren(hItem)) {
            auto hChild = m_tree.GetChildItem(hItem);
            ++uCurIndent;
            printItems(hChild, hEnd, uIndent, uCurIndent);
            --uCurIndent;
        }

        hItem = m_tree.GetNextSiblingItem(hItem);
        
    }
}

void CTreeCtrlRecursionDlg::BFS_Check()
{
    queue<HTREEITEM> q;
    auto hRoot = m_tree.GetRootItem();
    // 根节点及其兄弟节点入队列
    while (hRoot) {
        q.push(hRoot);
        hRoot = m_tree.GetNextSiblingItem(hRoot);
    }

    while (!q.empty()) {
        // 取出队首节点进行操作处理
        auto hCur = q.front();
        q.pop();

        BOOL bCheck = m_tree.GetCheck(hCur);
        m_tree.SetCheck(hCur, !bCheck); // 勾选/取消

        CString strLog;
        strLog.Format(_T("当前节点：%s (%s -> %s)"),
            m_tree.GetItemText(hCur),
            check_status[bCheck],
            check_status[1 - bCheck]);
        putLog(strLog);

        // 子节点入队列
        auto hChild = m_tree.GetChildItem(hCur);
        while (hChild) {
            q.push(hChild);
            hChild = m_tree.GetNextSiblingItem(hChild);
        }
    }
}

void CTreeCtrlRecursionDlg::DFS_I_Check()
{
    stack<HTREEITEM> s;
    auto hRoot = m_tree.GetRootItem();
    // 根节点及其兄弟节点入栈
    while (hRoot) {
        s.push(hRoot);
        hRoot = m_tree.GetNextSiblingItem(hRoot);
    }

    while (!s.empty()) {
        // 取出栈顶节点进行操作处理
        auto hCur = s.top();
        s.pop();

        BOOL bCheck = m_tree.GetCheck(hCur);
        m_tree.SetCheck(hCur, !bCheck); // 勾选/取消

        CString strLog;
        strLog.Format(_T("当前节点：%s (%s -> %s)"),
            m_tree.GetItemText(hCur),
            check_status[bCheck],
            check_status[1 - bCheck]);
        putLog(strLog);

        // 子节点入栈
        auto hChild = m_tree.GetChildItem(hCur);
        while (hChild) {
            s.push(hChild);
            hChild = m_tree.GetNextSiblingItem(hChild);
        }
    }
}

void CTreeCtrlRecursionDlg::DFS_R_Check(HTREEITEM hItem)
{
    hItem = hItem ? hItem : m_tree.GetRootItem();
    while (hItem) {
        BOOL bCheck = m_tree.GetCheck(hItem);
        m_tree.SetCheck(hItem, !bCheck);

        CString strLog;
        strLog.Format(_T("当前节点：%s (%s -> %s)"),
            m_tree.GetItemText(hItem),
            check_status[bCheck],
            check_status[1 - bCheck]);
        putLog(strLog);

        if (m_tree.ItemHasChildren(hItem)) {
            auto hChild = m_tree.GetChildItem(hItem);
            DFS_R_Check(hChild);
        }
        
        hItem = m_tree.GetNextSiblingItem(hItem);
    }
}

void CTreeCtrlRecursionDlg::putLog(LPCTSTR szLineLog)
{
    auto nLen = m_editlogger.GetWindowTextLength();
    m_editlogger.SetSel(nLen, nLen);
    m_editlogger.ReplaceSel(CString(szLineLog) + _T("\r\n"));
}

void CTreeCtrlRecursionDlg::OnBnClickedBtnReset()
{
    // TODO: 在此添加控件通知处理程序代码
    m_tree.DeleteAllItems();
    InitTree();
}


void CTreeCtrlRecursionDlg::OnBnClickedBtnExecute()
{
    // TODO: 在此添加控件通知处理程序代码
    if (!UpdateData())
        return;

    auto hBegin = m_tree.GetSelectedItem();
    auto hEnd = m_tree.GetNextSiblingItem(hBegin);

    if (m_nOption == 0) {

        if (m_strFind.Trim().IsEmpty()) {
            AfxMessageBox(_T("查找内容不能为空"));
            GetDlgItem(IDC_EDIT_FIND)->SetFocus();
            return;
        }

        putLog(_T("===>开始查找：") + m_strFind);

        auto hFind = findItem(m_strFind, hBegin, hEnd);
        
        auto strRet = m_tree.GetItemText(hFind);
        putLog(_T("=======结 果======="));
        putLog(hFind ? strRet : _T("*未找到*"));

    } else if (m_nOption == 1) {
  
        putLog(hBegin ? _T("===>开始递归删除当前节点下所有节点") :
            _T("===>当前未选中节点，将全部删除"));

        deleteItems(hBegin, hEnd);

        putLog(_T("=======删除结束======"));

    } else if (m_nOption == 2) {

        putLog(_T("===>开始打印节点"));
        printItems(hBegin, hEnd, m_uIndent);
        putLog(_T("=======打印结束======"));
    } else if (m_nOption == 3) {

        putLog(_T("===>开始广度优先搜索勾选/取消节点"));
        BFS_Check();
        putLog(_T("=======搜索结束======"));
        
    } else if (m_nOption == 4) {
        
        putLog(_T("===>开始深度优先搜索（迭代版）勾选/取消节点"));
        DFS_I_Check();
        putLog(_T("=======搜索结束======"));

    } else {
        
        putLog(_T("===>开始深度优先搜索（递归版）勾选/取消节点"));
        DFS_R_Check();
        putLog(_T("=======搜索结束======"));

    }
}


void CTreeCtrlRecursionDlg::OnBnClickedBtnClear()
{
    // TODO: 在此添加控件通知处理程序代码
    m_editlogger.SetWindowText(_T(""));
}
