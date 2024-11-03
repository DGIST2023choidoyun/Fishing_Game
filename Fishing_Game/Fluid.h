#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Vector.h"


#include "Object.h"


class Fluid : public Object
{
private:
	class SurfaceElement
	{
	protected:
		vf position;
		vf velocity;
		//VECTOR2<float> accel;

		float energyPerMass; //Assume mass = 1
	public:
		SurfaceElement();
		SurfaceElement(const vf& pos);

		virtual void SetVelocity(const vf&);
		virtual void AddVelocity(const vf&);
		virtual void AddPosition(const vf&);
		virtual vf GetPosition() const;
		float GetEnergy() const;

		virtual void Interact(const double dt, const SurfaceElement* nei, const float threshold);

	};
	class FixedSurfaceElement : public SurfaceElement
	{
	public:
		FixedSurfaceElement() = delete;
		FixedSurfaceElement(const vf& pos);

		virtual void SetVelocity(const vf&);
		virtual void AddVelocity(const vf&);
		virtual void AddPosition(const vf&) final;

		virtual void Interact(const double dt, const SurfaceElement* nei, const float threshold);

	};
	
	size_t sz; //valid size of surface element
	std::vector<SurfaceElement*> surface;
	float thresholdGap; //For applying force to itself as positive or negative along the gap b/w two element
public:
	Fluid();

	void AddVertex();

	virtual void Draw(HDC hdc);

protected:
	virtual void Process(double dt);
};

