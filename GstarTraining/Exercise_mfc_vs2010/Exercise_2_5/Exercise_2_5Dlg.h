
// Exercise_2_5Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

struct PersonInfo
{
    CString strName;
    CString strSex;
    int iAge;
};


// CExercise_2_5Dlg 对话框
class CExercise_2_5Dlg : public CDialogEx
{
// 构造
public:
	CExercise_2_5Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_2_5_DIALOG };

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
    CTreeCtrl m_treeInfo;
    PersonInfo personInfo[2];
public:
    afx_msg void OnNMClickInfoTree(NMHDR *pNMHDR, LRESULT *pResult);
};
