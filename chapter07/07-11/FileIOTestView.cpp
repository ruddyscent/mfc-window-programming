
// FileIOTestView.cpp: CFileIOTestView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "FileIOTest.h"
#endif

#include "FileIOTestDoc.h"
#include "FileIOTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileIOTestView

IMPLEMENT_DYNCREATE(CFileIOTestView, CView)

BEGIN_MESSAGE_MAP(CFileIOTestView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CFileIOTestView 생성/소멸

CFileIOTestView::CFileIOTestView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CFileIOTestView::~CFileIOTestView()
{
}

BOOL CFileIOTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CFileIOTestView 그리기

void CFileIOTestView::OnDraw(CDC* pDC)
{
	CFileIOTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->SetMapMode(MM_LOMETRIC);
	pDC->Rectangle(50, -50, 350, -350);
	pDC->Ellipse(500, -50, 800, -350);
}


// CFileIOTestView 인쇄

BOOL CFileIOTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CFileIOTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CFileIOTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CFileIOTestView 진단

#ifdef _DEBUG
void CFileIOTestView::AssertValid() const
{
	CView::AssertValid();
}

void CFileIOTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFileIOTestDoc* CFileIOTestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileIOTestDoc)));
	return (CFileIOTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileIOTestView 메시지 처리기
