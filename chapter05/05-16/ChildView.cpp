
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "ChangeCursor.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView(): m_pos(NULL), m_move(FALSE)
{
	CRect rect(10, 10, 400, 100);
	m_rectList.AddTail(rect);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
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
	CPaintDC dc(this);
	dc.SelectStockObject(LTGRAY_BRUSH);
	
	POSITION pos = m_rectList.GetHeadPosition();
	while (pos != NULL) {
		CRect rect = m_rectList.GetNext(pos);
		dc.Ellipse(rect);
	}
	
	if (m_move) {
		dc.SelectStockObject(NULL_BRUSH);
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		dc.SelectObject(pen);
		dc.Ellipse(m_tmpRect);
	}
}


BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// 클라이언트 영역이면 커서를 변경한다.
	if (nHitTest == HTCLIENT) {
		CPoint point;
		::GetCursorPos(&point); // 커서 위치(스크린 좌표)를 얻는다.
		ScreenToClient(&point); // 스크린 좌표를 클라이언트 좌표로 변환한다.
		CRgn rgn;
		rgn.CreateEllipticRgn(10, 10, 400, 100); // 타원형 리전을 생성한다.
		if (rgn.PtInRegion(point)) // 커서가 리전 안쪽에 있는지 확인한다.
			// 사용자 정의 커서로 변경한다.
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
		else
			// 표준 커서 중 하나로 변경한다.
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return TRUE;
	}

	// 클라이언트 영역이 아니면 운영체제가 자동으로 처리한다.
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pos = m_rectList.GetHeadPosition();
	while (m_pos != NULL) {
		CRect rect = m_rectList.GetAt(m_pos);
		CRgn rgn;
		rgn.CreateEllipticRgnIndirect(rect); // 타원형 리전을 생성한다.
		if (rgn.PtInRegion(point)) { // 커서가 리전 안쪽에 있는지 확인한다.
			m_offset.x = rect.left - point.x;
			m_offset.y = rect.top - point.y;
			m_tmpRect.CopyRect(rect);
			m_move = TRUE;
			return;
		}
		m_rectList.GetNext(m_pos);
	}
	Invalidate();

  	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_move) {
		m_tmpRect.MoveToXY(point);
		m_tmpRect.OffsetRect(m_offset);
		Invalidate();
	}
	else {
		CWnd::OnMouseMove(nFlags, point);
	}
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_move = FALSE;

	if (m_pos == NULL) {
		CWnd::OnLButtonUp(nFlags, point);
	}
	else {
		if (nFlags & MK_CONTROL) {
			CRect rect = m_rectList.GetAt(m_pos);
			m_rectList.AddTail(m_tmpRect);
		}
		else {
			CRect rect = m_rectList.GetAt(m_pos);
			m_rectList.RemoveAt(m_pos);
			m_rectList.AddTail(m_tmpRect);
		}
		Invalidate();
	}
}
