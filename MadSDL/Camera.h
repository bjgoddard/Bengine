#pragma once
#include "Point.h"
#include "Vec2.h"
#include <SDL.h>
#include "Engine.h"
class Camera
{
public:
	inline static Camera& get()
	{
		if (s_instance == nullptr)
		{
			s_instance = new Camera();
		}
		return *s_instance;
	}
	inline SDL_Rect GetViewbox() { return m_Viewbox; }
	inline Vec2 GetPosition() { return m_Position; }
	inline void SetTarget(Point* target) { m_Target = target; }
	void Update(float dt);
private:
	Camera() { m_Viewbox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; }
	Point* m_Target;
	Vec2 m_Position;
	SDL_Rect m_Viewbox;
	static Camera* s_instance;
};