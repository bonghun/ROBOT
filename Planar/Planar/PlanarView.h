
// PlanarView.h : interface of the CPlanarView class
//

#pragma once


class CPlanarView : public CView
{
protected: // create from serialization only
	CPlanarView();
	DECLARE_DYNCREATE(CPlanarView)

	// Attributes
public:
	CPlanarDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CPlanarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	void Floor(CRect rect);
	void Planar(CRect rect, double *q);
	void EndEffector(CRect rect, double *p);


};

#ifndef _DEBUG  // debug version in PlanarView.cpp
inline CPlanarDoc* CPlanarView::GetDocument() const
{
	return reinterpret_cast<CPlanarDoc*>(m_pDocument);
}
#endif

