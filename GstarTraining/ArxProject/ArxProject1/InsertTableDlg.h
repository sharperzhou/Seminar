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
    CArxProjectHelper::TableContent m_aTableContent; //表格内容，二维数组
    AcDbObjectId m_TextStyleId; //文字样式Id
    double m_dTextHeight; //文字高度
    double m_dWidthFactor; //文字宽度因子
    AcCmColor m_TextColor; //文字颜色
    int m_iRowNum; //表格行数
    int m_iColumnNum; //表格列数
    AcDb::CellAlignment m_CellAlignment; //单元格对齐方式
    AcDb::LineWeight m_LineWeight; //表格线框的线宽
    AcDbObjectId m_LineTypeId; //表格线框的线型Id
    AcCmColor m_LineColor; //表格线框的颜色
    AcDbObjectIdArray m_aTextStyleId; //当前图形所有文字样式的Id数组

    //控件变量
private:
    CGridCtrl m_gridContent; //设定表格内容的表格控件
    CComboBox m_comboTextStyle; //文字样式的组合框控件
    CAcUiNumericEdit m_editTextHeight; //文字高度的编辑框控件
    CAcUiNumericEdit m_editTextWidthFactor; //文字宽度因子的编辑框控件
    CAcUiTrueColorComboBox m_comboTextColor; //文字颜色的组合框控件
    CComboBox m_comboAlignment; //单元格对齐方式的组合框控件
    CAcUiLineWeightComboBox m_comboLineWidth; //表格线宽的组合框控件
    CAcUiLineTypeComboBox m_comboLineType; //表格线型的组合框控件
    CAcUiTrueColorComboBox m_comboLineColor; //表格线框颜色的组合框控件

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
    afx_msg void OnEnUpdateTableRownum();
    afx_msg void OnEnUpdateTableColumnnum();
    afx_msg void OnEnKillfocusTextHeight();
    afx_msg void OnEnKillfocusTextWidthfactor();
};

