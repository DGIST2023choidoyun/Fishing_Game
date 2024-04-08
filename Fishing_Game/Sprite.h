#pragma once

#include "Vector.h"


class Sprite
{
protected:
	VECTOR2<float> position;
public:
	Sprite();
	virtual void Draw(HDC hdc, const VECTOR2<float> objPos) = 0;
};

