
// Exercise_2_1Dlg.h : 头文件
//

#pragma once


// CExercise_2_1Dlg 对话框
class CExercise_2_1Dlg : public CDialogEx
{
// 构造
public:
	CExercise_2_1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXERCISE_2_1_DIALOG };

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
    int m_iOper;
    double m_dVal1;
    double m_dVal2;
    double m_dResult;
public:
    afx_msg void OnBnClickedCalcBtn();
    virtual void OnOK();
};
