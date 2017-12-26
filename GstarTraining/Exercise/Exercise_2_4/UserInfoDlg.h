#pragma once

class CExercise_2_4Dlg;

// CUserInfoDlg 对话框

class CUserInfoDlg : public CDialogEx
{
    friend CExercise_2_4Dlg;

	DECLARE_DYNAMIC(CUserInfoDlg)

public:
	CUserInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserInfoDlg();

// 对话框数据
	enum { IDD = IDD_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedIDOk();
private:
    CString m_strName;
    CString m_strSex;
    int m_iAge;
};
