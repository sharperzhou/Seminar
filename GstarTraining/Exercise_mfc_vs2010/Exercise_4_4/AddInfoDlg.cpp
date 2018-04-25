// AddInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_4_4.h"
#include "AddInfoDlg.h"
#include "afxdialogex.h"


// CAddInfoDlg 对话框

IMPLEMENT_DYNAMIC(CAddInfoDlg, CDialogEx)

CAddInfoDlg::CAddInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddInfoDlg::IDD, pParent)
    , m_strName(_T(""))
    , m_strSex(_T(""))
    , m_strAge(_T(""))
    , m_strAddr(_T(""))
{

}

CAddInfoDlg::~CAddInfoDlg()
{
}

void CAddInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_NAME_EDT, m_strName);
    DDX_Text(pDX, IDC_AGE_EDT, m_strAge);
    DDX_Text(pDX, IDC_ADDR_EDT, m_strAddr);
    DDX_CBString(pDX, IDC_SEX_COMBO, m_strSex);
}


BEGIN_MESSAGE_MAP(CAddInfoDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CAddInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddInfoDlg 消息处理程序


BOOL CAddInfoDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    SetDlgItemText(IDC_ID_EDT, _T("(自动编号)"));

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void CAddInfoDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码

    CDialogEx::OnOK();
}
