#pragma once
#include <SDL.h>
#include <vector>
#include "TileLayer.h"
#include "GameMap.h"
#include "Engine.h"

class CollisionHandler
{
public:
	static bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool MapCollision(SDL_Rect a);

	inline static CollisionHandler* get()
	{
		if (s_instance == nullptr)
		{
			s_instance = new CollisionHandler();
		}
		return s_instance;
	}
private:
	CollisionHandler();
	TileMap m_CollisionTilemap;
	TileLayer* m_CollisionLayer;
	static CollisionHandler* s_instance;
};