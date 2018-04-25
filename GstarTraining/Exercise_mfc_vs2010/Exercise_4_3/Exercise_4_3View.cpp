
// Exercise_4_3View.cpp : CExercise_4_3View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exercise_4_3.h"
#endif

#include "Exercise_4_3Doc.h"
#include "Exercise_4_3View.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_4_3View

IMPLEMENT_DYNCREATE(CExercise_4_3View, CView)

BEGIN_MESSAGE_MAP(CExercise_4_3View, CView)
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CExercise_4_3View 构造/析构

CExercise_4_3View::CExercise_4_3View()
{
	// TODO: 在此处添加构造代码

}

CExercise_4_3View::~CExercise_4_3View()
{
}

BOOL CExercise_4_3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CExercise_4_3View 绘制

void CExercise_4_3View::OnDraw(CDC* /*pDC*/)
{
	CExercise_4_3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CExercise_4_3View 诊断

#ifdef _DEBUG
void CExercise_4_3View::AssertValid() const
{
	CView::AssertValid();
}

void CExercise_4_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExercise_4_3Doc* CExercise_4_3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExercise_4_3Doc)));
	return (CExercise_4_3Doc*)m_pDocument;
}
#endif //_DEBUG


// CExercise_4_3View 消息处理程序


void CExercise_4_3View::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CString strBuf;
    strBuf.Format(_T("x=%d, y=%d"), point.x, point.y);
    ((CMainFrame*) GetParent())->m_wndStatusBar.SetPaneText(1, strBuf);

    CView::OnMouseMove(nFlags, point);
}
