#pragma once


// CImgView

class CImgView : public CStatic
{
	DECLARE_DYNAMIC(CImgView)

public:
	CImgView();
	virtual ~CImgView();

    bool Load(LPCTSTR lpszFileName);
    bool Attach(HBITMAP hBmp);
    HBITMAP Detach();

protected:
    CBitmap m_bmp;
    int cx;
    int cy;
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
protected:
    virtual void PreSubclassWindow();
};


