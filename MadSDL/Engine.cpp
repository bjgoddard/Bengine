#include "Engine.h"
#include <iostream>
#include "Input.h"
#include "Vec2.h"
#include "Warrior.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"
#include "Enemy.h"

Engine* Engine::s_instance = nullptr;
TextureManager* TextureManager::s_Instance = nullptr;
//SDL_Renderer* renderer = nullptr;
//Warrior* player;

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
    //MAD MAP WORKING
    m_LevelMap = MapParser::get()->GetMap("level1");

    TextureManager::get().ParseTextures("assets/textures.tml");
    //TextureManager::GetInstance()->Load("foo", "assets/foo.png");
    //TextureManager::GetInstance()->Load("player", "assets/Idle 1.png");
    ////TextureManager::GetInstance()->Load("player_run", "assets/walk 1.png");
    //TextureManager::get().Load("player_idle", "assets/Idle.png");
    //TextureManager::get().Load("player_run", "assets/Run.png");
    //TextureManager::get().Load("player_jump", "assets/Jump.png");
    //TextureManager::get().Load("player_fall", "assets/Fall.png");
    //TextureManager::get().Load("player_crouch", "assets/Crouch.png");
    //TextureManager::get().Load("player_attack", "assets/Attack.png");

    //TextureManager::get().Load("bg", "assets/forestbg.jpg");
   

    Warrior* player = new Warrior(new Properties("player", 100, 200, 136, 96));
    Enemy* boss = new Enemy(new Properties("boss_idle", 820, 240, 460, 352));

    m_GameObjects.push_back(player);
    m_GameObjects.push_back(boss);

    Camera::get().SetTarget(player->GetOrigin());

    return m_IsRunning = true;
}


void Engine::Update()
{
    float dt = Timer::get()->GetDeltaTime();
    /*player->Update(dt);*/
    for (unsigned int i = 0; i != m_GameObjects.size(); i++) {
        m_GameObjects[i]->Update(dt);
    }
    m_LevelMap->Update();
    Camera::get().Update(dt);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //TextureManager::get().Draw("bg", 0, 0, 1380, 1020, 0.4f);
    m_LevelMap->Render();
    //TextureManager::GetInstance()->Draw("foo", 0, 0, 64, 128);
 /*   TextureManager::GetInstance()->Draw("player", 0, 0, 64, 128);*/
    //player->Draw();
    for (unsigned int i = 0; i != m_GameObjects.size(); i++) {
        m_GameObjects[i]->Draw();
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