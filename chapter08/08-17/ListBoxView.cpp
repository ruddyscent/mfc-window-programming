
// ListBoxView.cpp: CListBoxView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ListBox.h"
#endif

#include "ListBoxDoc.h"
#include "ListBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CListBoxView

IMPLEMENT_DYNCREATE(CListBoxView, CFormView)

BEGIN_MESSAGE_MAP(CListBoxView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_RIGHT, &CListBoxView::OnBnClickedRight)
	ON_BN_CLICKED(IDC_LEFT, &CListBoxView::OnBnClickedLeft)
END_MESSAGE_MAP()

// CListBoxView 생성/소멸

CListBoxView::CListBoxView() noexcept
	: CFormView(IDD_LISTBOX_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CListBoxView::~CListBoxView()
{
}

void CListBoxView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_RIGHT, m_right);
	DDX_Control(pDX, IDC_LEFT, m_left);
}

BOOL CListBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CListBoxView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_list1.AddString(_T("사과"));
	m_list1.AddString(_T("딸기"));
	m_list1.AddString(_T("파인애플"));
	m_list1.AddString(_T("복숭아"));
}


// CListBoxView 인쇄

BOOL CListBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CListBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CListBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CListBoxView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CListBoxView 진단

#ifdef _DEBUG
void CListBoxView::AssertValid() const
{
	CFormView::AssertValid();
}

void CListBoxView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CListBoxDoc* CListBoxView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListBoxDoc)));
	return (CListBoxDoc*)m_pDocument;
}
#endif //_DEBUG


// CListBoxView 메시지 처리기


void CListBoxView::OnBnClickedRight()
{
	int nIndex = m_list1.GetCurSel();
	if (nIndex != LB_ERR) {
		CString str;
		m_list1.GetText(nIndex, str);
		m_list1.DeleteString(nIndex);
		m_list1.SetCurSel(nIndex); // 삭제된 다음 위치의 항목이 자동 선택됨
		m_list2.AddString(str);
		AfxGetMainWnd()->SetWindowText(_T("왼쪽에서 오른쪽으로..."));
	}
}


void CListBoxView::OnBnClickedLeft()
{
	int nIndex = m_list2.GetCurSel();
	if (nIndex != LB_ERR) {
		CString str;
		m_list2.GetText(nIndex, str);
		m_list2.DeleteString(nIndex);
		m_list2.SetCurSel(nIndex); // 삭제된 다음 위치의 항목이 자동 선택됨
		m_list1.AddString(str);
		AfxGetMainWnd()->SetWindowText(_T("오른쪽에서 왼쪽으로..."));
	}
}
