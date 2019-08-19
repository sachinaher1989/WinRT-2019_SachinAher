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
	static int iPaintFlag = -1;
	HBRUSH hbrush;
	//code
	switch (iMsg)
	{

	case WM_CREATE:
		GetClientRect(hwnd, &rc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		switch (WORD(wParam))
		{
		case 'R':
		case 'r':
			iPaintFlag = 1;
			InvalidateRect(hwnd, &rc, TRUE);
			break;

		case 'G':
		case 'g':
			iPaintFlag = 2;
			InvalidateRect(hwnd, &rc, TRUE);
			break;

		case 'B':
		case 'b':
			iPaintFlag = 3;
			InvalidateRect(hwnd, &rc, TRUE);
			break;

		case 'C':
		case 'c':
			iPaintFlag = 4;
			InvalidateRect(hwnd, &rc, TRUE);
			break;

		case 'M':
		case 'm':
			iPaintFlag = 5;
			InvalidateRect(hwnd, &rc, TRUE);
			break;

		case 'Y':
		case 'y':
			iPaintFlag = 6;
			InvalidateRect(hwnd, &rc, TRUE);
			break;

		case 'W':
		case 'w':
			iPaintFlag = 7;
			InvalidateRect(hwnd, &rc, TRUE);
			break;

		case 'K':
		case 'k':
		default:
			iPaintFlag = 0;
			InvalidateRect(hwnd, &rc, TRUE);
			break;
		}
		break;

	case WM_PAINT:

		//Get changing rectangle
		GetClientRect(hwnd, &rc);

		//Call specialist
		hdc = BeginPaint(hwnd, &ps);

		SetBkColor(hdc, RGB(0, 0, 0));

		switch (iPaintFlag)
		{
		case 1:
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);
			break;

		case 2:
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);
			break;

		case 3:
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);
			break;

		case 4:
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);
			break;

		case 5:
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);
			break;

		case 6:
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);
			break;

		case 7:
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);
			break;

		case 8:
			hbrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);
			break;

			EndPaint(hwnd, &ps);
			break;
		}
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}




