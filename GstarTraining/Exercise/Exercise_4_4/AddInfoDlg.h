#pragma once

class CExercise_4_4Dlg;
// CAddInfoDlg 对话框

class CAddInfoDlg : public CDialogEx
{
    friend CExercise_4_4Dlg;
	DECLARE_DYNAMIC(CAddInfoDlg)

public:
	CAddInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddInfoDlg();

// 对话框数据
	enum { IDD = IDD_ADDINFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
private:
    CString m_strName;
    CString m_strSex;
    CString m_strAge;
    CString m_strAddr;
public:
    afx_msg void OnBnClickedOk();
   
};
