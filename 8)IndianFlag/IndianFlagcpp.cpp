# include <Windows.h>
#include "Source.h"

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
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(szAppName,
		TEXT("Indian Flag"),
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static HBITMAP hbitmap;
	static BITMAP bitmap;
	static HDC hdc,hdcMem;
	PAINTSTRUCT ps;
	RECT rc, rc1, rc2,rc3;
	static HINSTANCE hInstance;
	int x, y, w, h;

	
	switch (iMsg) {
	case WM_CREATE:
		hInstance = GetModuleHandle(NULL);
		hbitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
		hdcMem = CreateCompatibleDC(NULL);
		break;

	case WM_PAINT:

		GetClientRect(hWnd, &rc);
		hdc = BeginPaint(hWnd, &ps);
		rc1.left = rc.left; rc1.right = rc.right; rc1.top = rc.top; rc1.bottom = rc.bottom / 3 * 1;

		rc2.left = rc.left; rc2.right = rc.right; rc2.top = rc.bottom / 3 * 1; rc2.bottom = rc.bottom / 3 * 2;

		rc3.left = rc.left; rc3.right = rc.right; rc3.top = rc.bottom / 3 * 2; rc3.bottom = rc.bottom;

		
        FillRect(hdc,&rc1, CreateSolidBrush(RGB(255, 153, 51)));
		FillRect(hdc,&rc2, CreateSolidBrush(RGB(255, 255, 255)));
		FillRect(hdc, &rc3, CreateSolidBrush(RGB(19, 136, 8)));

		SelectObject(hdcMem, hbitmap);
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);

		x = (rc.bottom / 3 * 2) + 50;
		y = rc.bottom / 3;
		w = rc.bottom / 3;
		h = rc.bottom / 3;
		StretchBlt(hdc, x, y, w, h, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}
