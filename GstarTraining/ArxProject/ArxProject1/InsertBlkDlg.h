#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "staticex.h"

class CArxProject1App;
// CInsertBlkDlg 对话框

class CInsertBlkDlg : public CDialogEx
{
    friend CArxProject1App;

	DECLARE_DYNAMIC(CInsertBlkDlg)

public:
	CInsertBlkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInsertBlkDlg();

// 对话框数据
	enum { IDD = IDD_INSERT_BLK_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
    CComboBox m_comboBlkName;
    CListCtrl m_listAttr;
    CEdit m_editValue;
    AcDbObjectId m_blkDefId;  //块定义的Id
    CArray<CArxProjectHelper::BlockAttribute> m_aBlkAttr;
    HBITMAP m_hBmp;
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnCbnSelchangeComboBlkname();
    afx_msg void OnLvnItemchangedListAttr(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnChangeEditValue();
    afx_msg void OnBnClickedOk();
private:
    CStaticEx m_pic;
};
