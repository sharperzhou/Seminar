
// Exercise_5_1Dlg.h : 头文件
//

#pragma once


// CExercise_5_1Dlg 对话框
class CExercise_5_1Dlg : public CDialogEx
{
// 构造
public:
	CExercise_5_1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_5_1_DIALOG };

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
    afx_msg void OnBnClickedLoadBtn();
    afx_msg void OnBnClickedSaveBtn();
    afx_msg void OnPopupMenuClicked(UINT uId);
    afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
    afx_msg void OnSetFocus(CWnd* pOldWnd);

private:
    HANDLE m_hAccel;

public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};
