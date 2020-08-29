#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"
#include "tinyxml.h"
bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::get().getRenderer(), surface);
    if (texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }
    m_TextureMap[id] = texture;
    return true;
}

bool TextureManager::ParseTextures(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()) {
        std::cout << "Failed to load: " << source << std::endl;
        return false;
    }
    else {
        TiXmlElement* root = xml.RootElement();
        for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
            if (e->Value() == std::string("texture")) {
                std::string id = e->Attribute("id");
                std::string src = e->Attribute("source");
                Load(id, src);
            }
        }
        return true;
    }
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float scaleX, float scaleY, float scrollRatio, SDL_RendererFlip flip)
{
    Vec2 cam = Camera::get().GetPosition() * scrollRatio;
    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect destRect = { x - cam.X, y - cam.Y, width * scaleX, height * scaleY };
    SDL_RenderCopyEx(Engine::get().getRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    Vec2 cam = Camera::get().GetPosition();
    SDL_Rect srcRect = { width * frame, height * row, width, height };
    SDL_Rect destRect = {  x - cam.X, y - cam.Y, width , height };
    SDL_RenderCopyEx(Engine::get().getRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    Vec2 cam = Camera::get().GetPosition();
    SDL_Rect destRect = { x - cam.X, y - cam.Y, tileSize, tileSize};
    SDL_Rect srcRect = { tileSize*frame, tileSize*row, tileSize, tileSize };
    SDL_RenderCopyEx(Engine::get().getRenderer(), m_TextureMap[tilesetID], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
}


