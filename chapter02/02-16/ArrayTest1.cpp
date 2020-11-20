// ArrayTest1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "ArrayTest1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 애플리케이션 개체입니다.

CWinApp theApp;

using namespace std;

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
#if 1
			_tsetlocale(LC_ALL, _T(""));
			UINT a, b;
			_tscanf_s(_T("%d, %d"), &a, &b);
			UINT min = a < b ? a : b;
			UINT max = a < b ? b : a;
			CUIntArray array;
			array.SetSize(max - min + 1);
			for (UINT i = 0; i < max - min + 1; i++) {
				array[i] = i + min;
			}

			UINT sum = 0;
			for (UINT i = 0; i < max - min + 1; i++) {
				_tprintf(_T("%d "), array[max - min - i]);
				sum += array[max - min - i];
			}
			_tprintf(_T("\n"));
			
			float mean = (float)sum / (max - min + 1);
			_tprintf(_T("합: %u, 평균: %0.1f\n"), sum, mean);
			getchar();
#endif
#if 0
			_tsetlocale(LC_ALL, _T("")); // 유니코드 한국어 출력에 필요
			CStringArray array; // 객체를 생성한다.
			array.SetSize(5); // 배열 크기를 설정한다.
			for (int i = 0; i < 5; i++) {
				CString string;
				string.Format(_T("%d년이 지났습니다."), (i + 1) * 10);
				array[i] = string; // 값을 대입한다.
			}
			for (int i = 0; i < 5; i++)
				_tprintf(_T("%s\n"), (LPCTSTR)array[i]); // 값을 출력한다.
#endif
#if 0
			CUIntArray array;
			array.SetSize(5);
			for (int i = 0; i < 5; i++)
				array[i] = i;
			/* 배열 원소 삽입 */
			array.InsertAt(3, 77); // 인덱스 3 위치에 원소를 삽입한다.
			for (int i = 0; i < array.GetSize(); i++) // 변경된 배열의 크기만큼 반복한다.
				_tprintf(_T("%d "), array[i]);
			_tprintf(_T("\n"));
			/* 배열 원소 삭제 */
			array.RemoveAt(4); // 인덱스 4 위치의 원소를 삭제한다.
			for (int i = 0; i < array.GetSize(); i++)
				_tprintf(_T("%d "), array[i]);
			_tprintf(_T("\n"));
#endif
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
