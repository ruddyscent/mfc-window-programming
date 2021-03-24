
// StaticView.cpp: CStaticView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Static.h"
#endif

#include "StaticDoc.h"
#include "StaticView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStaticView

IMPLEMENT_DYNCREATE(CStaticView, CFormView)

BEGIN_MESSAGE_MAP(CStaticView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_STN_CLICKED(IDC_METAFILE, &CStaticView::OnStnClickedMetafile)
END_MESSAGE_MAP()

// CStaticView 생성/소멸

CStaticView::CStaticView() noexcept
	: CFormView(IDD_STATIC_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CStaticView::~CStaticView()
{
}

void CStaticView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_METAFILE, m_metafile);
}

BOOL CStaticView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CStaticView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_metafile.SetEnhMetaFile(::GetEnhMetaFile(_T("test.emf")));
}


// CStaticView 인쇄

BOOL CStaticView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CStaticView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CStaticView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CStaticView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CStaticView 진단

#ifdef _DEBUG
void CStaticView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStaticView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CStaticDoc* CStaticView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStaticDoc)));
	return (CStaticDoc*)m_pDocument;
}
#endif //_DEBUG


// CStaticView 메시지 처리기


void CStaticView::OnStnClickedMetafile()
{
	MessageBox(_T("확장 메타파일 그림 클릭!"));
}
