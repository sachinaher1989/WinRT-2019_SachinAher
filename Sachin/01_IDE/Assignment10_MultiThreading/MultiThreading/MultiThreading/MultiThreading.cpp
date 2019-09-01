#include <windows.h>
#include "stdafx.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

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
	HANDLE hTHread1 = NULL;
	HANDLE hTHread2 = NULL;
	switch (iMsg)
	{

	case WM_CREATE:
		hTHread1 = CreateThread(NULL, 0, ThreadProcOne, (LPVOID)hWnd, 0, NULL);
		hTHread2 = CreateThread(NULL, 0, ThreadProcTwo, (LPVOID)hWnd, 0, NULL);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, TEXT("LBUTTONDOWN is arrived"), TEXT("LBUTTONDOWN"), MB_OK);
		break;
	case WM_DESTROY:
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
		//DraewText
		DrawText(hdc, str, -1, &Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//Set back Specialist and stop painting
		EndPaint(hWnd, &ps);
		break;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID Param)
{
	HDC hdc;
	unsigned long int i;
	TCHAR str[255];

	hdc = GetDC((HWND)Param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));

	for (i = 0; i < 4294967295; i++)
	{
		wsprintf(str, TEXT("ThreadOne -> Increasing order: %lu"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}
	ReleaseDC((HWND)Param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID Param)
{
	HDC hdc;
	unsigned long int i;
	TCHAR str[255];

	hdc = GetDC((HWND)Param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));

	for (i = 4294967295; i > 0; i--)
	{
		wsprintf(str, TEXT("ThreadTwo -> Decreasing order: %lu"), i);
		TextOut(hdc, 5, 30, str, wcslen(str));
	}
	ReleaseDC((HWND)Param, hdc);
	return 0;
}

