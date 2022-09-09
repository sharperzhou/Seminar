// PathToTreeDialog.cpp : implementation file
//

#include "pch.h"
#include "FileTree.h"
#include "afxdialogex.h"
#include "PathToTreeDialog.h"

#include <memory>


// PathToTreeDialog dialog

IMPLEMENT_DYNAMIC(PathToTreeDialog, CDialogEx)

PathToTreeDialog::PathToTreeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PATHTOTREE_DIALOG, pParent)
{

}

PathToTreeDialog::~PathToTreeDialog()
{
}

void PathToTreeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATh_TREE_PATHS, m_content);
	DDX_Control(pDX, IDC_TREE_PATH_TREE_TREE, m_tree);
}

BOOL PathToTreeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_content.SetLimitText(0);

	return TRUE;
}


BEGIN_MESSAGE_MAP(PathToTreeDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PATH_TREE_CONVERT, &PathToTreeDialog::OnClickedButtonPathTreeConvert)
END_MESSAGE_MAP()


// PathToTreeDialog message handlers


void PathToTreeDialog::OnClickedButtonPathTreeConvert()
{
	// TODO: Add your control notification handler code here
	m_tree.DeleteAllItems();
	Cache cache;
	for (int l = 0; l < m_content.GetLineCount(); l++)
	{
		const auto len = m_content.LineLength(m_content.LineIndex(l));
		if (len == 0) continue;

        const auto buffer = std::make_unique<wchar_t[]>(len + 1);
		m_content.GetLine(l, buffer.get(), len);

        std::wstring_view sv{buffer.get(), static_cast<std::size_t>(len)};
		BuildTree(sv, cache);
	}
}

void PathToTreeDialog::BuildTree(std::wstring_view& path, Cache& cache, HTREEITEM parent)
{
	path.remove_prefix(min(path.find_first_not_of(WHITE_SPACE), path.size()));
	if (path.empty()) return;

	const std::size_t pos = path.find_first_of(PATH_SEPARATOR);
	CString text{&path[0], static_cast<int>(min(pos, path.size()))};
	text.TrimRight();
	if (text.IsEmpty()) return;

	auto& node = cache[parent][text];
	// HTREEITEM node = FindItemNoRecursive(parent, text);
	if (node == nullptr)
	{
		node = m_tree.InsertItem(text, parent, TVI_SORT);
	}

	path.remove_prefix(min(path.find_first_not_of(PATH_SEPARATOR, pos), path.size()));
	BuildTree(path, cache, node);

	m_tree.Expand(node, TVE_EXPAND);
}

HTREEITEM PathToTreeDialog::FindItemNoRecursive(HTREEITEM parent, const CString& text) const
{
	HTREEITEM item = m_tree.GetChildItem(parent);
	while (item != nullptr)
	{
		const CString t = m_tree.GetItemText(item);
		if (t.CompareNoCase(text) == 0)
			break;

		item = m_tree.GetNextSiblingItem(item);
	}

	return item;
}
