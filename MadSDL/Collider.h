#pragma once
#include <SDL.h>
#include "Camera.h"
#include "CollisionHandler.h"

class Collider
{
public:
	inline SDL_Rect Get() { return m_Box; }
	inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x, y, w, h }; }

	void Set(int x, int y, int w, int h)
	{
		m_Box = {
			x - m_Buffer.x,
			y - m_Buffer.y,
			w - m_Buffer.w,
			h - m_Buffer.h
		};
	}
	void Draw() {
		Vec2 cam = Camera::get().GetPosition();
		SDL_Rect box = { (int)(m_Box.x - cam.X), (int)(m_Box.y - cam.Y), m_Box.w, m_Box.h };
		SDL_RenderDrawRect(Engine::get().getRenderer(), &box);
	}

private:
	SDL_Rect m_Box;
	SDL_Rect m_Buffer;
};