#pragma once
#include <string>
#include "SDL.h"
#include "Animation.h"

class SpriteAnimation : public Animation {
public:
	SpriteAnimation(bool repeat = true);

	virtual void Update(float dt);
	void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

private:
	int m_Speed;
	int m_SpriteRow;
	int m_FrameCount;
	std::string m_TextureID;

};