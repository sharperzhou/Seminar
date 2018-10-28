// TreeCtrlSeriesDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CTreeCtrlSeriesDlg 对话框
class CTreeCtrlSeriesDlg : public CDialog
{
// 构造
public:
	CTreeCtrlSeriesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TREECTRLSERIES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
    CImageList m_imgList;
    CTreeCtrl m_tree;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnSave();
};
