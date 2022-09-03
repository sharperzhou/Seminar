// FileTreeDialog.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FileTree.h"
#include "FileTreeDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// FileTreeDialog dialog


FileTreeDialog::FileTreeDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_FILETREE_DIALOG, pParent)
      , m_pathString(_T(""))
      , m_content(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

const CString& FileTreeDialog::GetContentRef() const
{
    return m_content;
}

void FileTreeDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_ROOTPATH, m_pathString);
    DDX_Control(pDX, IDC_TREE, m_tree);
    DDX_Text(pDX, IDC_EDIT_CONTENT, m_content);
    DDX_Control(pDX, IDC_SPIN_LEVEL, m_levelSpin);
}

BEGIN_MESSAGE_MAP(FileTreeDialog, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_CHOOSEFOLDER, &FileTreeDialog::OnChooseFolder)
    ON_BN_CLICKED(IDC_BTN_SHOW, &FileTreeDialog::OnShowLayout)
END_MESSAGE_MAP()


// FileTreeDialog message handlers

BOOL FileTreeDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE); // Set big icon
    SetIcon(m_hIcon, FALSE); // Set small icon

    // TODO: Add extra initialization here
    m_levelSpin.SetRange(1, 999);
    m_levelSpin.SetPos(1);

    auto* dlgFont = GetFont();
    LOGFONT lf = {0};
    dlgFont->GetLogFont(&lf);
    _tcscpy_s(lf.lfFaceName, L"Consolas");
    m_contentEditFont.CreateFontIndirect(&lf);

    auto* contentEdit = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CONTENT));
    contentEdit->SetFont(&m_contentEditFont);
    contentEdit->SetLimitText(0);

    return TRUE; // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void FileTreeDialog::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR FileTreeDialog::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void FileTreeDialog::OnChooseFolder()
{
    // TODO: Add your control notification handler code here
    CFolderPickerDialog folderDialog{m_pathString, 0, this};
    if (folderDialog.DoModal() != IDOK) return;

    m_pathString = folderDialog.GetPathName();
    UpdateData(FALSE);

    m_tree.DeleteAllItems();
    LoadFileTree(static_cast<LPCTSTR>(m_pathString));
}


void FileTreeDialog::OnShowLayout()
{
    // TODO: Add your control notification handler code here
    m_content.Empty();
    auto* selectedItem = m_tree.GetSelectedItem();
    m_content += (selectedItem == nullptr
                      ? std::filesystem::path(static_cast<LPCTSTR>(m_pathString)).filename().wstring().data()
                      : m_tree.GetItemText(selectedItem)) + CString(L"\r\n");
    Print(m_tree.GetChildItem(selectedItem == nullptr ? TVI_ROOT : selectedItem));
    UpdateData(FALSE);
}

void FileTreeDialog::LoadFileTree(const std::filesystem::path& parent, HTREEITEM hParent)
{
	std::error_code err;
    for (auto&& entry : std::filesystem::directory_iterator(parent, err))
    {
        const auto& child = entry.path();
        auto* newItem = m_tree.InsertItem(child.filename().wstring().data(), hParent);
        if (entry.is_directory(err))
            LoadFileTree(child, newItem);
        m_tree.Expand(newItem, TVE_EXPAND);
    }
}

void FileTreeDialog::Print(HTREEITEM item, int level, CString pre)
{
    while (item != nullptr && level < m_levelSpin.GetPos())
    {
        const auto name = m_tree.GetItemText(item);
        auto* nextItem = m_tree.GetNextSiblingItem(item);
        m_content += pre + (nextItem == nullptr ? L"└── " : L"├── ") + name + L"\r\n";
        Print(m_tree.GetChildItem(item), level + 1, pre + (nextItem == nullptr ? L"    " : L"│   "));
        item = nextItem;
    }
}
