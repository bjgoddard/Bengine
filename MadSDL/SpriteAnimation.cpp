#include "SpriteAnimation.h"
#include "TextureManager.h"
SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat)
{
	
}

void SpriteAnimation::Update(float dt)
{
	m_CurrentFrame = (SDL_GetTicks() / m_Speed) % m_FrameCount;
}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip)
{
	TextureManager::get().DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_CurrentFrame, flip);
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed)
{
	m_Speed = speed;
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
}
