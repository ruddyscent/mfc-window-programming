#include <windows.h>

// WinMain 함수에서 참조하므로 함수 원형을 선언한다.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wndclass;
	HWND hwnd;
	MSG msg;

	// 윈도우 클래스를 초기화하고 운영체제에 등록한다.
	wndclass.style = CS_HREDRAW | CS_VREDRAW; // 스타일 지정
	wndclass.lpfnWndProc = WndProc; // 윈도우 프로시저 이름
	wndclass.cbClsExtra = 0; // 여분 메모리(0바이트)
	wndclass.cbWndExtra = 0; // 여분 메모리(0바이트)
	wndclass.hInstance = hInstance; // 인스턴스 핸들
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 아이콘 모양
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 모양
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경(흰색)
	wndclass.lpszMenuName = NULL; // 메뉴(NULL->메뉴 없음)
	wndclass.lpszClassName = TEXT("HelloClass"); // 윈도우 클래스 이름
	if (!RegisterClass(&wndclass)) return 1;

	// 윈도우를 생성하고 화면에 나타낸다.
	hwnd = CreateWindow(TEXT("HelloClass"), TEXT("HelloSDK"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);

	// 메시지 큐에서 메시지를 하나씩 꺼내서 처리한다.
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* str = TEXT("Hello, SDK");

	// 발생한 메시지의 종류에 따라 적절히 처리한다.
	switch (message) {
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("마우스 클릭!"), TEXT("마우스 메시지"), MB_OK);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, str, lstrlen(str));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	// 응용 프로그램이 처리하지 않은 메시지는 운영체제가 처리한다.
	return DefWindowProc(hwnd, message, wParam, lParam);
}
