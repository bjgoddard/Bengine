#pragma once
#include "GameObject.h"
#include <SDL.h>
class Character : public GameObject
{
public:
	Character(Properties* props) : GameObject(props)
	{}

	virtual void Draw() = 0;
	virtual void Clean() = 0;
	virtual void Update(float dt) = 0;
	virtual SDL_Rect GetCollider() = 0;
	virtual std::string GetName() = 0;
	virtual void ProcessCollision(IObject* other) = 0;

protected:
	std::string m_Name;
};