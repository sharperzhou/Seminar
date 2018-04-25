
// Exercise_3_7Dlg.h : 头文件
//

#pragma once


// CExercise_3_7Dlg 对话框
class CExercise_3_7Dlg : public CDialogEx
{
// 构造
public:
	CExercise_3_7Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_3_7_DIALOG };

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
    afx_msg void OnBnClickedInstallBtn();
    afx_msg void OnBnClickedUninstallBtn();
    
};
