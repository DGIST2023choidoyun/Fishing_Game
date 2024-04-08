#pragma once

//#include <iostream>
#include <vector>
//#include "stdafx.h" //**

#include "Vector.h"
//using namespace std;

class Sprite;

class Object
{
private:
	Sprite* sprite;
	float mass;
	float inv_mass;
public:
	static std::vector<Object*> objs;

	VECTOR2<float> position;
	VECTOR2<float> velocity;
	VECTOR2<float> accel;

	float gravityScale = 9.8f;

	bool interact = true; //== Collide ?
public:
	Object();
	Object(const VECTOR2<float> pos, const float m);
	Object(const VECTOR2<float> pos, Sprite* sp);
	~Object();
	void SetSprite(Sprite* sp);
	void SetMass(float m);

private:
	void Physics(double dt);

public:
	void Simulating(double dt);
	void Draw(HDC hdc);

	void SetForce(const VECTOR2<float> f);
	void ApplyForce(const VECTOR2<float> f);

	virtual void Remove();
protected:
	virtual void Process(double dt);
	virtual void OnScr(HDC hdc);
	virtual void OnColliding(Object& victim);
	virtual void OnCollided(Object& offender);
};
