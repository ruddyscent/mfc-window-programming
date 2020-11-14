
// InputSaveLoadDoc.cpp: CInputSaveLoadDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "InputSaveLoad.h"
#endif

#include "InputSaveLoadDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CInputSaveLoadDoc

IMPLEMENT_DYNCREATE(CInputSaveLoadDoc, CDocument)

BEGIN_MESSAGE_MAP(CInputSaveLoadDoc, CDocument)
	ON_COMMAND(ID_STYLE_ITALIC, &CInputSaveLoadDoc::OnStyleItalic)
	ON_UPDATE_COMMAND_UI(ID_STYLE_ITALIC, &CInputSaveLoadDoc::OnUpdateStyleItalic)
	ON_COMMAND(ID_STYLE_UNDERLINE, &CInputSaveLoadDoc::OnStyleUnderline)
	ON_UPDATE_COMMAND_UI(ID_STYLE_UNDERLINE, &CInputSaveLoadDoc::OnUpdateStyleUnderline)
END_MESSAGE_MAP()


// CInputSaveLoadDoc 생성/소멸

CInputSaveLoadDoc::CInputSaveLoadDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CInputSaveLoadDoc::~CInputSaveLoadDoc()
{
}

BOOL CInputSaveLoadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_str.RemoveAll();
	m_bItalic = m_bUnderline = FALSE;

	return TRUE;
}




// CInputSaveLoadDoc serialization

void CInputSaveLoadDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_bItalic << m_bUnderline;
		m_str.Serialize(ar);
	}
	else
	{
		ar >> m_bItalic >> m_bUnderline;
		m_str.Serialize(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CInputSaveLoadDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CInputSaveLoadDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CInputSaveLoadDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CInputSaveLoadDoc 진단

#ifdef _DEBUG
void CInputSaveLoadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInputSaveLoadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CInputSaveLoadDoc 명령


void CInputSaveLoadDoc::OnStyleItalic()
{
	m_bItalic = !m_bItalic;
	SetModifiedFlag();
	UpdateAllViews(NULL); // 뷰의 화면을 갱신한다.
}


void CInputSaveLoadDoc::OnUpdateStyleItalic(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bItalic == TRUE);
}


void CInputSaveLoadDoc::OnStyleUnderline()
{
	m_bUnderline = !m_bUnderline;
	SetModifiedFlag();
	UpdateAllViews(NULL); // 뷰의 화면을 갱신한다.
}


void CInputSaveLoadDoc::OnUpdateStyleUnderline(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bUnderline == TRUE);
}
