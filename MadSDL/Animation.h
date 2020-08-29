#pragma once
#include <SDL.h>
#include <string>

class Animation
{
public:
	Animation(bool repeat) : m_Repeat(repeat) { m_IsEnded = false; }

	virtual void Update(float dt) = 0;
	inline bool IsEnded() { return m_IsEnded; }
	int m_CurrentFrame;
	bool m_IsEnded;
protected:
	bool m_Repeat;
	
	
};
