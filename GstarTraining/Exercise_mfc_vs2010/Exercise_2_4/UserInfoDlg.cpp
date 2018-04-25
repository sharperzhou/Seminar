// UserInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_2_4.h"
#include "UserInfoDlg.h"
#include "afxdialogex.h"


// CUserInfoDlg 对话框

IMPLEMENT_DYNAMIC(CUserInfoDlg, CDialogEx)

CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserInfoDlg::IDD, pParent)
    , m_strName(_T(""))
    , m_strSex(_T(""))
    , m_iAge(0)
{

}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_NAME_EDT, m_strName);
    DDX_Text(pDX, IDC_SEX_EDT, m_strSex);
    DDV_MaxChars(pDX, m_strSex, 1);
    DDX_Text(pDX, IDC_AGE_EDT, m_iAge);
	DDV_MinMaxInt(pDX, m_iAge, 0, 120);
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CUserInfoDlg::OnBnClickedIDOk)
END_MESSAGE_MAP()


// CUserInfoDlg 消息处理程序
void CUserInfoDlg::OnBnClickedIDOk()
{
    if (!UpdateData(TRUE)) return;

    if (m_strName.IsEmpty()) {
        AfxMessageBox(_T("姓名不能为空！"), MB_ICONERROR);
        GetDlgItem(IDC_NAME_EDT)->GetFocus();
        return;
    }

    if (_T("男") != m_strSex && _T("女") != m_strSex) {
        AfxMessageBox(_T("请输入正确的性别，男/女"), MB_ICONERROR);
        GetDlgItem(IDC_SEX_EDT)->GetFocus();
        return;
    }
    
    /*CDialogEx::OnOK();*/
    EndDialog(IDOK);
}