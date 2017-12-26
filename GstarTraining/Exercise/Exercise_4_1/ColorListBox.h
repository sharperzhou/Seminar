#pragma once


// CColorListBox

class CColorListBox : public CListBox
{
	DECLARE_DYNAMIC(CColorListBox)

public:
	CColorListBox();
	virtual ~CColorListBox();

protected:
	DECLARE_MESSAGE_MAP()
private:
    virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
    virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

public:
    void AddItemIconColor(COLORREF clrIcon);
    void SetIconWidth(int width = 20);
    void SetHighlightColor(COLORREF clrHighlight);

private:
    CArray<COLORREF> m_clrIconArray;
    int m_nIconWidth;
    COLORREF m_clrHighlight;

private:
    afx_msg void OnLbnSelchange();
public:
    afx_msg void OnKillFocus(CWnd* pNewWnd);
};


