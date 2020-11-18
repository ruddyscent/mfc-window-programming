
// Button1View.cpp: CButton1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Button1.h"
#endif

#include "Button1Doc.h"
#include "Button1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CButton1View

IMPLEMENT_DYNCREATE(CButton1View, CView)

BEGIN_MESSAGE_MAP(CButton1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_BN_CLICKED(101, OnButtonClicked)
END_MESSAGE_MAP()

// CButton1View 생성/소멸

CButton1View::CButton1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CButton1View::~CButton1View()
{
}

BOOL CButton1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CButton1View 그리기

void CButton1View::OnDraw(CDC* /*pDC*/)
{
	CButton1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CButton1View 인쇄

BOOL CButton1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CButton1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CButton1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CButton1View 진단

#ifdef _DEBUG
void CButton1View::AssertValid() const
{
	CView::AssertValid();
}

void CButton1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CButton1Doc* CButton1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CButton1Doc)));
	return (CButton1Doc*)m_pDocument;
}
#endif //_DEBUG


// CButton1View 메시지 처리기


int CButton1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 버튼 컨트롤을 생성한다.
	m_pushbutton.Create(_T("푸시 버튼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(20, 20, 160, 50), this, 101);
	m_checkbox.Create(_T("체크 박스"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		CRect(20, 60, 160, 90), this, 102);
	m_3state.Create(_T("3상태 체크 박스"), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE,
		CRect(20, 100, 160, 130), this, 103);
	m_radio1.Create(_T("라디오 버튼 1"), WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
		CRect(20, 170, 160, 200), this, 104);
	m_radio2.Create(_T("라디오 버튼 2"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		CRect(20, 210, 160, 240), this, 105);
	m_groupbox.Create(_T("그룹 박스"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		CRect(10, 140, 170, 250), this, 106);

	// 버튼 컨트롤을 초기화한다.
	m_checkbox.SetCheck(1);
	m_3state.SetCheck(2);
	m_radio2.SetCheck(1);

	return 0;
}


void CButton1View::OnButtonClicked()
{
	int state_checkbox = m_checkbox.GetCheck();
	int state_3state = m_3state.GetCheck();
	int state_radio1 = m_radio1.GetCheck();
	int state_radio2 = m_radio2.GetCheck();

	CString str;
	str.Format(_T("버튼 상태: %d, %d, %d, %d"),
		state_checkbox, state_3state, state_radio1, state_radio2);
	MessageBox(str, _T("Button1 예제"), MB_ICONINFORMATION);
}
