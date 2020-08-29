#pragma once
#include "IObject.h"
#include <vector>
class CollisionSystem
{
private:
	//holds all objects that participate in collision
	std::vector<IObject*> m_ObjectList;
public:
	void AddToCollisionList(IObject* obj);
	void RemoveFromCollisionList(IObject* obj);

	bool CheckCollision(SDL_Rect a, SDL_Rect b);

	void ProcessCollisionList();
	/*std::vector<IObject*> m_ObjectList;*/
};