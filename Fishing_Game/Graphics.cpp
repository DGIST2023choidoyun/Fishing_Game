#include "Graphics.h"

#include "ObjectManager.h"


void Graphics::DrawBackground(HDC hdc, int left, int top, int right, int bottom)
{
	HBRUSH dockBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, dockBrush);

	Rectangle(hdc, 0, 186, 85, 196);
	Rectangle(hdc, 75, 196, 78, 236);
	Rectangle(hdc, 50, 196, 53, 236);
	Rectangle(hdc, 25, 196, 28, 236);
	Rectangle(hdc, 3, 196, 6, 236);

	Rectangle(hdc, 82, 171, 84, 186);

	DeleteObject(SelectObject(hdc, oldBrush));

	HPEN plyPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, plyPen);

	MoveToEx(hdc, 84, 185, nullptr);
	LineTo(hdc, 87, 184);
	MoveToEx(hdc, 87, 184, nullptr);
	LineTo(hdc, 86, 190);


	DeleteObject(SelectObject(hdc, oldPen));



	Ellipse(hdc, 80, 171, 85, 176);
}

void Graphics::DrawObjects(HDC hdc)
{
	for (auto iter = ObjectManager::Instance()->Iterator(BEGIN); iter != ObjectManager::Instance()->Iterator(END); iter++)
	{
		(*iter)->Draw(hdc);
	}
}