
#include "PixelSprite.h"

PixelSprite::PixelSprite()
{
	position.x = position.y = 0;
	pts = 1;
	vertex = new vi;
	vertex[0] = vi(0, 0);
	width = 1;
}

PixelSprite::PixelSprite(vf pos, int num, vi PTR v, int w, COLORREF c)
{
	position = pos;
	
	if (num <= 0)
		num = 1;
	pts = num;
	vertex = new vi[num];

	for (int i = 0; i < num; i++)
		vertex[i] = v[i];
	
	width = w;

	framePen = CreatePen(PS_SOLID, w, c);

}

void PixelSprite::Draw(HDC hdc, const vf objPos)
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