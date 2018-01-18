// InsertTableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "InsertTableDlg.h"
#include "afxdialogex.h"

//数字转字母，类似Excel列标题A-Z，AA-ZZ效果
//0,1,2,3对应A,B,C ...
static CString NumToLetter(unsigned short num)
{
    CString str;

    TCHAR key = _T('A');
    short loop = num / 26;
    if (loop > 0) {
        str += NumToLetter(loop - 1);
    }
    key += num % 26;
    str += key;
    return str;
}


// CInsertTableDlg 对话框

IMPLEMENT_DYNAMIC(CInsertTableDlg, CDialog)

CInsertTableDlg::CInsertTableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInsertTableDlg::IDD, pParent)
    , m_iRowNum(4)
    , m_iColumnNum(4)
    , m_dTextHeight(3.5)
    , m_dWidthFactor(1.0)
{

}

CInsertTableDlg::~CInsertTableDlg()
{
}

void CInsertTableDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_GRID, m_gridContent);
    DDX_Control(pDX, IDC_TEXT_STYLE, m_comboTextStyle);
    DDX_Control(pDX, IDC_TEXT_HEIGHT, m_editTextHeight);
    DDX_Control(pDX, IDC_TEXT_WIDTHFACTOR, m_editTextWidthFactor);
    DDX_Control(pDX, IDC_TEXT_COLOR, m_comboTextColor);
    DDX_Text(pDX, IDC_TABLE_ROWNUM, m_iRowNum);
    DDX_Text(pDX, IDC_TABLE_COLUMNNUM, m_iColumnNum);
    DDX_Control(pDX, IDC_TABLE_ALIGNMENT, m_comboAlignment);
    DDX_Control(pDX, IDC_TABLE_LINEWIDTH, m_comboLineWidth);
    DDX_Control(pDX, IDC_TABLE_LINETYPE, m_comboLineType);
    DDX_Control(pDX, IDC_TABLE_LINECOLOR, m_comboLineColor);

    DDV_MinMaxInt(pDX, m_iRowNum, 1, 999);
	DDV_MinMaxInt(pDX, m_iColumnNum, 1, 999);
}


BEGIN_MESSAGE_MAP(CInsertTableDlg, CDialog)
    
    ON_BN_CLICKED(IDOK, &CInsertTableDlg::OnBnClickedOk)
    ON_EN_UPDATE(IDC_TABLE_ROWNUM, &CInsertTableDlg::OnEnUpdateTableRownum)
    ON_EN_UPDATE(IDC_TABLE_COLUMNNUM, &CInsertTableDlg::OnEnUpdateTableColumnnum)
    ON_EN_KILLFOCUS(IDC_TEXT_HEIGHT, &CInsertTableDlg::OnEnKillfocusTextHeight)
    ON_EN_KILLFOCUS(IDC_TEXT_WIDTHFACTOR, &CInsertTableDlg::OnEnKillfocusTextWidthfactor)
END_MESSAGE_MAP()


//对话框弹出时初始化控件
void CInsertTableDlg::InitCtrl(void)
{
    //表格控件初始化
    m_gridContent.SetRowCount(m_iRowNum + 1);
    m_gridContent.SetColumnCount(m_iColumnNum + 1);
    m_gridContent.SetFixedRowCount();
    m_gridContent.SetFixedColumnCount();

    m_gridContent.SetTrackFocusCell(FALSE);

    //设置行标题
    for (int i = 1; i <= m_iRowNum; ++i) {
        CString str;
        str.Format(_T("%d"), i);
        m_gridContent.SetItemText(i, 0, str);
        m_gridContent.SetItemFormat(i, 0, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
    m_gridContent.AutoSizeColumn(0);

    //设置列标题
    for (int j = 1; j <= m_iColumnNum; ++j) {
        m_gridContent.SetItemText(0, j, NumToLetter(j - 1));
        m_gridContent.SetItemFormat(0, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }

    //文字样式组合框初始化
    AcStringArray aStrTextStyle;
    CArxProjectHelper::getSymbolRecord<AcDbTextStyleTable>(aStrTextStyle, m_aTextStyleId);
    for (int i = 0; i < aStrTextStyle.length(); ++i)
        m_comboTextStyle.AddString(aStrTextStyle.at(i).constPtr());
    m_comboTextStyle.SetCurSel(0);

    //设置文字高度和宽高比初始值
    CString str;
    str.Format(_T("%.5G"), m_dTextHeight);
    m_editTextHeight.SetWindowText(str);
    m_editTextHeight.SetStyleMask(AC_ES_NUMERIC | AC_ES_NONEGATIVE);
    m_editTextHeight.SetRange(1e-50, DBL_MAX);
    str.Format(_T("%.5G"), m_dWidthFactor);
    m_editTextWidthFactor.SetWindowText(str);
    m_editTextWidthFactor.SetStyleMask(AC_ES_NUMERIC | AC_ES_NONEGATIVE);
    m_editTextWidthFactor.SetRange(0.01, 100);
    

    //上下微调按钮初始化
    CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_TABLE_ROWNUM_SPIN);
    pSpin->SetRange(1, 999);
    pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_TABLE_COLUMNNUM_SPIN);
    pSpin->SetRange(1, 999);


    //表格对齐方式组合框初始化，并设定ItemData为对其方式枚举值
    TCHAR *szAlignment[] = {_T("左上"), _T("中上"), _T("右上"),
                            _T("左中"), _T("正中"), _T("右中"),
                            _T("左下"), _T("中下"), _T("右下")};
    AcDb::CellAlignment cellAlignment[] = {AcDb::kTopLeft, AcDb::kTopCenter, AcDb::kTopRight,
        AcDb::kMiddleLeft, AcDb::kMiddleCenter, AcDb::kMiddleRight,
        AcDb::kBottomLeft, AcDb::kBottomCenter, AcDb::kBottomRight
    };

    int len = min(sizeof(cellAlignment) / sizeof (AcDb::CellAlignment),
        sizeof(szAlignment) / sizeof(TCHAR*));
    for (int i = 0; i < len; ++i) {
        m_comboAlignment.AddString(szAlignment[i]);
        m_comboAlignment.SetItemData(i, cellAlignment[i]);
    }
    m_comboAlignment.SetCurSel(0);

    //线型组合框初始化
    m_comboLineType.SetCurSel(0);
    
}

BOOL CInsertTableDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    InitCtrl();

    m_gridContent.SetFocus();
    m_gridContent.SetItemState(1, 1, GVIS_FOCUSED | GVIS_SELECTED);

    return FALSE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
void CInsertTableDlg::OnBnClickedOk()
{
    //获取表格控件中的内容
    for (int i = 1; i <= m_iRowNum; ++i) {
        std::vector<CString> aStr;
        for (int j = 1; j <= m_iColumnNum; ++j) {
            aStr.push_back(m_gridContent.GetItemText(i, j));
        }
        m_aTableContent.push_back(aStr);
    }

    //获取文字样式Id
    m_TextStyleId = m_aTextStyleId.at(m_comboTextStyle.GetCurSel());


    //获取文字颜色、对齐方式、线宽、线型和线框颜色
    m_comboTextColor.GetCurrentItemColor(m_TextColor);

    m_CellAlignment = (AcDb::CellAlignment) m_comboAlignment.GetItemData(m_comboAlignment.GetCurSel());

    m_LineWeight = (AcDb::LineWeight) m_comboLineWidth.GetCurrentItemLineWeight();

    m_LineTypeId = m_comboLineType.getOIDCurSel();

    m_comboLineColor.GetCurrentItemColor(m_LineColor);

    CDialogEx::OnOK();
}

//行数更新
void CInsertTableDlg::OnEnUpdateTableRownum()
{
    if (!::IsWindow(m_gridContent.m_hWnd)) return;
    UpdateData();

    int iOldRows = m_gridContent.GetRowCount();

    try {
        m_gridContent.SetRowCount(m_iRowNum + 1);
    }
    catch (CMemoryException &e) {
        e.ReportError();
        return;
    }
    m_iRowNum = m_gridContent.GetRowCount() - 1;
    UpdateData(FALSE);

    CString str;
    for (int i = iOldRows; i <= m_iRowNum; ++i) {
        str.Format(_T("%d"), i);
        m_gridContent.SetItemText(i, 0, str);
        m_gridContent.SetItemFormat(i, 0, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
    m_gridContent.AutoSizeColumn(0);
}

//列数更新
void CInsertTableDlg::OnEnUpdateTableColumnnum()
{
    if (!::IsWindow(m_gridContent.m_hWnd)) return;
    UpdateData();

    int iOldCols = m_gridContent.GetColumnCount();

    try {
        m_gridContent.SetColumnCount(m_iColumnNum + 1);
    }
    catch (CMemoryException &e) {
        e.ReportError();
        return;
    }

    m_iColumnNum = m_gridContent.GetColumnCount() - 1;
    UpdateData(FALSE);

    for (int j = iOldCols; j <= m_iColumnNum; ++j) {
        m_gridContent.SetItemText(0, j, NumToLetter(j - 1));
        m_gridContent.SetItemFormat(0, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
}

//文字高度有效性校验
void CInsertTableDlg::OnEnKillfocusTextHeight()
{
    CString str;
    if (m_editTextHeight.Validate()) {
        m_editTextHeight.GetWindowText(str);
        m_dTextHeight = _tstof(str);
        str.Format(_T("%.5G"), m_dTextHeight);
        m_editTextHeight.SetWindowText(str);
    }
    else {
        AfxMessageBox(_T("高度无效，请输入新值。\n\n(最小值 1.0E-50)"));
        m_editTextHeight.SetFocus();
        str.Format(_T("%.5G"), m_dTextHeight);
        m_editTextHeight.SetWindowText(str);
        m_editTextHeight.SetSel(0, -1);
    }
}

//文字宽高比有效性校验
void CInsertTableDlg::OnEnKillfocusTextWidthfactor()
{
    CString str;
    if (m_editTextWidthFactor.Validate()) {
        m_editTextWidthFactor.GetWindowText(str);
        m_dWidthFactor = _tstof(str);
        str.Format(_T("%.5G"), m_dWidthFactor);
        m_editTextWidthFactor.SetWindowText(str);
    }
    else {
        AfxMessageBox(_T("宽高比无效，请输入新值。\n\n(范围：0.01 到 100.0)"));
        m_editTextWidthFactor.SetFocus();
        str.Format(_T("%.5G"), m_dWidthFactor);
        m_editTextWidthFactor.SetWindowText(str);
        m_editTextWidthFactor.SetSel(0, -1);
    }
}
