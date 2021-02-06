
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "InputKeyStroke.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_xPos = m_yPos = 60; // 임의 값으로 초기화
	m_bFill = FALSE; // 도형 내부를 채우지 않음
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
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
	CPaintDC dc(this);
	if (m_bFill == TRUE) dc.SelectStockObject(BLACK_BRUSH);
	dc.Ellipse(m_xPos - 20, m_yPos - 20, m_xPos + 20, m_yPos + 20);
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	m_xMax = cx;
	m_yMax = cy;
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		m_xPos -= 20;
		break;
	case VK_RIGHT:
		m_xPos += 20;
		break;
	case VK_UP:
		m_yPos -= 20;
		break;
	case VK_DOWN:
		m_yPos += 20;
		break;
	case VK_SPACE:
		m_bFill = !m_bFill;
	}
	// 20 <= m_xPos <= m_xMax-20
	m_xPos = min(max(20, m_xPos), m_xMax - 20);
	// 20 <= m_yPos <= m_yMax-20
	m_yPos = min(max(20, m_yPos), m_yMax - 20);
	Invalidate();
}
