#include <Windows.h>
#include <tchar.h>
#include "resource2.h"



static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTile[] = _T("Windows Desktop Guided Tour Application");
HINSTANCE hInst;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM );


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"), NULL);
		return 1;
	}
	hInst = hInstance;
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTile,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500,
		100,
		NULL,
		NULL,
		hInstance,
		NULL);
	HWND btns[8][8];
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			int menu = 101 + j + (8 * i);
			btns[i][j] = CreateWindow(
				_T("button"),
				NULL,
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				5 + 40 * j,
				5 + 40 * i,
				40,
				40,
				hWnd,
				((HMENU) menu),
				hInstance,
				NULL
			);
		}
		
	}
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop!");
	HPEN hPen = CreatePen(PS_DASHDOTDOT, 2, NULL);

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, hPen);
		Ellipse(hdc, 5, 5, 100, 20);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//get eventcalls from children
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case BN_CLICKED:
			MessageBox(NULL, _T("that's good"), _T("ok button response"), NULL);
			break;
		case BTN_1:
			MessageBox(NULL, _T("button 1 pressed :)"), _T("header"), NULL);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}