#pragma once
#include "Vec2.h"

#define UNI_MASS 1.0f
#define GRAVITY 10.0f

#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1

class RigidBody
{
public:
	RigidBody() 
	{
		m_Mass = UNI_MASS;
		m_Gravity = GRAVITY;
	}
	
	inline void SetMass(float mass) { m_Mass = mass; }
	inline void SetGravity(float gravity) { m_Gravity = gravity; }

	inline void ApplyForce(Vec2 F) { m_Force = F; }
	inline void ApplyForceX(float Fx) { m_Force.X = Fx; }
	inline void ApplyForceY(float Fy) { m_Force.Y = Fy; }
	inline void UnsetForce() { m_Force = Vec2(0, 0); }

	inline void ApplyFriction(Vec2 Fr) { m_Friction = Fr; }
	inline void UnsetFriction() { m_Friction = Vec2(0, 0); }

	inline float GetMass() { return m_Mass; }
	inline Vec2 Position() { return m_Position; }
	inline Vec2 Velocity() { return m_Velocity; }
	inline Vec2 Acceleration() { return m_Acceleration; }

	void Update(float dt)
	{
		m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
		m_Acceleration.Y = m_Gravity + m_Force.Y/m_Mass;
		m_Velocity = m_Acceleration;
		m_Position = m_Velocity;
	}


private:
	float m_Mass;
	float m_Gravity;

	Vec2 m_Force;
	Vec2 m_Friction;

	Vec2 m_Position;
	Vec2 m_Velocity;
	Vec2 m_Acceleration;
};