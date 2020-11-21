// TCPServer1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "TCPServer1.h"

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
			if (!sock.Create(8000))
				ErrQuit(sock.GetLastError());

			if (!sock.Listen())
				ErrQuit(sock.GetLastError());

			TCHAR buf[256 + 1];
			int nbytes;

			while (1) {
				CSocket newsock;
				if (!sock.Accept(newsock))
					ErrQuit(sock.GetLastError());

				CString PeerAddress;
				UINT PeerPort;
				newsock.GetPeerName(PeerAddress, PeerPort);
				_tprintf(_T("### IP 주소: %s, 포트 번호: %d ###\n"),
					(LPCTSTR)PeerAddress, PeerPort);

				while (1) {
					nbytes = newsock.Receive(buf, 256);
					if (nbytes == 0 || nbytes == SOCKET_ERROR) {
						break;
					}
					else {
						buf[nbytes] = _T('\0');
						_tprintf(_T("%s"), buf);
					}
				}
				newsock.Close();
				_tprintf(_T("### 접속 종료 ###\n\n"));
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
