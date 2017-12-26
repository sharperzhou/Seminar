
// Exercise_4_2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CExercise_4_2Dlg 对话框
class CExercise_4_2Dlg : public CDialogEx
{
// 构造
public:
	CExercise_4_2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_4_2_DIALOG };

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
    CComboBox m_Combo;

private:
    void SetFontAndFontName(int iCtrlId, LPCTSTR szFontName);
public:
    afx_msg void OnCbnSelchangeCombo();
};
