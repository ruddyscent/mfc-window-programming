// ArrayTest2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "ArrayTest2.h"
#include <afxtempl.h> // 템플릿 클래스 정의를 담고 있다.

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 애플리케이션 개체입니다.

CWinApp theApp;

using namespace std;


// 3차원 좌표를 저장할 수 있는 클래스
// 모든 멤버가 public일 때는 class 대신 struct를 사용하면 좀더 편리하다.
struct Point3D {
	int x, y, z;
	Point3D() {} // 템플릿 클래스에 사용할 때는 기본 생성자가 필요하다.
	Point3D(int x0, int y0, int z0) { x = x0; y = y0; z = z0; }
};


int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: 여기에 애플리케이션 동작을 코딩합니다.
			wprintf(L"심각한 오류: MFC 초기화 실패\n");
			nRetCode = 1;
		}
		else
		{
			// Point3D 객체를 저장할 수 있는 배열 객체를 생성한다.
			CArray<Point3D, Point3D&> array;
			array.SetSize(5);
			for (int i = 0; i < 5; i++) {
				Point3D pt(i, i * 10, i * 100);
				array[i] = pt;
			}
			for (int i = 0; i < 5; i++) {
				Point3D pt = array[i];
				_tprintf(_T("%d, %d, %d\n"), pt.x, pt.y, pt.z);
			}
		}
	}
	else
	{
		// TODO: 오류 코드를 필요에 따라 수정합니다.
		wprintf(L"심각한 오류: GetModuleHandle 실패\n");
		nRetCode = 1;
	}

	return nRetCode;
}
