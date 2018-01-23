//////////////////////////////////////////////////////////////////////////
// 用于显示块定义预览图的控件类，使用AcGs类实现
//
//////////////////////////////////////////////////////////////////////////

#pragma once


// CStaticEx

class CStaticEx : public CStatic
{
	DECLARE_DYNAMIC(CStaticEx)

public:
	CStaticEx();
	virtual ~CStaticEx();

public:
    //----------------------------------------------------------
    // Summary:
    //    初始化Model、View和Device
    // Parameter:
    // Returns:
    //    BOOL
    //----------------------------------------------------------
    BOOL Init();

    //----------------------------------------------------------
    // Summary:
    //    预览块图标
    // Parameter:
    //    lpszBlockName - 块名称
    // Returns:
    //    void
    //----------------------------------------------------------
    void PreviewIcon(LPCTSTR lpszBlockName = ACDB_MODEL_SPACE);

protected:
	DECLARE_MESSAGE_MAP()

private:
    afx_msg void OnPaint();
    
private:
    AcGsView *m_pView;
    AcGsDevice *m_pDevice;
    AcGsModel *m_pModel;
};


