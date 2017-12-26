
// Exercise_2_2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CExercise_2_2Dlg 对话框
class CExercise_2_2Dlg : public CDialogEx
{
// 构造
public:
	CExercise_2_2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_2_2_DIALOG };

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
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
    int m_iSpeed;
    int m_iColor[3];
    CBrush m_hbrCtl;
};
