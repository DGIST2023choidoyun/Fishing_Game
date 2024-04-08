#include "stdafx.h"
#include <iostream>
#include <vector>

#include "Sprite.h"

#include "Object.h"


Object::Object()
{
	objs.push_back(this);

	position = VECTOR2<float>(0, 0);
	mass = 1;
	inv_mass = 1;
}

Object::Object(const VECTOR2<float> pos, const float m)
{
	objs.push_back(this);

	position = pos;
	mass = m;
	inv_mass = 1 / m;
}

Object::Object(const VECTOR2<float> pos, Sprite* sp)
{
	objs.push_back(this);

	position = pos;
	sprite = sp;
}

void Object::SetSprite(Sprite* sp)
{
	sprite = sp;
}
void Object::SetMass(float m)
{

	if (m <= 0)
	{
		mass = 0;
		inv_mass = 0;
	}
	else
	{
		mass = m;
		inv_mass = 1 / m;
	}
}

void Object::Simulating(double dt)
{
	Physics(dt);
	Process(dt);
}

void Object::SetForce(const VECTOR2<float> f)
{
	accel = f * inv_mass;
}

void Object::ApplyForce(const VECTOR2<float> f)
{
	accel += f * inv_mass;
}

void Object::Remove()
{
	this->~Object();
}

Object::~Object()
{
	if (sprite)
		delete sprite;
	objs.erase(std::find(objs.begin(), objs.end(), this));
}

void Object::Physics(double dt)
{
	accel.y += gravityScale * dt;
	velocity += accel * dt;
	position += velocity * dt;
}
void Object::Draw(HDC hdc)
{
	sprite->Draw(hdc, position);
	OnScr(hdc);
}

void Object::Process(double dt)
{

}
void Object::OnScr(HDC hdc)
{

}
void Object::OnColliding(Object& victim)
{

}
void Object::OnCollided(Object& offender)
{

}