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
    CComboBox m_comboBlkName; //显示当前图形中所有块定义的名称的组合框
    CListCtrl m_listAttr; //显示组合框所选块定义的属性的列表控件
    CEdit m_editValue; //块定义的属性值的编辑框
    AcDbObjectId m_blkDefId;  //块定义的Id
    CArray<CArxProjectHelper::BlockAttribute> m_aBlkAttr; //某个块定义的属性数组
    CStaticEx m_pic; //派生自静态文本的控件类，用于显示缩略图
private:
    virtual BOOL OnInitDialog();
    afx_msg void OnCbnSelchangeComboBlkname();
    afx_msg void OnLvnItemchangedListAttr(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnChangeEditValue();
    afx_msg void OnBnClickedOk();
};
