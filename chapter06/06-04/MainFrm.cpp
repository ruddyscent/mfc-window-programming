﻿
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Simple2.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_TRAY_NOTIFICATION, OnTrayNotification)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	/*
	 * 본문 속 예제(코드를 이용한 메뉴 생성 #2)
	 */
	// (1) '항목2'의 하위 메뉴를 생성한다.
	CMenu Popup1; // 메뉴 객체 생성
	Popup1.CreatePopupMenu(); // 팝업 메뉴 생성
	Popup1.AppendMenu(MF_STRING, 301, _T("1"));
	Popup1.AppendMenu(MF_STRING, 302, _T("2"));
	Popup1.AppendMenu(MF_STRING, 303, _T("3"));
	Popup1.AppendMenu(MF_STRING, 304, _T("4"));

	// (2) '테스트' 메뉴를 생성한다.
	CMenu Popup2; // 메뉴 객체 생성
	Popup2.CreatePopupMenu(); // 팝업 메뉴 생성
	Popup2.AppendMenu(MF_STRING | MF_CHECKED, 201, _T("항목&1"));
	Popup2.AppendMenu(MF_POPUP, (UINT)Popup1.Detach(), _T("항목&2"));
	Popup2.AppendMenu(MF_STRING, 203, _T("항목&3"));

	// (3) '테스트' 메뉴를 최상위 메뉴에 붙인다.
	CMenu* pTopLevel = GetMenu(); // 최상위 메뉴의 포인터를 얻는다.
	pTopLevel->AppendMenu(MF_POPUP, (UINT)Popup2.Detach(), _T("테스트(&T)"));

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	pSysMenu->InsertMenu(6, MF_BYPOSITION | MF_STRING, 16, _T("[트레이 아이콘]"));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((nID & 0xFFF0) == 16) {
		NOTIFYICONDATA nid;
		::ZeroMemory(&nid, sizeof(nid));
		nid.cbSize = sizeof(nid);
		nid.uID = 0;
		nid.hWnd = GetSafeHwnd();
		nid.uFlags = NIF_ICON | NIF_MESSAGE;
		nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		lstrcpy(nid.szTip, _T("내 트레이"));
		nid.uCallbackMessage = WM_TRAY_NOTIFICATION;
		BOOL bRet = ::Shell_NotifyIcon(NIM_ADD, &nid);
		// ShowWindow(SW_MINIMIZE);
		ShowWindow(SW_HIDE);
		return;
	}
	CFrameWnd::OnSysCommand(nID, lParam);
}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	NOTIFYICONDATA nid;
	::ZeroMemory(&nid, sizeof(nid));
	nid.uID = 0;
	nid.hWnd = GetSafeHwnd();
	BOOL bRet = ::Shell_NotifyIcon(NIM_DELETE, &nid);
}

LRESULT CMainFrame::OnTrayNotification(WPARAM wParam, LPARAM lParam) {
	switch (lParam) {
	case WM_LBUTTONDBLCLK:
		ShowWindow(SW_RESTORE);
		NOTIFYICONDATA nid;
		::ZeroMemory(&nid, sizeof(nid));
		nid.uID = 0;
		nid.hWnd = GetSafeHwnd();
		BOOL bRet = ::Shell_NotifyIcon(NIM_DELETE, &nid);
		break;
	}
	return 1;
}