

#include "Fluid.h"


Fluid::SurfaceElement::SurfaceElement()
{
	position = VECTOR2_ZERO_F;
	velocity = VECTOR2_ZERO_F;

	energyPerMass = 0;
}
Fluid::SurfaceElement::SurfaceElement(const vf& pos) : SurfaceElement()
{
	position.x = pos.x;
	position.y = pos.y;

}

void Fluid::SurfaceElement::SetVelocity(const vf& v)
{
	float mag;

	velocity.x = v.x;
	velocity.y = v.y;

	mag = (float)velocity.Magnitude();
	energyPerMass = mag * mag * 0.5f;

}
void Fluid::SurfaceElement::AddVelocity(const vf& v)
{
	float mag;

	velocity += v;

	mag = (float)velocity.Magnitude();
	energyPerMass = mag * mag * 0.5f;

}

void Fluid::SurfaceElement::AddPosition(const vf& p)
{
	position += p;
}

vf Fluid::SurfaceElement::GetPosition() const
{
	return position;
}

float Fluid::SurfaceElement::GetEnergy() const
{
	return energyPerMass;
}

void Fluid::SurfaceElement::Interact(const double dt, const SurfaceElement* nei, const float threshold)
{
	vf rel = position - nei->position;
	if (position.Distance(nei->position) <= threshold)
	{
		velocity -= rel.Normalized() * 50;
	}
	else
	{
		velocity += rel.Normalized() * 50;
	}
	position += velocity * dt;
}

Fluid::FixedSurfaceElement::FixedSurfaceElement(const vf& pos) : SurfaceElement(pos)
{
	EMPTY
}

void Fluid::FixedSurfaceElement::SetVelocity(const vf& v)
{
	float mag;

	velocity.y = (float)v.Magnitude();

	mag = (float)velocity.Magnitude();
	energyPerMass = mag * mag * 0.5f;

}

void Fluid::FixedSurfaceElement::AddVelocity(const vf& v)
{
	float mag;

	velocity.y += (float)v.Magnitude();

	mag = (float)velocity.Magnitude();
	energyPerMass = mag * mag * 0.5f;

}

void Fluid::FixedSurfaceElement::AddPosition(const vf& p)
{
	EMPTY
}

void Fluid::FixedSurfaceElement::Interact(const double dt, const SurfaceElement* nei, const float threshold)
{
	vf rel = position - nei->GetPosition();
	if (position.Distance(nei->GetPosition()) <= threshold)
	{
		velocity.y -= rel.y * 50;
	}
	else
	{
		velocity.y += rel.y * 50;
	}
	position += velocity * dt;
}


Fluid::Fluid()
{
	gravityScale = 0;
	interact = false;

	FixedSurfaceElement* leftEnd = new FixedSurfaceElement(vf(0, rand() % 40 + 200.0f));//sea level 220
	FixedSurfaceElement* rightEnd = new FixedSurfaceElement(vf(SCR_X, rand() % 40 + 200.0f));//sea level 220

	leftEnd->SetVelocity(vf(0, rand() % 100 - 50.0f));
	rightEnd->SetVelocity(vf(0, rand() % 100 - 50.0f));

	surface.push_back(leftEnd);
	surface.push_back(rightEnd);

	sz = 0;
	thresholdGap = SCR_X * 0.5f;
}

void Fluid::AddVertex()
{
	SurfaceElement* ele = new SurfaceElement(vf(rand() % 60 - 30 - thresholdGap + SCR_X, rand() % 40 + 200.0f));//sea level 220
	float vx = rand() % 100 - 50.0f;
	SurfaceElement* rightEnd = surface.back();
	surface.pop_back();

	for (auto iter = surface.begin() + 1; iter != surface.end(); iter++)
	{
		(*iter)->AddPosition(vf(-thresholdGap, 0));
	}

	ele->SetVelocity(vf(vx, abs(vx) / vx * sqrt(2500 - vx * vx)));
	
	surface.push_back(ele);

	sz++;
	
	thresholdGap *= sz / (sz + 1);

	surface.push_back(rightEnd);
}

void Fluid::Draw(HDC hdc)
{
	auto prev = surface.front()->GetPosition();
	MoveToEx(hdc, prev.x, prev.y, nullptr);

	for (auto iter = surface.begin(); iter != surface.end(); iter++)
	{
		auto cur = (*iter)->GetPosition();
		LineTo(hdc, prev.x, prev.y);
		MoveToEx(hdc, cur.x, cur.y, nullptr);
		
		prev = cur;
	}
}

void Fluid::Process(const double dt)
{
	for (int i = 0; i < sz + 1; i++) // Interact each other that is next to => end has to be excluded.
	{
		surface[i]->Interact(dt, surface[i + 1], thresholdGap);
		surface[i + 1]->Interact(dt, surface[i], thresholdGap);

	}
}