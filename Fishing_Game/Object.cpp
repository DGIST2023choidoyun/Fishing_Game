
#include "Object.h"

#include "ObjectManager.h"

//std::vector<Object*> Object::objs;

Object::Object()
{
	ObjectManager::Instance()->New(this);

	position = VECTOR2_ZERO_F;
	mass = 1;
	inv_mass = 1;
}

Object::Object(const vf& pos, const float m)
{
	ObjectManager::Instance()->New(this);

	position = pos;
	mass = m;
	inv_mass = 1 / m;
}

Object::Object(const vf& pos, Sprite* sp)
{
	ObjectManager::Instance()->New(this);

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

void Object::Simulating(const double dt)
{
	Physics(dt);
	Process(dt);
}

void Object::SetForce(const vf& f)
{
	accel = f * inv_mass;
}

void Object::ApplyForce(const vf& f)
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
	ObjectManager::Instance()->Delete(this);
}

void Object::Physics(const double dt)
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

void Object::Process(const double dt)
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