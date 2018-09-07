// ImgView.cpp : 实现文件
//

#include "stdafx.h"
#include <atlimage.h>
#include "ImageViewer.h"
#include "ImgView.h"



// CImgView

IMPLEMENT_DYNAMIC(CImgView, CStatic)

CImgView::CImgView()
{

}

CImgView::~CImgView()
{
}


BEGIN_MESSAGE_MAP(CImgView, CStatic)
    ON_WM_PAINT()
END_MESSAGE_MAP()



// CImgView 消息处理程序


bool CImgView::Load(LPCTSTR lpszFileName)
{
    if (m_bmp.m_hObject)
        m_bmp.DeleteObject();
    CImage img;
    bool bRet = false;

    HRESULT hr = img.Load(lpszFileName);
    if (SUCCEEDED(hr)) {
        bRet = m_bmp.Attach(img.Detach()) == TRUE;
    }

    return bRet;
}

bool CImgView::Attach(HBITMAP hBmp)
{
    m_bmp.DeleteObject();
    return m_bmp.Attach(hBmp) == TRUE;
}

HBITMAP CImgView::Detach()
{
    return (HBITMAP) m_bmp.Detach();
}
void CImgView::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CStatic::OnPaint()
    HBITMAP hBmp = stretchImage(m_bmp, cx, cy);
    
    if (hBmp != NULL) {
        CBitmap bmp;
        bmp.Attach(hBmp);

        CDC memDC;
        memDC.CreateCompatibleDC(&dc);
        memDC.SelectObject(&bmp);

        dc.BitBlt(0, 0, cx, cy, &memDC, 0, 0, SRCCOPY);
    }
}

void CImgView::PreSubclassWindow()
{
    // TODO: 在此添加专用代码和/或调用基类
    CRect rc;
    GetClientRect(&rc);

    cx = rc.Width();
    cy = rc.Height();

    CStatic::PreSubclassWindow();
}
