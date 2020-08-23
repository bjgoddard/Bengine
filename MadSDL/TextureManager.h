#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class TextureManager
{
public:
	
	static TextureManager& get()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new TextureManager();
		}
		return *s_Instance;
	}
	bool Load(std::string id, std::string filename);
	bool ParseTextures(std::string source);
	void Drop(std::string id);
	void Clean();
	void Draw(std::string id, int x, int y, int width, int height, float scaleX=1.0f, float scaleY=1.0f, float scrollRatio = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip);

	static TextureManager* s_Instance;
	

private:
	TextureManager() {};
	std::map<std::string, SDL_Texture*> m_TextureMap;
	
};