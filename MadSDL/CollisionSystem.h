#pragma once
#include "IObject.h"
#include <vector>
class CollisionSystem
{
private:
	std::vector<IObject*> m_ObjectList;
public:
	void AddToCollisionList(IObject* obj);
	void RemoveFromCollisionList(IObject* obj);

	bool CheckCollision(SDL_Rect a, SDL_Rect b);

	void ProcessCollisionList();
};