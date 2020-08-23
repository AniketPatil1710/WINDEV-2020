# include <Windows.h>
#define MYTIMER 1000
#define TIME 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndClass;
	HWND hWnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Aniket");

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(szAppName,
		TEXT("Blinking Window"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		900,
		500,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

int iPaintFlag;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HBRUSH HBrush[11];
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;

	switch (iMsg) {
	case WM_CREATE:
		HBrush[0] = CreateSolidBrush(RGB(255, 0, 0));
		HBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
		HBrush[2] = CreateSolidBrush(RGB(0, 0, 255));
		HBrush[3] = CreateSolidBrush(RGB(255, 255, 0));
		HBrush[4] = CreateSolidBrush(RGB(0, 255, 255));
		HBrush[5] = CreateSolidBrush(RGB(255, 0, 255));
		HBrush[6] = CreateSolidBrush(RGB(255, 255, 255));
		HBrush[7] = CreateSolidBrush(RGB(0,  0, 0));
		HBrush[8] = CreateSolidBrush(RGB(123, 345, 32));
		HBrush[9] = CreateSolidBrush(RGB(200, 126, 125));
		HBrush[10] = CreateSolidBrush(RGB(50, 200, 120));

		break;
	case WM_TIMER:
		KillTimer(hWnd, MYTIMER);
		if (iPaintFlag > 10)
			iPaintFlag = -1;

		iPaintFlag++;

		InvalidateRect(hWnd, NULL, TRUE);

		SetTimer(hWnd, MYTIMER, TIME, NULL);
		break;

	case WM_PAINT :
		GetClientRect(hWnd, &rc);

		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, HBrush[iPaintFlag]);
		FillRect(hdc, &rc, HBrush[iPaintFlag]);
		EndPaint(hWnd, &ps);
		SetTimer(hWnd, MYTIMER, TIME, NULL);
		break;
	

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}
