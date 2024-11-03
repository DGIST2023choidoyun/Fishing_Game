#pragma once

#include "stdafx.h"
#include "Vector.h"

#include "Sprite.h"


class PixelSprite : public Sprite
{
private:
	
	int pts;
	vi PTR vertex;
	int width;
	HPEN framePen;
	HBRUSH brush;
public:
	PixelSprite();
	PixelSprite(vf pos, int num, vi PTR v, int w, COLORREF c);
	virtual void Draw(HDC hdc, const vf objPos) override;
	~PixelSprite();
};

