#pragma once
#include <acuiEdit.h>
#include <acuiComboBox.h>
#include "GridCtrl_src/GridCtrl.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "ArxProjectHelper.h"

// CInsertTableDlg 对话框

class CInsertTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertTableDlg)

public:
	CInsertTableDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInsertTableDlg();

// 对话框数据
	enum { IDD = IDD_INSERTTABLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

    //数据变量
private:
    CArxProjectHelper::TableContent m_aTableContent;
    AcDbObjectId m_TextStyleId;
    double m_dTextHeight;
    double m_dWidthFactor;
    AcCmColor m_TextColor;
    int m_iRowNum;
    int m_iColumnNum;
    AcDb::CellAlignment m_CellAlignment;
    AcDb::LineWeight m_LineWeight;
    AcDbObjectId m_LineTypeId;
    AcCmColor m_LineColor;
    AcDbObjectIdArray m_aTextStyleId;

    //控件变量
private:
    CGridCtrl m_gridContent;
    CComboBox m_comboTextStyle;
    CAcUiNumericEdit m_editTextHeight;
    CAcUiNumericEdit m_editTextWidthFactor;
    CAcUiTrueColorComboBox m_comboTextColor;
    CComboBox m_comboAlignment;
    CAcUiLineWeightComboBox m_comboLineWidth;
    CAcUiLineTypeComboBox m_comboLineType;
    CAcUiTrueColorComboBox m_comboLineColor;

    //属性
public:
    const CArxProjectHelper::TableContent&
        getTableContent() const                              {return m_aTableContent;}
    const AcDbObjectId& getTextStyle() const                 {return m_TextStyleId;  }
    double getTextHeight() const                             {return m_dTextHeight;  }
    double getTextWidthFactor() const                        {return m_dWidthFactor; }
    const AcCmColor& getTextColor() const                    {return m_TextColor;    }
    int getRowCount() const                                  {return m_iRowNum;      }
    int getColumnCount() const                               {return m_iColumnNum;   }
    AcDb::CellAlignment getCellAlignment() const             {return m_CellAlignment;}
    AcDb::LineWeight getLineWeight() const                   {return m_LineWeight;   }
    const AcDbObjectId& getLineType() const                  {return m_LineTypeId;   }
    const AcCmColor& getLineColor() const                    {return m_LineColor;    }

private:
    // 对话框弹出时初始化控件
    void InitCtrl(void);
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
public:
    afx_msg void OnEnUpdateTableRownum();
    afx_msg void OnEnUpdateTableColumnnum();
    afx_msg void OnEnKillfocusTextHeight();
    afx_msg void OnEnKillfocusTextWidthfactor();
};

