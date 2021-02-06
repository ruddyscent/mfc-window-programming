
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "InputCharacter.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_rect.SetRect(0, 0, 0, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
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

	// 화면 출력용 폰트를 선택한다.
	CFont font;
	font.CreatePointFont(150, _T("궁서"));
	dc.SelectObject(&font);

	// 현재까지 입력된 글자들을 화면에 출력한다.
	GetClientRect(&m_rect);
	dc.DrawText(m_str.GetData(), m_str.GetSize(), &m_rect, DT_SINGLELINE);
	dc.DrawText(m_str.GetData(), m_str.GetSize(), &m_rect, DT_CALCRECT);
	SetCaretPos(CPoint(m_rect.Width(), 0));
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// [Backspace] 키 입력 시 맨 마지막 글자를 삭제한다.
	if (nChar == _T('\b')) {
		if (m_str.GetSize() > 0)
			m_str.RemoveAt(m_str.GetSize() - 1);
	}
	// 그 밖의 경우에는 동적 배열에 글자를 추가한다.
	else {
		m_str.Add(nChar);
	}

	// 화면을 갱신한다.
	Invalidate();
}


void CChildView::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideCaret(); // 캐럿을 숨긴다.
	::DestroyCaret(); // 캐럿을 파괴한다.
}


void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(150, _T("궁서"));
	dc.SelectObject(&font);
	dc.DrawText(m_str.GetData(), m_str.GetSize(), &m_rect, DT_CALCRECT);

	CreateSolidCaret(20, 20); // 캐럿을 생성한다.
	SetCaretPos(CPoint(m_rect.Width(), 0)); // 캐럿의 위치를 설정한다.
	ShowCaret(); // 캐럿을 화면에 보인다.
}
