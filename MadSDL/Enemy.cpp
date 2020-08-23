#include "Enemy.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"
#include <iostream>

static Registrar<Enemy> registrar("BOSS");

Enemy::Enemy(Properties* props) : Character(props)
{
	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(3.5);
	m_Collider = new Collider();

	m_Animation = new SeqAnimation(false);
	m_Animation->Parse("assets/animation.aml");
	m_Animation->SetCurrentSeq("boss_appear");
}

void Enemy::Draw()
{
	m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 0.3f, 0.3f, m_Flip);
	m_Collider->Draw();
}

void Enemy::Update(float dt)
{
	//x axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 140, 100);

	if (CollisionHandler::get()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}

	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 140, 100);

	if (CollisionHandler::get()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}

	m_Animation->Update(dt);

	if (m_Animation->IsEnded()) {
		m_Animation->SetCurrentSeq("boss_appear");
		m_Animation->SetRepeat(false);
	}
}

void Enemy::Clean()
{

}