
#include "ObjectManager.h"

void ObjectManager::New(Object* obj)
{
	objs.push_back(obj);
}

void ObjectManager::Delete(Object*)
{
	
}

void ObjectManager::Delete(const int idx)
{

}

void ObjectManager::Delete(std::vector<Object*>::iterator iter)
{

}

auto ObjectManager::Iterator(int mode) const
{
	return (mode == 0) ? objs.begin() : objs.end();
}

void ObjectManager::Initialize()
{
	//Write down objects in first frame.
	
}