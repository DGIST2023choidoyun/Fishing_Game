#pragma once

class Object;

class Graphics
{
private:
public:
	void DrawBackground(HDC hdc, int left, int top, int right, int bottom);
	void DrawObjects(HDC hdc, std::vector<Object*> objs);
};

