
// Exercise_3_5Doc.cpp : CExercise_3_5Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exercise_3_5.h"
#endif

#include "Exercise_3_5Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExercise_3_5Doc

IMPLEMENT_DYNCREATE(CExercise_3_5Doc, CDocument)

BEGIN_MESSAGE_MAP(CExercise_3_5Doc, CDocument)
END_MESSAGE_MAP()


// CExercise_3_5Doc 构造/析构

CExercise_3_5Doc::CExercise_3_5Doc()
{
	// TODO: 在此添加一次性构造代码

}

CExercise_3_5Doc::~CExercise_3_5Doc()
{
}

BOOL CExercise_3_5Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CExercise_3_5Doc 序列化

void CExercise_3_5Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
        int iCount = m_aPoint.GetSize();
        ar << iCount;
        for (int i = 0; i < iCount; ++i)
            ar << m_aPoint[i];
	}
	else
	{
		// TODO: 在此添加加载代码
        m_aPoint.RemoveAll();
        int iCount;
        CPoint pt;
        ar >> iCount;
        for (int i = 0; i < iCount; ++i) {
            ar >> pt;
            m_aPoint.Add(pt);
        }
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CExercise_3_5Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CExercise_3_5Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CExercise_3_5Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CExercise_3_5Doc 诊断

#ifdef _DEBUG
void CExercise_3_5Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExercise_3_5Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CExercise_3_5Doc 命令
