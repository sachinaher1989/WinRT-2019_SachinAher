#include <windows.h>
#include "stdafx.h"
#include "WindowsProject1.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("MyWIndowApp");
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	wndclass.hInstance = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("SaChIn's Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	 HDC hdc, cdc;
	 PAINTSTRUCT ps;
	 RECT rc;
	 HINSTANCE hInstance;
	 static HBITMAP hbitSS;
	 BITMAP bitSS;

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		//MessageBox(hwnd, TEXT("WM_CREATE is arrived"), TEXT("WM_CREATE"), MB_OK | MB_ICONINFORMATION);
		hInstance = GetModuleHandle(NULL);
		hbitSS = LoadBitmap(hInstance, MAKEINTRESOURCE(MY_BITMAP));
		if (hbitSS == NULL)
		{
			MessageBox(hwnd, TEXT("BMP didnt load !"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		break;

	case WM_LBUTTONDOWN:
		MessageBeep(true);
		break;
	case WM_KEYDOWN:
		switch (WORD(wParam))
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;

	case WM_PAINT:

		//Call specialist
		hdc = BeginPaint(hwnd, &ps);
		
		//Get changing rectangle
		GetClientRect(hwnd, &rc);

		cdc = CreateCompatibleDC(NULL);
		SelectObject(cdc, hbitSS);
		GetObject(hbitSS, sizeof(BITMAP), &bitSS);
		StretchBlt(hdc,
			rc.left,
			rc.top,
			rc.right - rc.left,
			rc.bottom - rc.top,
			cdc,
			0,
			0,
			bitSS.bmWidth,
			bitSS.bmHeight,
			SRCCOPY);



		//Set the text color
		SetTextColor(hdc, RGB(0, 255, 0));

		// set background coor
		//SetBkColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		DeleteObject(cdc);
		// Draw Actual text
		DrawText(hdc, TEXT(" Hello Window "), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			// Set back specialist and stop painting
		EndPaint(hwnd, &ps);
		break;
	}


	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


