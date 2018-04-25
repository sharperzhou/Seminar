
// Exercise_2_3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CExercise_2_3Dlg 对话框
class CExercise_2_3Dlg : public CDialogEx
{
// 构造
public:
	CExercise_2_3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_2_3_DIALOG };

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
    afx_msg void OnBnClickedSetfontBtn();

private:
    CFont m_Font;
    CString m_strFontName;
    COLORREF m_clr;
    CBrush m_clrBrush;
    CStatic m_ResultCtl;
public:
    afx_msg void OnBnClickedSetclrBtn();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
