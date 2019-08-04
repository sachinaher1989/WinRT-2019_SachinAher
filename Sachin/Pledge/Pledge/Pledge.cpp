#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpszCmdLine, int iCmdShow)
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
	wndclass.hCursor  = LoadCursor(NULL, IDC_ARROW);
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
	while(GetMessage(&msg, NULL, 0,0))
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

	switch(iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		//Get Changing Rectangle
		GetClientRect(hWnd, &Rc);
		//Call Specialist
		hdc = BeginPaint(hWnd, &ps);
		//Set Text Color
		SetTextColor(hdc, RGB(255,125,0));
		//Set Background Color
		SetBkColor(hdc,RGB(0,0,0));
		//DraewText
		Rc.bottom  =  500;
		DrawText(hdc,TEXT("India is my country."),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rc.bottom += 40;
		DrawText(hdc,TEXT("All Indians are my Brothers and Sisters."),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rc.bottom += 40;
		DrawText(hdc,TEXT("I love my country and "),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rc.bottom += 40;
		DrawText(hdc,TEXT("I am proud of its rich and varied heritage. "),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		
		SetTextColor(hdc, RGB(255,255,255));
		Rc.bottom += 40;
		DrawText(hdc,TEXT("I shall always strive to be worthy of it. "),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rc.bottom += 40;
		DrawText(hdc,TEXT("I shall give my parents,"),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rc.bottom += 40;
		DrawText(hdc,TEXT("teachers and all elders respect and "),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rc.bottom += 40;
		DrawText(hdc,TEXT("treat everyone with courtesy. "),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);


		SetTextColor(hdc, RGB(0,255,0));
		Rc.bottom += 40;
		DrawText(hdc,TEXT("To my country and my people,"),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rc.bottom += 40;
		DrawText(hdc,TEXT("I pledge my devotion. "),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rc.bottom += 40;
		DrawText(hdc,TEXT("In their well being and prosperity alone, "),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rc.bottom += 40;
		DrawText(hdc,TEXT("lies my happiness. "),-1,&Rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		//Set back Specialist and stop painting
		EndPaint(hWnd, &ps);
		break;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}
