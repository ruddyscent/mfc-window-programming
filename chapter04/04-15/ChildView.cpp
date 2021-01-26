
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "DrawTexts.h"
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

	CRect rect;
	GetClientRect(&rect);

	dc.SetTextColor(RGB(255, 0, 0)); // 글자를 빨간색으로 설정
	dc.SetBkColor(RGB(255, 255, 0)); // 배경을 노란색으로 설정
	dc.DrawText(CString("DrawText 함수를 연습합니다. [1]"), &rect, 0);
	dc.DrawText(CString("DrawText 함수를 연습합니다. [2]"), &rect,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	dc.SetTextAlign(TA_CENTER); // 가운데 정렬 방식으로 변경
	dc.SetTextColor(RGB(0, 0, 255)); // 글자를 파란색으로 설정
	dc.SetBkColor(RGB(0, 255, 0)); // 배경을 초록색으로 설정
	dc.TextOut(rect.right / 2, 3 * rect.bottom / 4,
		CString("TextOut 함수를 연습합니다."));
}

