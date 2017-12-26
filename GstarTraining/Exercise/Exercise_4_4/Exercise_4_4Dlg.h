
// Exercise_4_4Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CExercise_4_4Dlg 对话框
class CExercise_4_4Dlg : public CDialogEx
{
// 构造
public:
	CExercise_4_4Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_4_4_DIALOG };

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
private:
    CListCtrl m_LV;

private:
    BOOL QueryData();
public:
    afx_msg void OnBnClickedAddBtn();
    afx_msg void OnBnClickedRemoveBtn();
};
