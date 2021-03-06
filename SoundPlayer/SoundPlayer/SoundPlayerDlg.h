
// SoundPlayerDlg.h: 头文件
//

#pragma once
#include "CWMPPlayer4.h"

// CSoundPlayerDlg 对话框
class CSoundPlayerDlg : public CDialogEx
{
// 构造
public:
	CSoundPlayerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOUNDPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
    HACCEL m_hAccel;
    CWMPPlayer4 m_wmpPlayer;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
    afx_msg void OnOpen();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    DECLARE_EVENTSINK_MAP()
    void PlayStateChangeMediaPlayer(long NewState);
public:
    afx_msg void OnMcilen();
};
