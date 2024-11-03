#pragma once
#include "stdafx.h"

#include "Vector.h"

#include "Sprite.h"
#include "PixelSprite.h"

#include "Object.h"

class Cloud : public Object
{
private:

public:
	Cloud();
protected:
	virtual void Process(double dt);
};

