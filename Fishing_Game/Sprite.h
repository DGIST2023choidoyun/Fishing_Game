#pragma once
#include "stdafx.h"
#include "Vector.h"


class Sprite
{
protected:
	vf position;
public:
	Sprite();
	virtual void Draw(HDC hdc, const vf objPos) = 0;
};

