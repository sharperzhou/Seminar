
// Exercise_1_3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CExercise_1_3Dlg 对话框
class CExercise_1_3Dlg : public CDialogEx
{
// 构造
public:
	CExercise_1_3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_1_3_DIALOG };

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
	CStatic m_CurItem;
	CComboBox m_Catalog;
	CListBox m_List;
    CArray<CString> m_ArrayFruit;
    CArray<CString> m_ArrayStudyMaterial;
private:
    void InitData();
public:
    afx_msg void OnCbnSelchangeCatalogCombo();
    afx_msg void OnLbnSelchangeListList();
};
