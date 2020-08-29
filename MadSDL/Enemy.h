#pragma once
#include "Character.h"
#include "RigidBody.h"
#include "Collider.h"
#include "SeqAnimation.h"
#include "SpriteAnimation.h"


class Enemy : public Character
{
public:
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

	std::string GetName() { return m_Name; }
	//Collider* GetCollider() { return m_Collider; }
	virtual SDL_Rect GetCollider() {
		return m_Collider->Get();
	}

	//Using this function, we notify the object that it collided with something else
	virtual void ProcessCollision(IObject* other) { std::cout << "Enemy Collision" << std::endl; }

private:
	Collider* m_Collider;
	RigidBody* m_RigidBody;
	SeqAnimation* m_Animation;
	Vec2 m_LastSafePosition;
	std::string m_Name;
};
