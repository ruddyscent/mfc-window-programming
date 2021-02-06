
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	int m_xPos, m_yPos; // 도형의 현재 위치
	int m_xMax, m_yMax; // 클라이언트 영역의 크기
	BOOL m_bFill; // 도형의 내부를 채울지 여부

// 작업입니다.
public:

// 재정의입니다.
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

