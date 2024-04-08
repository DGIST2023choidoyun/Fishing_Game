#pragma once

class Sprite;
#include "Vector.h"


class PixelSprite : public Sprite
{
private:
	
	int pts;
	VECTOR2<int> PTR vertex;
	int width;
	HPEN framePen;
	HBRUSH brush;
public:
	PixelSprite();
	PixelSprite(VECTOR2<float> pos, int num, VECTOR2<int> PTR v, int w, COLORREF c);
	virtual void Draw(HDC hdc, const VECTOR2<float> objPos) override;
	~PixelSprite();
};

