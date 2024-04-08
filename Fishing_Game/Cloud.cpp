#include "stdafx.h"

#include "Vector.h"

#include "Sprite.h"
#include "PixelSprite.h"

#include "Object.h"
#include "Cloud.h"


Cloud::Cloud()
{
	position.x = 530;
	position.y = rand() % 80 + 20;
	
	SetMass(0);
	gravityScale = 0;
	
	velocity.x = -50 - rand() % 20;
	velocity.y = 0;

	VECTOR2<int> test_vertex[3] = { VECTOR2<int>(-3, -2), VECTOR2<int>(3, -2), VECTOR2<int>(0, 4) };
	SetSprite((Sprite*)(new PixelSprite(VECTOR2_ZERO_F, 3, test_vertex, 5, RGB(0, 255, 255))));
}
void Cloud::Process(double dt)
{
	if (position.x < 100)
	{
		Remove();
	}
}
