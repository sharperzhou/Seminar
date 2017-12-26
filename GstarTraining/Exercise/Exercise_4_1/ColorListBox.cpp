// ColorListBox.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_4_1.h"
#include "ColorListBox.h"


// CColorListBox

IMPLEMENT_DYNAMIC(CColorListBox, CListBox)

CColorListBox::CColorListBox() :
    m_nIconWidth(0), m_clrHighlight(0)
{

}

CColorListBox::~CColorListBox()
{
}


BEGIN_MESSAGE_MAP(CColorListBox, CListBox)
    ON_CONTROL_REFLECT(LBN_SELCHANGE, &CColorListBox::OnLbnSelchange)
    ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CColorListBox 消息处理程序




void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{

    // TODO:  添加您的代码以确定指定项的大小
    lpMeasureItemStruct->itemHeight = 20;
}


void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

    // TODO:  添加您的代码以绘制指定项
    CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    CString strBuf;
    GetText(lpDrawItemStruct->itemID, strBuf);

    COLORREF crOldTextColor = pDC->GetTextColor();
    COLORREF crOldBkColor = pDC->GetBkColor();

    CRect rcItem = lpDrawItemStruct->rcItem;
    CRect rcIcon = lpDrawItemStruct->rcItem;
    rcItem.left += m_nIconWidth;
    rcIcon.right = m_nIconWidth;
    rcIcon.top += 1;
    rcIcon.bottom -= 1;


    pDC->SetBkMode(TRANSPARENT);


    if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
        (lpDrawItemStruct->itemState & ODS_SELECTED)) {
            pDC->FillSolidRect(&rcItem, m_clrHighlight ? m_clrHighlight : 
                ::GetSysColor(COLOR_HIGHLIGHT));
            pDC->SetBkColor(m_clrHighlight ? m_clrHighlight : ::GetSysColor(COLOR_HIGHLIGHT));
            //pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
            pDC->FillSolidRect(&rcIcon, m_clrIconArray[lpDrawItemStruct->itemID]);
    }
    else {
        pDC->FillSolidRect(&rcItem, crOldBkColor);
        pDC->FillSolidRect(&rcIcon, m_clrIconArray[lpDrawItemStruct->itemID]);

    }

    if((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
        (lpDrawItemStruct->itemState & ODS_FOCUS)) {
            //pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);
            CPen pen, *pOldPen;
            pen.CreatePen(PS_DOT, 1, RGB(0,0,0));
            pOldPen = pDC->SelectObject(&pen);
            pDC->SelectStockObject(NULL_BRUSH);
            pDC->Rectangle(&lpDrawItemStruct->rcItem);
            pDC->SelectObject(pOldPen);
            pDC->SelectStockObject(WHITE_BRUSH);
    }

    pDC->DrawText(strBuf, &rcItem, DT_VCENTER | DT_SINGLELINE);
    
    pDC->SetTextColor(crOldTextColor);
    pDC->SetBkColor(crOldBkColor);
}

void CColorListBox::AddItemIconColor(COLORREF clrIcon)
{
    m_clrIconArray.Add(clrIcon);
}

void CColorListBox::SetIconWidth(int width /* = 20 */)
{
    m_nIconWidth = width;
}

void CColorListBox::SetHighlightColor(COLORREF clrHighlight)
{
    m_clrHighlight = clrHighlight;
}


void CColorListBox::OnLbnSelchange()
{
    // TODO: 在此添加控件通知处理程序代码
    Invalidate();
}


void CColorListBox::OnKillFocus(CWnd* pNewWnd)
{
    CListBox::OnKillFocus(pNewWnd);

    // TODO: 在此处添加消息处理程序代码
    Invalidate();
}
