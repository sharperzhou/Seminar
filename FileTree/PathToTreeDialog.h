#pragma once
#include <string_view>

#include "afxdialogex.h"


// PathToTreeDialog dialog

class PathToTreeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PathToTreeDialog)

public:
	PathToTreeDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~PathToTreeDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATHTOTREE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_content;
	CTreeCtrl m_tree;
	const wchar_t* const WHITE_SPACE = L" \t";
	const wchar_t* const PATH_SEPARATOR = L"/\\";

	afx_msg void OnClickedButtonPathTreeConvert();

	void BuildTree(std::wstring_view& path, HTREEITEM parent = TVI_ROOT);

	HTREEITEM FindItemNoRecursive(HTREEITEM parent, const CString& text) const;
};
