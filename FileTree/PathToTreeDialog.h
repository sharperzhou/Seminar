#pragma once
#include <algorithm>
#include <string_view>
#include <unordered_map>

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
	struct IgnoreCaseHasher
	{
		std::size_t operator()(const CString& s) const noexcept
		{
			std::wstring str;
			std::transform(static_cast<LPCTSTR>(s), static_cast<LPCTSTR>(s) + s.GetLength(), std::back_inserter(str), ::tolower);

			return std::hash<std::wstring>{}(str);
		}
	};
	struct IgnoreCaseEquality
	{
		bool operator()(const CString& l, const CString& r) const noexcept
		{
			return l.CompareNoCase(r) == 0;
		}
	};
	using Cache = std::unordered_map<HTREEITEM, std::unordered_map<CString, HTREEITEM, IgnoreCaseHasher, IgnoreCaseEquality>>;

	CEdit m_content;
	CTreeCtrl m_tree;
	const wchar_t* const WHITE_SPACE = L" \t";
	const wchar_t* const PATH_SEPARATOR = L"/\\";

	afx_msg void OnClickedButtonPathTreeConvert();

	void BuildTree(std::wstring_view& path, Cache& cache, HTREEITEM parent = TVI_ROOT);

	HTREEITEM FindItemNoRecursive(HTREEITEM parent, const CString& text) const;
};
