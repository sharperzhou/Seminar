#pragma once
#include <string_view>

// TextToTreeDialog dialog

class TextToTreeDialog : public CDialogEx
{
DECLARE_DYNAMIC(TextToTreeDialog)

public:
    TextToTreeDialog(const CString& content, CWnd* pParent = nullptr); // standard constructor
    virtual ~TextToTreeDialog();

    // Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTTOTREE_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg void OnClickedButtonTextToTree();

DECLARE_MESSAGE_MAP()
private:
    CEdit m_content;
    CTreeCtrl m_tree;
    CFont m_contentEditFont;
    const CString& m_contentRef;
};
