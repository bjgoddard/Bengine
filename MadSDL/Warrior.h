#pragma once
#include "Character.h"
#include "RigidBody.h"
#include "Collider.h"
#include "SpriteAnimation.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Warrior : public Character
{
public:

	Warrior(Properties* props);
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);
	virtual std::string GetName() { return m_Name; }
	virtual SDL_Rect GetCollider() {
		return m_Collider->Get();
	}
	virtual void ProcessCollision(IObject* other);
	Vec2 GetPosition() { return m_LastSafePosition; }

private:
	void AnimationState();

private:
	bool m_IsJumping = false;
	bool m_IsGrounded = false;
	bool m_IsRunning = false;
	bool m_IsFalling = false;
	bool m_IsAttacking = false;
	bool m_IsCrouching = false;

	float m_AttackTime;
	float m_JumpTime;
	float m_JumpForce;

	SpriteAnimation* m_Animation;
	RigidBody* m_RigidBody;
	Collider* m_Collider;
	Vec2 m_LastSafePosition;
	std::string m_Name;
};