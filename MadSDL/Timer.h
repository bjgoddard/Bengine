#pragma once

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer
{
public:
	void Tick();
	inline float GetDeltaTime() { return m_DeltaTime; }
	inline static Timer* get()
	{
		if (s_instance == nullptr)
		{
			s_instance = new Timer();
		}
	return s_instance;
	}
private:
	Timer() {}
	static Timer* s_instance;
	float m_DeltaTime;
	float m_LastTime;
};