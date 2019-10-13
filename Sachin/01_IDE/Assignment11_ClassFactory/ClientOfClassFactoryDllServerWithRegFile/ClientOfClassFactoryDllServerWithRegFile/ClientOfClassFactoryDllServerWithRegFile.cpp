#include <windows.h>
#include "stdafx.h"
#include "ClientOfClassFactoryDllServerWithRegFile.h"
#include "ClassFactoryDllServerWithRegFile.h"

#define MESSAGE_MACRO  0
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ComClient");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM library cannot be initialized.\n Program will now exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("CoInitialize success"), TEXT("Program No Error"), MB_OK);
#endif
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
	CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//void SafeInterfaceRelease();
	HRESULT hr;
	int iNum1, iNum2, iSum;
	TCHAR str[255];


	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
#if MESSAGE_MACRO
			MessageBox(NULL, TEXT("ISum Interface cannot be obtained"), TEXT("Error"), MB_OK);
#endif
			DestroyWindow(hWnd);
		}
		iNum1 = 100;
		iNum2 = 55;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iSum);
		MessageBox(hWnd, str, TEXT("Result"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISubtract Interface cannot be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hWnd);
		}

		pISum->Release();
		pISum = NULL;

		iNum1 = 100;
		iNum2 = 55;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);
		pISubtract->Release();
		pISubtract = NULL;

		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, iSum);
		MessageBox(hWnd, str, TEXT("Result"), MB_OK);

		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}

void SafeIntefaceRelease(void)
{
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
}