
// Exercise_1_2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CExercise_1_2Dlg 对话框
class CExercise_1_2Dlg : public CDialogEx
{
// 构造
public:
	CExercise_1_2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_Exercise_1_2_DIALOG };

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
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedRemoveBtn();
	afx_msg void OnBnClickedAddallBtn();
	afx_msg void OnBnClickedClearBtn();
private:
	CListBox m_StuInfoField;
	CListBox m_ReportField;
};
