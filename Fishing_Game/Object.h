#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Vector.h"

#include "Sprite.h"

class Sprite;

class Object
{
private:
	Sprite* sprite;
	float mass;
	float inv_mass;
public:
	//static std::vector<Object*> objs;

	vf position;
	vf velocity;
	vf accel;

	float gravityScale = 9.8f;

	bool interact = true; //== Collide ?
public:
	Object();
	Object(const vf& pos, const float m);
	Object(const vf& pos, Sprite* sp);
	~Object();
	void SetSprite(Sprite* sp);
	void SetMass(float m);

private:
	void Physics(const double dt);

public:
	void Simulating(const double dt);
	void Draw(HDC hdc);

	void SetForce(const vf& f);
	void ApplyForce(const vf& f);

	virtual void Remove();
protected:
	virtual void Process(const double dt);
	virtual void OnScr(HDC hdc);
	virtual void OnColliding(Object& victim);
	virtual void OnCollided(Object& offender);
};
