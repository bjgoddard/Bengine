#pragma once
#include "Character.h"
#include "RigidBody.h"
#include "Collider.h"
#include "SeqAnimation.h"
#include "SpriteAnimation.h"
#include "Warrior.h"

#define VJUMP_TIME 15.0f
#define VJUMP_FORCE 10.0f

#define VRUN_FORCE 4.0f
#define VATTACK_TIME 20.0f

class Viking : public Character
{
public:
	Viking(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);


	std::string GetName() { return m_Name; }
	virtual SDL_Rect GetCollider() {
		return m_Collider->Get();
	}
	virtual void ProcessCollision(IObject* other) { std::cout << "Viking Collision" << std::endl; }
	Warrior* player;
	Vec2 GetPosition() { return m_LastSafePosition; }

private:
	void AnimationState();
	void VikingAI(float dt);

	bool m_IsJumping = false;
	bool m_IsGrounded = false;
	bool m_IsRunning = false;
	bool m_IsFalling = false;
	bool m_IsAttacking = false;
	bool m_IsCrouching = false;
	bool m_InCombat = false;

	float m_AttackTime;
	float m_JumpTime;
	float m_JumpForce;


	Collider* m_Collider;
	Collider* m_AttackCollider;
	RigidBody* m_RigidBody;
	SeqAnimation* m_Animation;
	Vec2 m_LastSafePosition;
	std::string m_Name;
};