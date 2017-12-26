
// Exercise_4_3View.h : CExercise_4_3View 类的接口
//

#pragma once


class CExercise_4_3View : public CView
{
protected: // 仅从序列化创建
	CExercise_4_3View();
	DECLARE_DYNCREATE(CExercise_4_3View)

// 特性
public:
	CExercise_4_3Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CExercise_4_3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exercise_4_3View.cpp 中的调试版本
inline CExercise_4_3Doc* CExercise_4_3View::GetDocument() const
   { return reinterpret_cast<CExercise_4_3Doc*>(m_pDocument); }
#endif

