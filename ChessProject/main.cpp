#include <Windows.h>
#include <optional>
#include <tchar.h>
#include "resource2.h"
#include <string>
#include "ChessPiece.h"
using namespace std;

#define Button_Size 100

#define PAWN "pawn"
#define ALLIGNWHITE "white"


static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTile[] = _T("Windows Desktop Guided Tour Application");
enum Phase;
Phase title;
HINSTANCE hInst;
void buttonAction(int wParam);

HWND btns[8][8];
ChessPiece chessPieces[32];


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM );
HWND hWnd;
void setString(HWND arr[][8], int x, int y, LPCWSTR newTitle);
optional<ChessPiece> getChessPieceAtPosition(ChessPiece arr[32], int x, int y);


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	title = Phase::Pick;

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
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTile,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		830,
		850,
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
				5 + Button_Size * j,
				5 + Button_Size * i,
				Button_Size,
				Button_Size,
				hWnd,
				((HMENU) menu),
				hInstance,
				NULL
			);
		}
		
	}
	btns[0][0] = NULL;
	btns[0][0] = CreateWindow(
		_T("button"),
		_T("button"),
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		5,
		5,
		Button_Size,
		Button_Size,
		hWnd,
		(HMENU)101,
		hInstance,
		NULL
	);
	setString(btns, 4, 7, L"mah man");
	

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
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//get eventcalls from children
	case WM_COMMAND:

		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			MessageBox(NULL, _T("that's good"), _T("ok button response"), NULL);
			buttonAction(wParam);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}


void setString(HWND arr[][8], int x, int y, LPCWSTR newTitle) {
	arr[x][y] = NULL;
	int menu = 101 + x + y * 8;
	arr[x][y] = CreateWindow(
		_T("button"),
		newTitle,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		5 + Button_Size * x,
		5 + Button_Size * y,
		Button_Size,
		Button_Size,
		hWnd,
		(HMENU) menu,
		hInst,
		NULL
	);
}

optional<ChessPiece> getChessPieceAtPosition(ChessPiece arr[32], int x, int y) {
	if (x < 0 || x > 7 || y < 0 || y > 7) throw new exception("x or y outside of range at getChessPiece");
	for (int i = 0; i < 32; i++) {
		if (arr[i].X == x && arr[i].Y == y) return arr[i];
	}
	return {};
}


void buttonAction(int wParam) {

}

void buttonUpdate() {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			LPCWSTR title;
			for (int k = 0; k < 32; k++) {
				if (chessPieces[k].X == j && chessPieces[k].Y == i) {
					title = chessPieces[k].name;
				}
				else
				{
					title = L"";
				}
			}
			int menu = 101 + j + (8 * i);
			btns[i][j] = CreateWindow(
				_T("button"),
				title,
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				5 + Button_Size * j,
				5 + Button_Size * i,
				Button_Size,
				Button_Size,
				hWnd,
				((HMENU)menu),
				hInst,
				NULL
			);
		}

	}
}

enum Phase {
	Pick,
	Step
};