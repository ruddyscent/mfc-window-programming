
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "TrackMouse.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_bMouseIn = FALSE;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
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


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bMouseIn == FALSE) {
		// 마우스 커서 추적을 요청한다.
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = HOVER_DEFAULT;
		::TrackMouseEvent(&tme);

		// 메인 윈도우 크기를 300*150으로 변경한다.
		CWnd* pMainWnd = AfxGetMainWnd();
		CRect rect;
		pMainWnd->GetWindowRect(&rect);
		rect.right = rect.left + 300;
		rect.bottom = rect.top + 150;
		pMainWnd->MoveWindow(&rect);

		// 마우스 커서가 클라이언트 영역에 있음을 기억해둔다.
		m_bMouseIn = TRUE;
	}
}


void CChildView::OnMouseLeave()
{
	// 마우스 커서가 클라이언트 영역 밖에 있음을 기억해둔다.
	m_bMouseIn = FALSE;

	// 메인 윈도우 크기를 200*100으로 변경한다.
	CWnd* pMainWnd = AfxGetMainWnd();
	CRect rect;
	pMainWnd->GetWindowRect(&rect);
	rect.right = rect.left + 200;
	rect.bottom = rect.top + 100;
	pMainWnd->MoveWindow(&rect);
}
