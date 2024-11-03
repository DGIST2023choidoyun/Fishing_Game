#pragma once
#include "stdafx.h"
#include <iostream>
#include <map>
#include "Object.h"
#include "Fluid.h"

#define BEGIN	0
#define END		1


class Object;
class ObjectManager : public Singleton<ObjectManager>
{
private:
	std::vector<Object*> objs;
public:
	void New(Object*);
	void Delete(Object*);
	void Delete(const int idx);
	void Delete(std::vector<Object*>::iterator iter);
	
	auto Iterator(int mode) const;

	void Initialize();
};

