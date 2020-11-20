
// Button2View.cpp: CButton2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Button2.h"
#endif

#include "Button2Doc.h"
#include "Button2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CButton2View

IMPLEMENT_DYNCREATE(CButton2View, CFormView)

BEGIN_MESSAGE_MAP(CButton2View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON1, &CButton2View::OnBnClickedButton1)
END_MESSAGE_MAP()

// CButton2View 생성/소멸

CButton2View::CButton2View() noexcept
	: CFormView(IDD_BUTTON2_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CButton2View::~CButton2View()
{
}

void CButton2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_checkbox);
	DDX_Control(pDX, IDC_CHECK2, m_3state);
	DDX_Control(pDX, IDC_RADIO1, m_radio1);
	DDX_Control(pDX, IDC_RADIO2, m_radio2);
}

BOOL CButton2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CButton2View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// 버튼 컨트롤을 초기화한다.
	m_checkbox.SetCheck(1);
	m_3state.SetCheck(2);
	m_radio2.SetCheck(1);
}


// CButton2View 인쇄

BOOL CButton2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CButton2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CButton2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CButton2View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CButton2View 진단

#ifdef _DEBUG
void CButton2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CButton2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CButton2Doc* CButton2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CButton2Doc)));
	return (CButton2Doc*)m_pDocument;
}
#endif //_DEBUG


// CButton2View 메시지 처리기


void CButton2View::OnBnClickedButton1()
{
	int state_checkbox = m_checkbox.GetCheck();
	int state_3state = m_3state.GetCheck();
	int state_radio1 = m_radio1.GetCheck();
	int state_radio2 = m_radio2.GetCheck();

	CString str;
	str.Format(_T("버튼 상태: %d, %d, %d, %d"),
		state_checkbox, state_3state, state_radio1, state_radio2);
	MessageBox(str, _T("Button2 예제"), MB_ICONINFORMATION);
}
