
// Button2View.h: CButton2View 클래스의 인터페이스
//

#pragma once


class CButton2View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CButton2View() noexcept;
	DECLARE_DYNCREATE(CButton2View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_BUTTON2_FORM };
#endif

// 특성입니다.
public:
	CButton2Doc* GetDocument() const;

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
	virtual ~CButton2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CButton m_checkbox;
	CButton m_3state;
	CButton m_radio1;
	CButton m_radio2;
	afx_msg void OnBnClickedButton1();
};

#ifndef _DEBUG  // Button2View.cpp의 디버그 버전
inline CButton2Doc* CButton2View::GetDocument() const
   { return reinterpret_cast<CButton2Doc*>(m_pDocument); }
#endif

