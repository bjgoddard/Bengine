#pragma once
#include "Vec2.h"
#include "SDL.h"
#include <typeinfo>
#include <string>
class IObject
{
public:
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

	// we use these function to retrieve collision relevant information
	//virtual Vec2 GetPosition() = 0;
	//virtual Vec2 GetSize() = 0;
	virtual SDL_Rect GetCollider() = 0;
	virtual std::string GetName() = 0;

	//Using this function, we notify the object that it collided with something else
	virtual void ProcessCollision(IObject* other) = 0;
	std::string m_Name;
	/*virtual ~ICollidable{};*/
};