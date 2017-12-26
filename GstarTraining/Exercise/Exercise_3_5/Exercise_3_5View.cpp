
// Exercise_3_5View.cpp : CExercise_3_5View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exercise_3_5.h"
#endif

#include "Exercise_3_5Doc.h"
#include "Exercise_3_5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_3_5View

IMPLEMENT_DYNCREATE(CExercise_3_5View, CView)

BEGIN_MESSAGE_MAP(CExercise_3_5View, CView)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CExercise_3_5View 构造/析构

CExercise_3_5View::CExercise_3_5View()
{
	// TODO: 在此处添加构造代码

}

CExercise_3_5View::~CExercise_3_5View()
{
}

BOOL CExercise_3_5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CExercise_3_5View 绘制

void CExercise_3_5View::OnDraw(CDC* pDC)
{
	CExercise_3_5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
    CRect rc;
    GetClientRect(rc);
    pDC->DrawText(_T("鼠标单击以半径10画圆，【文件-保存】命令将所有单击的点保存为*.dots文件，")
        _T("【文件-打开】命令所有点的信息读取并进行重画。"), rc, DT_WORDBREAK);

    //pDC->SetBkMode(TRANSPARENT);
    HBRUSH hbrOld = (HBRUSH) pDC->SelectObject(GetStockObject(NULL_BRUSH));
    int iCount = pDoc->m_aPoint.GetSize();
    int xpt, ypt;
    for (int i = 0; i < iCount; ++i) {
        xpt = pDoc->m_aPoint[i].x, ypt = pDoc->m_aPoint[i].y;
        pDC->Ellipse(xpt-10, ypt-10, xpt+10, ypt+10);
    }
    pDC->SelectObject(hbrOld);
}


// CExercise_3_5View 诊断

#ifdef _DEBUG
void CExercise_3_5View::AssertValid() const
{
	CView::AssertValid();
}

void CExercise_3_5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExercise_3_5Doc* CExercise_3_5View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExercise_3_5Doc)));
	return (CExercise_3_5Doc*)m_pDocument;
}
#endif //_DEBUG


// CExercise_3_5View 消息处理程序


void CExercise_3_5View::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CExercise_3_5Doc *pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    pDoc->m_aPoint.Add(point);

    Invalidate();

    CView::OnLButtonDown(nFlags, point);
}
