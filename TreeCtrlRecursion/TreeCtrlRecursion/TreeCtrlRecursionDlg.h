
// TreeCtrlRecursionDlg.h: 头文件
//

#pragma once


// CTreeCtrlRecursionDlg 对话框
class CTreeCtrlRecursionDlg : public CDialogEx
{
// 构造
public:
	CTreeCtrlRecursionDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TREECTRLRECURSION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:

    const TCHAR* check_status[2]{ _T("✘"), _T("✔") };

	HICON m_hIcon;
    CTreeCtrl m_tree;
    int m_nOption;
    CEdit m_editlogger;
    CString m_strFind;
    UINT m_uIndent;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnBnClickedBtnReset();
    afx_msg void OnBnClickedBtnExecute();
    afx_msg void OnBnClickedBtnClear();

    void InitTree();
    /**
     * \brief 查找指定名称的节点
     * \param szItemName 要查找的树形控件节点名称
     * \param hBegin 开始节点（包含在查询中），当含默认值时，从根节点开始查询
     * \param hEnd 结束节点（不包含在查询中），当为默认值时查询到底
     * \return 查询结果，如果未找到返回NULL
     */
    HTREEITEM findItem(LPCTSTR szItemName, HTREEITEM hBegin = NULL, HTREEITEM hEnd = NULL);
    /**
     * \brief 递归删除节点（含子节点），从子节点开始删
     * \param hBegin 开始节点（包含在查询中），当含默认值时，从根节点开始查询
     * \param hEnd 结束节点（不包含在查询中），当为默认值时查询到底
     */
    void deleteItems(HTREEITEM hBegin = NULL, HTREEITEM hEnd = NULL);
    void printItems(HTREEITEM hBegin = NULL, HTREEITEM hEnd = NULL,
        UINT uIndent = 2, UINT uCurIndent = 0);

    void BFS_Check();
    void DFS_I_Check();
    void DFS_R_Check(HTREEITEM hItem = NULL);

    void putLog(LPCTSTR szLineLog);

	DECLARE_MESSAGE_MAP()
};
