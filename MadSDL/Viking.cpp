#include "Viking.h"
#include "Camera.h"
#include "Input.h"
#include "Warrior.h"
#include <iostream>
#include <algorithm>
#include <cmath>



Viking::Viking(Properties* props) : Character(props)
{
	m_AttackTime = VATTACK_TIME;
	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(10.0f);
	m_Collider = new Collider();
	m_Collider->SetBuffer(-100, -140, 0, 0);
	m_Animation = new SeqAnimation(false);
	m_Animation->Parse("assets/viking_animation.aml");
	m_Animation->SetCurrentSeq("viking_idle");
	m_Animation->SetRepeat(false);
	m_AttackCollider = new Collider();
	m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 50, 50);
	m_Name = "viking";
}

void Viking::Draw()
{
	m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 4.0f, 4.0f, 1.0f, m_Flip);
	//m_Collider->Draw();
	//m_AttackCollider->Draw();
}

void Viking::Update(float dt)
{
	if (m_IsAttacking && m_AttackTime > 0) {
		m_AttackTime -= dt;
	}
	else {
		m_IsAttacking = false;
		m_AttackTime = VATTACK_TIME;
	}
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 50, 50);
	m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 50, 50);

	if (CollisionHandler::get()->MapCollision(m_Collider->Get()))
	{
		m_Transform->X = m_LastSafePosition.X;
	}
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 50, 50);
	m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 50, 50);

	if (CollisionHandler::get()->MapCollision(m_Collider->Get()))
	{
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else
	{
		m_IsGrounded = false;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	if (player != nullptr) {
		Vec2 playerPos = player->GetPosition();
		Vec2 vikingPos = this->GetPosition();
		Vec2 playerDist = playerPos - vikingPos;
		float aggroRange = 300.0f;
		if (std::abs(playerDist.X) < aggroRange) {
			m_InCombat = true;
		}
		if (m_InCombat) {

			//RIGHT ATTACK
			if (playerDist.X > 0.0f && playerDist.X < 160.0f) {
				m_IsAttacking = true;
				m_Flip = SDL_FLIP_NONE;
			}
			//LEFT ATTACK
			else if (playerDist.X < 0.0f && playerDist.X > -50.0f ) {

				m_IsAttacking = true;
				m_Flip = SDL_FLIP_HORIZONTAL;
				m_AttackCollider->SetBuffer(-15, -140, 0, 0);
			}
			//LEFT MOVE
			else if (playerDist.X < 0.0f && !m_IsAttacking) {
				m_IsRunning = true;
				m_Flip = SDL_FLIP_HORIZONTAL;
				m_Transform->TranslateX(-0.5f);
			}
			//RIGHT MOVE
			else if (playerDist.X > 0.0f ) {
				m_IsRunning = true;
				m_Flip = SDL_FLIP_NONE;
				m_Transform->TranslateX(0.5f);
			}
		}
	}
	AnimationState();
	m_Animation->Update(dt);
}

void Viking::AnimationState()
{
	if (m_IsRunning) {
		m_Animation->SetCurrentSeq("viking_run");
	}

	if (m_IsAttacking) {
		m_Animation->SetCurrentSeq("viking_attack");
	}
}

void Viking::VikingAI(float dt)
{
	if (m_IsRunning && !m_IsAttacking) {
		m_Animation->SetCurrentSeq("viking_run");
	}

	if (m_IsAttacking && m_Animation->IsEnded()) {
		m_Animation->SetCurrentSeq("viking_attack");
	}

	Vec2 playerPos = player->GetPosition();
	Vec2 vikingPos = this->GetPosition();
	Vec2 playerDist = playerPos - vikingPos;
	float aggroRange = 300.0f;
	if (std::abs(playerDist.X) < aggroRange) {
		m_InCombat = true;
	}
	if (m_InCombat) {
		if (playerDist.X > 0.0f && playerDist.X < 160.0f && !m_IsAttacking) {
			m_IsAttacking = true;
			m_Flip = SDL_FLIP_NONE;
			std::cout << "attack1" << std::endl;

		}
		else if (playerDist.X < 0.0f && playerDist.X > -50.0f && !m_IsAttacking) {

			m_IsAttacking = true;
			m_Flip = SDL_FLIP_HORIZONTAL;
			m_AttackCollider->SetBuffer(-15, -140, 0, 0);
			std::cout << "attack2" << std::endl;
		}
		else if (playerDist.X < 0.0f && !m_IsAttacking) {
			m_IsRunning = true;
			m_Flip = SDL_FLIP_HORIZONTAL;
			m_Transform->TranslateX(-0.5f);
		}
		else if (playerDist.X > 0.0f && !m_IsAttacking) {
			m_IsRunning = true;
			m_Flip = SDL_FLIP_NONE;
			m_Transform->TranslateX(0.5f);
		}
	}
}

void Viking::Clean()
{
	TextureManager::get().Drop(m_TextureID);
}

