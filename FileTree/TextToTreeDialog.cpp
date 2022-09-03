// TextToTreeDialog.cpp : implementation file
//

#include "pch.h"
#include "FileTree.h"
#include "TextToTreeDialog.h"

#include <memory>
#include <unordered_map>

#include "afxdialogex.h"


// TextToTreeDialog dialog

IMPLEMENT_DYNAMIC(TextToTreeDialog, CDialogEx)

TextToTreeDialog::TextToTreeDialog(const CString& content, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TEXTTOTREE_DIALOG, pParent),
      m_contentRef(content)
{
}

TextToTreeDialog::~TextToTreeDialog()
{
}

void TextToTreeDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_CONTENT2, m_content);
    DDX_Control(pDX, IDC_TREE2, m_tree);
}


BEGIN_MESSAGE_MAP(TextToTreeDialog, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_TEXT_TO_TREE, &TextToTreeDialog::OnClickedButtonTextToTree)
END_MESSAGE_MAP()


// TextToTreeDialog message handlers


void TextToTreeDialog::OnClickedButtonTextToTree()
{
    // TODO: Add your control notification handler code here
    m_tree.DeleteAllItems();

    // { level(indent) => node }
    std::unordered_map<int, HTREEITEM> cache{{-1, TVI_ROOT}};
    for (auto l = 0; l < m_content.GetLineCount(); l++)
    {
        // 获取每行的文本长度
        const auto len = m_content.LineLength(m_content.LineIndex(l));
        // Skip empty line
        if (len == 0) continue;
        const auto buffer = std::make_unique<wchar_t[]>(len + 1);
        // 当前行的文本放入 buffer
        m_content.GetLine(l, buffer.get(), len);

        // 通过视图获取特征连接线位置
        std::wstring_view sv{buffer.get(), static_cast<std::size_t>(len)};
        auto pos = sv.find(L"── ");
        pos == std::wstring_view::npos ? pos = 0 : pos += 3;

        // 计算缩进单位，连接线单位宽度为4
        const auto indent = static_cast<int>(pos / 4);

        // 从 cache 中找到父节点，并用新插入的节点更新 cache
        // 其特点为从上至下读入文本，当上一节点及其子节点处理完后，
        // 上一节点的兄弟节点才开始处理，因此在 cache 中覆盖 indent
        // 不会影响后续的处理
        cache[indent] = m_tree.InsertItem(buffer.get() + pos, cache[indent - 1]);
    }
}

BOOL TextToTreeDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  Add extra initialization here
    auto* dlgFont = GetFont();
    LOGFONT lf = {0};
    dlgFont->GetLogFont(&lf);
    _tcscpy_s(lf.lfFaceName, L"Consolas");
    m_contentEditFont.CreateFontIndirect(&lf);

    m_content.SetFont(&m_contentEditFont);

    m_content.SetWindowText(m_contentRef);
    m_content.SetLimitText(0);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
