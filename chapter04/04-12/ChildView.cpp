
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "DrawLines.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);

	// 클라이언트 영역의 좌표를 얻는다.
	CRect rect;
	GetClientRect(&rect);

	// 수평선과 수직선을 그린다.
	dc.MoveTo(0, rect.bottom / 2);
	dc.LineTo(rect.right, rect.bottom / 2);
	dc.MoveTo(rect.right / 2, 0);
	dc.LineTo(rect.right / 2, rect.bottom);

	// 마름모꼴을 그린다.
	POINT points[] = { {rect.right / 2, 0}, {rect.right, rect.bottom / 2},
		{ rect.right / 2, rect.bottom}, {0, rect.bottom / 2}, {rect.right / 2, 0} };
	dc.Polyline(points, 5);

	dc.SetMapMode(MM_LOMETRIC);
	CSize size = dc.GetWindowExt();
	CPen thickpen(PS_SOLID, 5, RGB(0, 0, 0));
	dc.SelectObject(&thickpen);
	dc.Rectangle(0, 0, size.cx, -100);
	
	// cm tick
	for (int i = 1; i < size.cx / 100; i++) {
		int x = 100 * i;
		int y = -60;
		dc.MoveTo(x, 0);
		dc.LineTo(x, y);
	}
	CPen thinpen(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(&thinpen);
	
	// mm tick
	for (int i = 1; i < size.cx / 10; i++) {
		int x = 10 * i;
		int y = -20;
		if (i % 5 == 0) y = -40;
		dc.MoveTo(x, 0);
		dc.LineTo(x, y);
	}

	// cm label
	CFont font;
	VERIFY(font.CreateFont(
		30,                       // nHeight
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		FW_NORMAL,                // nWeight
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("Arial")));            // lpszFacename
	dc.SelectObject(font);
	dc.TextOut(10, -40, _T("0"));
	dc.SetTextAlign(TA_RIGHT);
	for (int i = 1; i < size.cx / 100; i++) {
		int x = 100 * i - 12;
		int y = -40;
		CString str;
		str.Format(_T("%d"), i);
		dc.TextOut(x, y, str);
	}
}
