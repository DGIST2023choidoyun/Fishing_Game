#pragma once

#include "stdafx.h"
//#include <iostream>
//#include <vector>

#include "Object.h"

class Graphics
{
private:
public:
	void DrawBackground(HDC hdc, int left, int top, int right, int bottom);
	void DrawObjects(HDC hdc);
};

