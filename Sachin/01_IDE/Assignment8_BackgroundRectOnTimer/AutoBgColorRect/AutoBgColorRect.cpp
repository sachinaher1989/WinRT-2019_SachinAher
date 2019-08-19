// MyWindow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Headers
#include "stdafx.h"
#include <windows.h>

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR
	lpszCmdLine, int iCmdShow)
{
	// variabe declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	// initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
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

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rc;
	static int iPaintFlag = 0;
	static int iPrevPaintFlag = 0;
	UINT_PTR MyTimer = 1;
	HBRUSH hbrush;
	static INT var = 0;
	static INT var1 = 0;
	//code
	switch (iMsg)
	{

	case WM_CREATE:
		GetClientRect(hwnd, &rc);
		rc.left = 0;
		var = rc.right/8;
		rc.right = var;
		SetTimer(hwnd, MyTimer, 2000, NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		KillTimer(hwnd, MyTimer);
		
		if (iPaintFlag == 8)
		{
			iPaintFlag = 0;
			GetClientRect(hwnd, &rc);
			rc.left = 0;
			var = rc.right / 8;
			rc.right = var;
		}
	
		InvalidateRect(hwnd, &rc, TRUE);

		rc.right += var;
		rc.left += var;
		iPaintFlag++;
		SetTimer(hwnd, MyTimer, 200, NULL);
		break;


	case WM_PAINT:

		//Call specialist
		hdc = BeginPaint(hwnd, &ps);

		//SetBkColor(hdc, RGB(0, 0, 0));
		
		switch (iPaintFlag)
		{
		case 1:
			//rc.left = (2 * rc.left / 8);
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &ps.rcPaint, hbrush);
			break;

		case 2:
			//rc.left += (2 * rc.left / 8);
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &ps.rcPaint, hbrush);
			break;

		case 3:
			//rc.left += (2 * rc.left / 8);
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &ps.rcPaint, hbrush);
			break;

		case 4:
			//rc.left += (2 * rc.left / 8);
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &ps.rcPaint, hbrush);
			break;

		case 5:
			//rc.left += (2 * rc.left / 8);
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &ps.rcPaint, hbrush);
			break;

		case 6:
			//rc.left += (2 * rc.left / 8);
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &ps.rcPaint, hbrush);
			break;

		case 7:
			//rc.left += (2 * rc.left / 8);
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &ps.rcPaint, hbrush);
			break;

		case 8:
		default:
			//rc.left += (2 * rc.left / 8);
			hbrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &ps.rcPaint, hbrush);
			break;
		}
		EndPaint(hwnd, &ps);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}




