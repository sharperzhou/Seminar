
// Exercise_4_1Dlg.h : 头文件
//

#pragma once
#include "colorlistbox.h"


// CExercise_4_1Dlg 对话框
class CExercise_4_1Dlg : public CDialogEx
{
// 构造
public:
	CExercise_4_1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_4_1_DIALOG };

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
    CColorListBox m_listbox;
};
