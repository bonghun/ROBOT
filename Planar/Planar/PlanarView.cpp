
// PlanarView.cpp : implementation of the CPlanarView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Planar.h"
#endif

#include "PlanarDoc.h"
#include "PlanarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanarView

IMPLEMENT_DYNCREATE(CPlanarView, CView)

BEGIN_MESSAGE_MAP(CPlanarView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_NCPAINT()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CPlanarView construction/destruction

CPlanarView::CPlanarView()
{
	// TODO: add construction code here

}

CPlanarView::~CPlanarView()
{
}

BOOL CPlanarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanarView drawing

void CPlanarView::OnDraw(CDC* /*pDC*/)
{
	CPlanarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CPlanarView printing

BOOL CPlanarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPlanarView diagnostics

#ifdef _DEBUG
void CPlanarView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanarDoc* CPlanarView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanarDoc)));
	return (CPlanarDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlanarView message handlers





void CPlanarView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CView::OnPaint() for painting messages
	CRect rect;
	CWnd* pWnd = this->GetParent();
	pWnd->GetWindowRect(&rect);

	Floor(rect);
	//
	double m_p[2] = { 0 };
	EndEffector(rect, m_p);

}

void CPlanarView::Floor(CRect rect)
{
	CPen pen, *oldpen;
	CClientDC dc(this);

	pen.CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	oldpen = dc.SelectObject(&pen);
	dc.MoveTo(0, rect.Height()*0.5);
	dc.LineTo(rect.right, rect.Height()*0.5);
	dc.SelectObject(oldpen);
	pen.DeleteObject();

}

void CPlanarView::EndEffector(CRect rect, double *p)
{
	double radius = 25;
	CClientDC dc(this);
	CPen pen, *oldpen;
	pen.CreatePen(PS_DOT, 3, RGB(255, 0, 0));
	oldpen = dc.SelectObject(&pen);

	int nOriginX = rect.Width()*0.5;
	int nOriginY = rect.Height()*0.5;

	dc.Ellipse(nOriginX - radius*0.5 + p[0],
		nOriginY + radius*0.5 - p[1],
		nOriginX - radius*0.5 + p[0] + radius,
		nOriginY + radius*0.5 - p[1] - radius);

	dc.SelectObject(oldpen);
	pen.DeleteObject();
}

void CPlanarView::Planar(CRect rect, double *q)
{
	CPen pen;
	CClientDC dc(this);

	pen.CreatePen(PS_DOT, 3, RGB(0, 0, 125)); // »¡°£»ö ÆæÀ» 
	CPen* oldPen = dc.SelectObject(&pen);

	double factor = (2.0f * 3.1416f) / 360.0f;
	double rot = q[0];

	int nOriginX = rect.Width() * 0.5;
	int nOriginY = rect.Height() * 0.5;

	CPoint pVertex[4];
	int w = 15, h = 60;
	int rad = 25;

	pVertex[0].x = 0; pVertex[0].y = 0;
	pVertex[1].x = w; pVertex[1].y = 0;
	pVertex[2].x = w; pVertex[2].y = -h;
	pVertex[3].x = 0; pVertex[3].y = -h;

	int X, Y;
	/////LINK 01//
	for (int i = 0; i<4; i++)
	{
		X = (int)(cos(rot) * (pVertex[i].x - w*0.5)
			- sin(rot)*pVertex[i].y) + nOriginX; // +rad*0.5;
		Y = (int)(sin(rot) * (pVertex[i].x - w*0.5)
			+ cos(rot)*pVertex[i].y) + nOriginY; // -rad*0.5;
		pVertex[i] = CPoint(X, Y);
	}

	dc.MoveTo(pVertex[3]);
	for (int i = 0; i < 4; i++)
	{
		dc.LineTo(pVertex[i]);
	}
	//
	//////joint 01////
	dc.Ellipse((nOriginX - rad*0.5), (nOriginY + rad*0.5),
		(nOriginX - rad*0.5) + rad, (nOriginY + rad*0.5)
		- rad);

	dc.SelectObject(oldPen);
	///// link 02////




}