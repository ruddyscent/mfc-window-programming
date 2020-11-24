
// ListBoxView.h: CListBoxView 클래스의 인터페이스
//

#pragma once


class CListBoxView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CListBoxView() noexcept;
	DECLARE_DYNCREATE(CListBoxView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_LISTBOX_FORM };
#endif

// 특성입니다.
public:
	CListBoxDoc* GetDocument() const;

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
	virtual ~CListBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list1;
	CListBox m_list2;
	CButton m_right;
	CButton m_left;
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedLeft();
};

#ifndef _DEBUG  // ListBoxView.cpp의 디버그 버전
inline CListBoxDoc* CListBoxView::GetDocument() const
   { return reinterpret_cast<CListBoxDoc*>(m_pDocument); }
#endif

