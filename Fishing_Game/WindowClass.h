#pragma once
//#include <iostream> // For vector

//#include <vector> // For vector
#include "stdafx.h"
#include "Resource.h"
#include <vector>
#include <cmath>


#include "Vector.h"

#include "Sprite.h"
#include "PixelSprite.h"

#include "Object.h"
#include "Cloud.h"

#include "Graphics.h"

#include "ObjectManager.h"

class WindowClass : public Singleton<WindowClass>
{
private:

	HINSTANCE _hInstance;
	HWND _hWnd;

	WCHAR _title[MAX_LOADSTRING];
	WCHAR _windowClass[MAX_LOADSTRING];

	int _scrSize[2];//0: Width, 1: Height
	RECT _scrArea;

	Graphics* _graphics;

private:
	LARGE_INTEGER _second;
	LARGE_INTEGER _time;
	double _deltaTime;

	enum SCENE { TITLE, MAIN, END };
	SCENE scene = TITLE;

public:
	WindowClass();
	~WindowClass();

	bool Initialize(HINSTANCE hInstance);
	int Run();

	LRESULT AppProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void FrameTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	void Shutdown();
	void Release();


	void ClassLoadString(HINSTANCE hInstance);
	void ResisterClass(HINSTANCE hInstance);
	bool CreateSystemWindow(int sW, int sH);

	void InitializeControl();

	void Simulating();

};

