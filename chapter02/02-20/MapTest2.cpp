// MapTest2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "MapTest2.h"
#include <afxtempl.h> // 템플릿 클래스 정의를 담고 있다.

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 애플리케이션 개체입니다.

CWinApp theApp;

using namespace std;


// CString 타입에 해당하는 해시 함수가 없으므로 정의한다.
template <> UINT AFXAPI HashKey(CString& str)
{
	LPCTSTR key = (LPCTSTR)str;
	return HashKey(key); // LPCTSTR 타입의 해시 함수를 재호출한다. 
}


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
			_tsetlocale(LC_ALL, _T("")); // 유니코드 한국어 출력에 필요

			// 맵(CString -> UINT) 객체를 생성하고 초기화한다.
			CMap<CString, CString&, UINT, UINT&> map;
			map[CString(_T("전승환"))] = 172;
			map[CString(_T("박철수"))] = 164;
			map[CString(_T("이해인"))] = 158;
			map[CString(_T("구오성"))] = 182;
			map[CString(_T("김순희"))] = 159;
			map[CString(_T("박상훈"))] = 177;
			map[CString(_T("최규석"))] = 172;
			map[CString(_T("백설현"))] = 168;
			map[CString(_T("김정훈"))] = 170;
			map[CString(_T("한수길"))] = 168;
			map[CString(_T("정지민"))] = 172;
			map[CString(_T("최진"))] = 179;

			TCHAR szName[100];
			_tscanf_s(_T("%s"), szName, (UINT)_countof(szName));

			UINT height;
			if (map.Lookup(CString(szName), height))
				_tprintf(_T("키: %d cm\n"), height);
			else {
				height = _wtoi(szName);
				POSITION pos = map.GetStartPosition();
				while (pos != NULL) {
					CString key;
					UINT value;
					map.GetNextAssoc(pos, key, value);
					if (height == value)
						_tprintf(_T("%s "), key);
				}
				_tprintf(_T("\n"));
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
