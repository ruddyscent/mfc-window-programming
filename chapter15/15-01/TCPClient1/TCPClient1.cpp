// TCPClient1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "TCPClient1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 애플리케이션 개체입니다.

CWinApp theApp;

using namespace std;

void ErrQuit(int err)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, _T("오류 발생"), MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
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
			_tsetlocale(LC_ALL, _T(""));
			AfxSocketInit();

			CSocket sock;
			if (!sock.Create())
				ErrQuit(sock.GetLastError());

			if (!sock.Connect(_T("127.0.0.1"), 8000))
				ErrQuit(sock.GetLastError());

			TCHAR buf[256];
			int nbytes;

			for (int i = 0; i < 5; i++) {
				wsprintf(buf, _T("%d번째 테스트 메시지\r\n"), i);
				nbytes = sock.Send(buf, 256);
				if (nbytes == SOCKET_ERROR)
					ErrQuit(sock.GetLastError());
				else {
					_tprintf(_T("<%d> %d바이트 전송\n"), i, nbytes);
					Sleep(1000);
				}
			}
			sock.Close();
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
