
// Exercise_3_5View.h : CExercise_3_5View 类的接口
//

#pragma once


class CExercise_3_5View : public CView
{
protected: // 仅从序列化创建
	CExercise_3_5View();
	DECLARE_DYNCREATE(CExercise_3_5View)

// 特性
public:
	CExercise_3_5Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CExercise_3_5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exercise_3_5View.cpp 中的调试版本
inline CExercise_3_5Doc* CExercise_3_5View::GetDocument() const
   { return reinterpret_cast<CExercise_3_5Doc*>(m_pDocument); }
#endif

