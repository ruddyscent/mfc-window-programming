
// EditCtrlView.h: CEditCtrlView 클래스의 인터페이스
//

#pragma once


class CEditCtrlView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CEditCtrlView() noexcept;
	DECLARE_DYNCREATE(CEditCtrlView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_EDITCTRL_FORM };
#endif

// 특성입니다.
public:
	CEditCtrlDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CEditCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit;
	CStatic m_static;
	afx_msg void OnEnChangeMyedit();
	afx_msg void OnEnMaxtextMyedit();
};

#ifndef _DEBUG  // EditCtrlView.cpp의 디버그 버전
inline CEditCtrlDoc* CEditCtrlView::GetDocument() const
   { return reinterpret_cast<CEditCtrlDoc*>(m_pDocument); }
#endif

