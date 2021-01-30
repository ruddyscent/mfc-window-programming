
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

CChildView::CChildView()
{
	rect = new CRect(10, 10, 400, 100);
}

CChildView::~CChildView()
{
	delete rect;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
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
	dc.Ellipse(rect);
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


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	point.x -= 195;
	point.y -= 45;
	rect->MoveToXY(point);

	CWnd::OnMouseMove(nFlags, point);

	Invalidate();
}
