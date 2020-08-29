#include "Engine.h"
#include <iostream>
#include "Input.h"
#include "Vec2.h"
#include "Warrior.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"
#include "Enemy.h"
#include "CollisionHandler.h"
#include "CollisionSystem.h"
#include "Viking.h"

Engine* Engine::s_instance = nullptr;
TextureManager* TextureManager::s_Instance = nullptr;
CollisionSystem collisionSystem;



bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags  window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if (m_Window == nullptr)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (!MapParser::get()->Load())
    {
        std::cout << "Failed to load map" << std::endl;
        return false;
    }

    m_LevelMap = MapParser::get()->GetMap("level1");

    TextureManager::get().ParseTextures("assets/textures.tml");
  

    Warrior* player = new Warrior(new Properties("player", 500, 1000, 136, 96));
    Viking* viking = new Viking(new Properties("viking", 1200, 1000, 128, 128));
    if (viking) {
        viking->player = player;
    }

    m_GameObjects.push_back(player);
    m_GameObjects.push_back(viking);

    collisionSystem.AddToCollisionList(player);
    collisionSystem.AddToCollisionList(viking);

    Camera::get().SetTarget(player->GetOrigin());

    return m_IsRunning = true;
}


void Engine::Update()
{
    float dt = Timer::get()->GetDeltaTime();
    for (auto& obj : m_GameObjects) {
        obj->Update(dt);
    }
    collisionSystem.ProcessCollisionList();
    m_LevelMap->Update();
    Camera::get().Update(dt);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //Background images
    TextureManager::get().Draw("bg5", 0, 0, 2250, 914, 1.0f, 1.0f, 0.4f);
    TextureManager::get().Draw("bg4", 0, 0, 2250, 911, 1.0f, 1.0f, 0.5f);
    TextureManager::get().Draw("bg3", 0, 0, 2250, 1128, 1.0f, 1.0f, 0.6f);
    TextureManager::get().Draw("bg2", 0, 0, 2250, 1800, 1.0f, 1.0f, 0.7f);
    TextureManager::get().Draw("bg1", 0, 900, 2250, 591, 1.0f, 0.7f, 0.4f);
    m_LevelMap->Render();

    for (auto& obj : m_GameObjects) {
        obj->Draw();
    }

    SDL_RenderPresent(renderer);
}

void Engine::Events()
{
    Input::get().Listen();
}

void Engine::Clean()
{
    for (unsigned int i = 0; i != m_GameObjects.size(); i++) {
        m_GameObjects[i]->Clean();
    }
    TextureManager::get().Clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}