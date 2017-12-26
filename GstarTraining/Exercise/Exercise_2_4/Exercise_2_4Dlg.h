
// Exercise_2_4Dlg.h : 头文件
//

#pragma once


// CExercise_2_4Dlg 对话框
class CExercise_2_4Dlg : public CDialogEx
{
// 构造
public:
	CExercise_2_4Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_2_4_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedShowBtn();

private:
    void SplitString(LPCTSTR szSrc, LPCTSTR szDelim, CStringArray &strArray);

private:
    CString m_strName;
    CString m_strSex;
    int m_iAge;
};
