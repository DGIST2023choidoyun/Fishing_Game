#include "WindowClass.h"



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return WindowClass::Instance()->AppProc(hWnd, message, wParam, lParam);
}

WindowClass::WindowClass()
{
	_hInstance = NULL;
	_hWnd = NULL;

	memset(_title, 0, MAX_LOADSTRING);
	memset(_windowClass, 0, MAX_LOADSTRING);

	_scrSize[0] = SCR_X;
	_scrSize[1] = SCR_Y;

	_graphics = new Graphics;
}

WindowClass::~WindowClass()
{
	Shutdown();
}

bool WindowClass::Initialize(HINSTANCE hInstance)
{
	_hInstance = hInstance;

	_scrArea.left = 0;
	_scrArea.right = _scrSize[0];
	_scrArea.top = 0;
	_scrArea.bottom = _scrSize[1];

	ClassLoadString(hInstance);

	ResisterClass(hInstance);

	if (!CreateSystemWindow(_scrSize[0], _scrSize[1]))
	{
		MessageBox(NULL, L"Failed creating window.", L"Error", MB_OK);
		return false;
	}

	

	return true;
}

int WindowClass::Run()
{
	MSG msg;

	QueryPerformanceFrequency(&_second);
	QueryPerformanceCounter(&_time);

	ObjectManager::Instance()->Initialize();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	Shutdown();

	return (int)msg.wParam;
}

void WindowClass::Simulating()
{
	auto objs = ObjectManager::Instance()->objs;
	for (auto iter = objs.begin(); iter != objs.end(); iter++)
	{
		(*iter).get()->Simulating(_deltaTime);
	}
}

LRESULT WindowClass::AppProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		SetWindowText(_hWnd, L"Fishing Game");

		SetTimer(hWnd, GLOBAL_CLOCK, 1, NULL);
		//SetTimer(hWnd, 10, 1, NULL);
		SetTimer(hWnd, 100, 1000, NULL);

		InitializeControl();

		break;
	}

	case WM_DESTROY:
	{

		PostQuitMessage(0);
		break;
	}
	case WM_TIMER:
	{
		FrameTimer(hWnd, message, wParam, lParam);
	}
	break;
	case WM_CLOSE:
	{
		PostQuitMessage(0);

		break;
	}
	case WM_GETMINMAXINFO://Set minimum of window
	{
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = SCR_X + 16;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = SCR_Y + 29;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = SCR_X + 16;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = SCR_Y + 29;

		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);//Start Painting

#pragma region DoubleBuffering

		HDC memoryDC = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, _scrSize[0], _scrSize[1]);//Create bitmap big as window
		HBITMAP oldBit = (HBITMAP)SelectObject(memoryDC, memBit);//Connect bitmap to memory DC and Extend memory DC

		PatBlt(memoryDC, 0, 0, _scrArea.right, _scrArea.bottom, WHITENESS);//Memory DC's white background color
#pragma endregion

		_graphics->DrawBackground(memoryDC, 0, 0, _scrArea.right, _scrArea.bottom);
		_graphics->DrawObjects(memoryDC);

		BitBlt(hdc, 0, 0, _scrArea.right, _scrArea.bottom, memoryDC, 0, 0, SRCCOPY);

		SelectObject(memoryDC, oldBit);
		DeleteObject(memBit);
		DeleteDC(memoryDC);
		EndPaint(hWnd, &ps);

		break;
	}

	case WM_COMMAND:
	{


		break;
	}
	case WM_KEYDOWN:
		break;
	}


	return DefWindowProc(hWnd, message, wParam, lParam);
}

void WindowClass::FrameTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case GLOBAL_CLOCK://Get deltaTime
	{

		LARGE_INTEGER ct;
		QueryPerformanceCounter(&ct);
		_deltaTime = (ct.QuadPart - _time.QuadPart) / (float)_second.QuadPart;

		_time = ct;

		Simulating();

		InvalidateRect(hWnd, &_scrArea, FALSE);

		break;
	}
	case 100:
	{
		/*float x = rand() % 50 + 500;
		float y = rand() % 60 + 20;
		VECTOR2<int> test_vertex[3] = { VECTOR2<int>(-3, -2), VECTOR2<int>(3, -2), VECTOR2<int>(0, 4) };
		Object* newOne = new Object(VECTOR2<float>(x, y), new PixelSprite(VECTOR2_ZERO_F, 3, test_vertex, 5, RGB(0, 0, 0)));
		objs.push_back(newOne);
		
		newOne->gravityScale = 0;
		newOne->velocity.x = -(rand() % 80 + 1);*/

		Cloud* newCl = new Cloud();

		break;
	}
	}
}

void WindowClass::Shutdown()
{

	KillTimer(_hWnd, GLOBAL_CLOCK);

	Release();

	DestroyWindow(_hWnd);
	_hWnd = NULL;

	UnregisterClass(_windowClass, _hInstance);

	_hInstance = NULL;
}

void WindowClass::Release()
{


}

void WindowClass::ClassLoadString(HINSTANCE hInstance)
{
	LoadStringW(hInstance, IDS_APP_TITLE, _title, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_FISHINGGAME, _windowClass, MAX_LOADSTRING);
}

void WindowClass::ResisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;

	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FISHINGGAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _windowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);
}

bool WindowClass::CreateSystemWindow(int sW, int sH)
{
	_hWnd = CreateWindowW(_windowClass, _title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, 0, sW, sH, nullptr, nullptr, _hInstance, nullptr);//forbid maximizing

	if (!_hWnd)
		return false;

	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);

	return true;
}


void WindowClass::InitializeControl()
{
}
