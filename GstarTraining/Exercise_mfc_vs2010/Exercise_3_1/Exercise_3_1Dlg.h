
// Exercise_3_1Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CExercise_3_1Dlg 对话框
class CExercise_3_1Dlg : public CDialogEx
{
// 构造
public:
	CExercise_3_1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_3_1_DIALOG };

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
    CProgressCtrl m_process;
    int m_iPos;
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy();
};
