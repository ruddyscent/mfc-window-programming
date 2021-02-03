
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "DrawCircles.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_bDrawMode = FALSE;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
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
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 마우스 캡처를 시작한다(MFC 함수 사용).
	SetCapture();
	// 그리기 모드를 시작한다.
	m_bDrawMode = TRUE;
	// 좌표를 저장한다.
	m_x1 = m_x2 = point.x;
	m_y1 = m_y2 = point.y;
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// 그리기 모드이면 타원을 지우고 그리기를 반복한다.
	if (m_bDrawMode) {
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		// 이전에 그린 타원을 지운다.
		dc.SetROP2(R2_NOT);
		dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
		// 새로운 타원을 그린다.
		dc.SetROP2(R2_NOT);
		m_x2 = point.x;
		m_y2 = point.y;
		dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	}
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.SelectStockObject(NULL_BRUSH);
	// 최종적인 타원을 그린다.
	dc.SetROP2(R2_COPYPEN);
	m_x2 = point.x;
	m_y2 = point.y;
	dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	// 그리기 모드를 끝낸다.
	m_bDrawMode = FALSE;
	// 마우스 캡처를 해제한다(API 함수 사용).
	::ReleaseCapture();
}
