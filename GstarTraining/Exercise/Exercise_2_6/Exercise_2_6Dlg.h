
// Exercise_2_6Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CExercise_2_6Dlg 对话框
class CExercise_2_6Dlg : public CDialogEx
{
// 构造
public:
	CExercise_2_6Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_2_6_DIALOG };

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
    CListCtrl m_lvInfo;
};
