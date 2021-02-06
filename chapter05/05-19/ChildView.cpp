
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "ShowCaret.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_caratPos.SetPoint(50, 50);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
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
	SetCaretPos(m_caratPos); // 캐럿의 위치를 설정한다.
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}


void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	CreateSolidCaret(20, 20); // 캐럿을 생성한다.
	SetCaretPos(m_caratPos); // 캐럿의 위치를 설정한다.
	ShowCaret(); // 캐럿을 화면에 보인다.
}


void CChildView::OnKillFocus(CWnd* pNewWnd)
{
	HideCaret(); // 캐럿을 숨긴다.
	::DestroyCaret(); // 캐럿을 파괴한다.
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar) {
	case VK_LEFT:
		m_caratPos.x -= 20;
		break;
	case VK_RIGHT:
		m_caratPos.x += 20;
		break;
	case VK_UP:
		m_caratPos.y -= 20;
		break;
	case VK_DOWN:
		m_caratPos.y += 20;
		break;
	default:
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	}

	CRect rect;
	GetClientRect(rect);
	m_caratPos.x = min(max(0, m_caratPos.x), rect.Width() - 20);
	m_caratPos.y = min(max(0, m_caratPos.y), rect.Height() - 20);
	Invalidate();
}
