
// Exercise_3_3Dlg.h : 头文件
//

#pragma once


// CExercise_3_3Dlg 对话框
class CExercise_3_3Dlg : public CDialogEx
{
// 构造
public:
	CExercise_3_3Dlg(CWnd* pParent = NULL);	// 标准构造函数
    ~CExercise_3_3Dlg();

// 对话框数据
	enum { IDD = IDD_EXERCISE_3_3_DIALOG };

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
private:
    HBITMAP m_hBitmap;
    int m_cx, m_cy;
    int m_cxBmp, m_cyBmp;
private:
    BOOL SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpszFileName);
};
