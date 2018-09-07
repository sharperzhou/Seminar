// ImageViewerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ImgView.h"


// CImageViewerDlg 对话框
class CImageViewerDlg : public CDialog
{
// 构造
public:
	CImageViewerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IMAGEVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
    HACCEL m_hAccel;
    CListCtrl m_listPreview;
    CImageList m_imageList;
    CImgView m_staticView;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnOpen();
    afx_msg void OnLvnItemchangedListPreview(NMHDR *pNMHDR, LRESULT *pResult);
};
