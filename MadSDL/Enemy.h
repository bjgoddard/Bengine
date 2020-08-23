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

private:
	Collider* m_Collider;
	RigidBody* m_RigidBody;
	SeqAnimation* m_Animation;
	Vec2 m_LastSafePosition;
};
