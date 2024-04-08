#pragma once

class Object;
class Cloud : public Object
{
private:

public:
	Cloud();
protected:
	virtual void Process(double dt);
};

