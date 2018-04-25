
// Exercise_3_8Dlg.h : 头文件
//

#pragma once


// CExercise_3_8Dlg 对话框
class CExercise_3_8Dlg : public CDialogEx
{
// 构造
public:
	CExercise_3_8Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_3_8_DIALOG };

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
    CWinThread *m_thread[3];
    int m_nId[3];
    int m_iThreadIndex;
    static ULONG m_ulData;
    static CMutex m_mutex;
    static BOOL m_bDestroy;

private:
    static UINT ThreadFun(LPVOID pParam);
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg LRESULT OnUpdateValue(WPARAM wParam, LPARAM lParam);
    afx_msg void OnDestroy();
};
