// FileTreeDialog.h : header file
//

#pragma once
#include <filesystem>

// FileTreeDialog dialog
class FileTreeDialog : public CDialogEx
{
    // Construction
public:
    FileTreeDialog(CWnd* pParent = nullptr); // standard constructor

    /**
     * \brief 获取内容视图
     * \return 内容视图
     */
    const CString& GetContentRef() const;

    // Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILETREE_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
DECLARE_MESSAGE_MAP()
    CString m_pathString;
    CTreeCtrl m_tree;
    CString m_content;
    CFont m_contentEditFont;
    CSpinButtonCtrl m_levelSpin;

    afx_msg void OnChooseFolder();
    afx_msg void OnShowLayout();

private:
    void LoadFileTree(const std::filesystem::path& parent, HTREEITEM hParent = nullptr);
    void Print(HTREEITEM item, int level = 1, CString pre = L"");
};
