
// Exercise_1_1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CExercise_1_1Dlg 对话框
class CExercise_1_1Dlg : public CDialogEx
{
// 构造
public:
	CExercise_1_1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_1_1_DIALOG };

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
	afx_msg void OnEnChangeTxt1Edt();
private:
	CEdit m_txt1; //Edit Control 1
	CEdit m_txt2; //Edit Control 2
public:
	afx_msg void OnEnChangeTxt2Edt();
};
