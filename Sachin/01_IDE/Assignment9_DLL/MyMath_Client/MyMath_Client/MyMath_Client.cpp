#include <windows.h>
#include "stdafx.h"
#include <stdio.h>
//#include <stdlib.h>
#include "MyMath.h"
#define _CRT_SECURE_NO_WARNINGS
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("MyApplication"),
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

	// MessageLoop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT Rc;
	TCHAR str[] = TEXT("Hello World");
	CHAR str2[255];
	int i = 5;

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		sprintf_s(str2, "square of %d is %d", i, MakeSquare(i));
		MessageBox(hWnd, str2, (TEXT("Square")), MB_OK);
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		//Get Changing Rectangle
		GetClientRect(hWnd, &Rc);
		//Call Specialist
		hdc = BeginPaint(hWnd, &ps);
		//Set Text Color
		SetTextColor(hdc, RGB(0, 255, 0));
		//Set Background Color
		SetBkColor(hdc, RGB(0, 0, 0));
		//DrawText
		DrawText(hdc, str, -1, &Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//Set back Specialist and stop painting
		EndPaint(hWnd, &ps);
		break;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}