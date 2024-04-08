#include "stdafx.h"


#include "Sprite.h"
#include "PixelSprite.h"

PixelSprite::PixelSprite()
{
	position.x = position.y = 0;
	pts = 1;
	vertex = new VECTOR2<int>;
	vertex[0] = VECTOR2<int>(0, 0);
	width = 1;
}

PixelSprite::PixelSprite(VECTOR2<float> pos, int num, VECTOR2<int> PTR v, int w, COLORREF c)
{
	position = pos;
	
	if (num <= 0)
		num = 1;
	pts = num;
	vertex = new VECTOR2<int>[num];

	for (int i = 0; i < num; i++)
		vertex[i] = v[i];
	
	width = w;

	framePen = CreatePen(PS_SOLID, w, c);

}

void PixelSprite::Draw(HDC hdc, const VECTOR2<float> objPos)
{
	HPEN oldPen = (HPEN)SelectObject(hdc, framePen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

	for (int i = 0; i < pts; i++)
		Ellipse(hdc, objPos.x + vertex[i].x - (width - 1) / 2, objPos.y + vertex[i].y - (width - 1) / 2, objPos.x + vertex[i].x + width - 1, objPos.y + vertex[i].y + width - 1);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

PixelSprite::~PixelSprite()
{
	DeleteObject(framePen);
	DeleteObject(brush);

	if (vertex)
		delete[] vertex;
}