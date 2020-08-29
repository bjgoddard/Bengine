#include "Enemy.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include <iostream>

Enemy::Enemy(Properties* props) : Character(props)
{
	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(10.0f);
	m_Collider = new Collider();
	//m_Collider->SetBuffer(0, -100, 0, 0);

	m_Animation = new SeqAnimation(false);
	m_Animation->Parse("assets/boss_animation.aml");
	m_Animation->SetCurrentSeq("boss_appear");

	m_Name = "boss";
}


void Enemy::Draw()
{
	m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 0.3f, 0.3f, 1.0f, m_Flip);
	m_Collider->Draw();
}

void Enemy::Update(float dt)
{
	//x axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 140, 100);

	/*m_RigidBody->ApplyForceX(3); */

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
		m_Animation->SetCurrentSeq("boss_idle");
		m_Animation->SetRepeat(true);
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;
}

void Enemy::Clean()
{

}