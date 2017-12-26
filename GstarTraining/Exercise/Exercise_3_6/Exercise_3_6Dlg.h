
// Exercise_3_6Dlg.h : 头文件
//

#pragma once


// CExercise_3_6Dlg 对话框
class CExercise_3_6Dlg : public CDialogEx
{
// 构造
public:
	CExercise_3_6Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_3_6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
    NOTIFYICONDATA m_nid;
public:
    afx_msg void OnDestroy();
    afx_msg void OnShow();
    afx_msg void OnExit();
    afx_msg void OnBnClickedOk();
};
