// InsertBlkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "ArxProjectHelper.h"
#include "InsertBlkDlg.h"
#include "afxdialogex.h"


// CInsertBlkDlg 对话框

IMPLEMENT_DYNAMIC(CInsertBlkDlg, CDialogEx)

CInsertBlkDlg::CInsertBlkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInsertBlkDlg::IDD, pParent)
    , m_hBmp(0)
{

}

CInsertBlkDlg::~CInsertBlkDlg()
{
    DeleteObject(m_hBmp);
}

void CInsertBlkDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_BLKNAME, m_comboBlkName);
    DDX_Control(pDX, IDC_LIST_ATTR, m_listAttr);
    DDX_Control(pDX, IDC_EDIT_VALUE, m_editValue);
    DDX_Control(pDX, IDC_PIC, m_pic);
}


BEGIN_MESSAGE_MAP(CInsertBlkDlg, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO_BLKNAME, &CInsertBlkDlg::OnCbnSelchangeComboBlkname)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ATTR, &CInsertBlkDlg::OnLvnItemchangedListAttr)
    ON_EN_CHANGE(IDC_EDIT_VALUE, &CInsertBlkDlg::OnEnChangeEditValue)
    ON_BN_CLICKED(IDOK, &CInsertBlkDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInsertBlkDlg 消息处理程序


BOOL CInsertBlkDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    //设置块属性列表控件的标题及样式
    m_listAttr.InsertColumn(0, _T("标记"), LVCFMT_LEFT, 100);
    m_listAttr.InsertColumn(1, _T("提示"), LVCFMT_LEFT, 100);
    m_listAttr.InsertColumn(2, _T("数值"), LVCFMT_LEFT, 100);
    m_listAttr.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    //设置Combobox显示的块名称
    AcStringArray aGroupName;
    CArxProjectHelper::getSymbolRecord<AcDbBlockTable>(aGroupName);
    int len = aGroupName.length();
    for (int i = 0; i < len; ++i) {
        CString strBuf = aGroupName.at(i).kACharPtr();
        if (strBuf.Compare(ACDB_MODEL_SPACE)
            && strBuf.Compare(ACDB_PAPER_SPACE)
            && strBuf.Compare(_T("*Paper_Space0"))
            && strBuf.Compare(_T("*T"))) {
                m_comboBlkName.AddString(strBuf);
        }
        else {
            continue; //当遇到模型空间、图纸空间和表格，忽略
        }
    }

    //Combobox无项目时将编辑框和确定按钮置灰
    if (-1 == m_comboBlkName.SetCurSel(0)) {
        GetDlgItem(IDOK)->EnableWindow(FALSE);
        m_editValue.EnableWindow(FALSE); 
    }
    else
        OnCbnSelchangeComboBlkname();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void CInsertBlkDlg::OnCbnSelchangeComboBlkname()
{
    CString strBlkName;
    int iCurIndex = m_comboBlkName.GetCurSel();
    if (-1 == iCurIndex) return;

    m_listAttr.DeleteAllItems();

    m_comboBlkName.GetLBText(iCurIndex, strBlkName);
    bool bRet = CArxProjectHelper::getBlockAttribute(m_aBlkAttr, m_blkDefId, strBlkName);
    assert(bRet);
    if (!bRet) return; //获取块定义的Id失败，返回

    //显示块定义的缩略图
    CDC *pDC = m_pic.GetDC();
    BITMAP bmp; //为了获取位图宽高
    CRect rcClient; //为了获取控件宽高
    if (m_hBmp) DeleteObject(m_hBmp);
    m_hBmp = CArxProjectHelper::getBlockPreviewBitmap(m_blkDefId, pDC->GetSafeHdc());
    ::GetObject((HANDLE) m_hBmp, sizeof(BITMAP), (LPVOID) &bmp);
    m_pic.GetClientRect(rcClient);
    m_pic.DrawBitmap(m_hBmp, rcClient.right, rcClient.bottom, bmp.bmWidth, bmp.bmHeight);
    ReleaseDC(pDC);

    if (m_aBlkAttr.IsEmpty()) {
        //无属性时，将编辑框清空并置灰
        m_editValue.EnableWindow(FALSE);
        m_editValue.SetWindowText(_T(""));
        return;
    }
    else {
        m_editValue.EnableWindow(TRUE);
    }

    INT_PTR len = m_aBlkAttr.GetCount();
    for (int i = 0; i < len; ++i) {
        const CArxProjectHelper::BlockAttribute* pBlkAttr = (&m_aBlkAttr.GetAt(i));
        m_listAttr.InsertItem(i, pBlkAttr->getTag());
        m_listAttr.SetItemText(i, 1, pBlkAttr->getPompt());
        m_listAttr.SetItemText(i, 2, pBlkAttr->getTextString());
    }

    //默认第一个属性选中且具有焦点
    m_listAttr.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
}


void CInsertBlkDlg::OnLvnItemchangedListAttr(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    
    if (LVIF_STATE == pNMLV->uChanged) {
        if (LVIS_SELECTED & pNMLV->uNewState) {
            //让编辑框失去焦点，否则下条语句执行时，触发EN_CHANGE事件时编辑框判断
            //有焦点，OnEnChangeEditValue会将边框内容赋给ListCtrl的另一个Item
            m_listAttr.SetFocus();
            m_editValue.SetWindowText(m_listAttr.GetItemText(pNMLV->iItem, 2));
            m_editValue.SetFocus();
            m_editValue.SetSel(0, -1);
        }
    }

    *pResult = 0;
}

void CInsertBlkDlg::OnEnChangeEditValue()
{
    if ((CWnd*) &m_editValue != GetFocus()) return; //编辑框无焦点时不进行操作

    CString strBuf;
    m_editValue.GetWindowText(strBuf);

    //更新块属性列表控件及块属性数组中的属性值（TextString）
    int index = m_listAttr.GetSelectionMark();
    m_listAttr.SetItemText(index, 2, strBuf);
    m_aBlkAttr[index].setTextString(strBuf);
}

void CInsertBlkDlg::OnBnClickedOk()
{
    //检查获取的块定义是否有效（调试用）
    assert(m_blkDefId.isValid());
    CDialogEx::OnOK();
}

