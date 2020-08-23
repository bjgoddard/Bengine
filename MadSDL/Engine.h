#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "GameMap.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Engine
{
public:
	inline static Engine& get() 
	{
		if (s_instance == nullptr) {
			s_instance = new Engine();
		}
		return *s_instance;
	}
	bool Init();
	void Clean();
	void Quit();

	void Update();
	void Render();
	void Events();

	inline GameMap* GetMap() { return m_LevelMap; }
	inline bool IsRunning() { return m_IsRunning; }
	inline SDL_Renderer* getRenderer() {
		return renderer;
	}
	
private:
	Engine() {};
	bool m_IsRunning;
	GameMap* m_LevelMap;
	SDL_Renderer* renderer;
	SDL_Window* m_Window;
	static Engine* s_instance;
};