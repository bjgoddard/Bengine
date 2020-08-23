//#include "Animation.h"
//#include "TextureManager.h"
//
//void Animation::Update()
//{
//	m_CurrentFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
//}
//
//void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
//{
//	TextureManager::get().DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_CurrentFrame, flip);
//}
//
//void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed)
//{
//	m_TextureID = textureID;
//	m_SpriteRow = spriteRow;
//	m_FrameCount = frameCount;
//	m_AnimSpeed = animSpeed;
//}
