#include "CollisionSystem.h"

void CollisionSystem::AddToCollisionList(IObject* obj)
{
	m_ObjectList.push_back(obj);
}

void CollisionSystem::RemoveFromCollisionList(IObject* obj)
{
	std::vector<IObject*>::iterator newEnd = std::remove(m_ObjectList.begin(), m_ObjectList.end(), obj);
	m_ObjectList.erase(newEnd, m_ObjectList.end());
}

bool CollisionSystem::CheckCollision(SDL_Rect a, SDL_Rect b)
{
		bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
		bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
		return (x_overlaps && y_overlaps);
}

void CollisionSystem::ProcessCollisionList()
{
	for (int i = 0; i < m_ObjectList.size(); i++) {
		IObject* currObj = m_ObjectList[i];
		SDL_Rect temp = currObj->GetCollider();
		for (int j = 0; j < m_ObjectList.size(); j++) {
			IObject* secondObj = m_ObjectList[j];
			if (currObj != secondObj) {
				SDL_Rect tempJ = secondObj->GetCollider();
				if (CheckCollision(temp, tempJ)) {
					currObj->ProcessCollision(secondObj);
				}
			}
		}
	}
}
