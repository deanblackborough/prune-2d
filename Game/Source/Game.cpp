#include "Game.h"
#include <Prune/Component/AnimatedSpriteComponent.h>
#include <Prune/Component/BoxColliderComponent.h>
#include <Prune/Component/KeyPressComponent.h>
#include <Prune/Component/SpriteComponent.h>
#include <Prune/Component/TransformComponent.h>
#include <Prune/Component/VelocityComponent.h>
#include <Prune/Event/KeyPressEvent.h>
#include <Prune/System/Update/AnimatedSpriteSystem.h>
#include <Prune/System/Update/CollisionSystem.h>
#include <Prune/System/Update/HealthSystem.h>
#include <Prune/System/Update/KeyPressSystem.h>
#include <Prune/System/Update/MovementSystem.h>
#include <Prune/System/Render/BoxColliderRenderSystem.h>
#include <Prune/System/Render/SpriteRenderSystem.h>

Game::Game()
{
    InitECS();

    m_SpriteLibrary = Prune::SpriteLibrary::SpriteLibrary();
    m_EventBus = std::make_unique<Prune::EventBus>();
    m_IsRunning = true;
}

void Game::Run()
{
    // This is effectively the level/menu being loaded, later
    // on, work out how we have going to handle that, for now, 
    // OK to go straight to the game as that is all we have
    {
        AddSpritesToLibrary();
        CreateEntities();
    }

    Uint32 frameEndTime = 0;

    while (m_IsRunning)
    {

        Uint32 frameStartTime = SDL_GetTicks();
        
        CaptureInputEvents();

        m_EventBus->Reset();
        
        double deltaTime = (frameStartTime - frameEndTime) / 1000.f;

        RunSystems(deltaTime);

        Render();

        frameEndTime = frameStartTime;
    }
}

void Game::Render()
{
    RenderBackground();
    RenderEntities();

    SDL_RenderPresent(m_Renderer);
}

void Game::CaptureInputEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_IsRunning = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                m_IsRunning = false;
            }
            if (event.key.keysym.sym == SDLK_d) {
                m_ShowBoxColliders2D = !m_ShowBoxColliders2D;
            }

            m_EventBus->EmitEvent<Prune::KeyPressEvent>(m_Registry, event.key.keysym.sym);
            break;
        }
    }
}

void Game::InitECS()
{
    entt::registry m_Registry;
}

void Game::SetRenderer(SDL_Renderer* renderer)
{
    m_Renderer = renderer;
}

void Game::CreateEntities()
{
    entt::entity plane_grey = m_Registry.create();
    m_Registry.emplace<Prune::TransformComponent>(plane_grey, glm::vec2(10, (300 - 16)), glm::vec2(1, 1));
    m_Registry.emplace<Prune::VelocityComponent>(plane_grey, glm::vec2(100, 0));
    m_Registry.emplace<Prune::SpriteComponent>(plane_grey, "plane-grey-right", 32, 32, 0, 0, 128, 128);
    m_Registry.emplace<Prune::BoxColliderComponent>(plane_grey, glm::vec2(32, 32));

    entt::entity plane_green = m_Registry.create();
    m_Registry.emplace<Prune::TransformComponent>(plane_green, glm::vec2((800 - 10 - 32), (300 - 16)), glm::vec2(1, 1));
    m_Registry.emplace<Prune::VelocityComponent>(plane_green, glm::vec2(-250, 0));
    m_Registry.emplace<Prune::SpriteComponent>(plane_green, "plane-green-left", 32, 32, 0, 0, 128, 128);
    m_Registry.emplace<Prune::BoxColliderComponent>(plane_green, glm::vec2(32, 32));

    entt::entity player = m_Registry.create();
    m_Registry.emplace<Prune::TransformComponent>(player, glm::vec2((400), (400)), glm::vec2(1, 1));
    m_Registry.emplace<Prune::VelocityComponent>(player, glm::vec2(75, 0));
    m_Registry.emplace<Prune::SpriteComponent>(player, "player-idle", 200, 200, 0, 0, 200, 200);
    m_Registry.emplace<Prune::AnimatedSpriteComponent>(player, 1, 4, 8);
    m_Registry.emplace<Prune::BoxColliderComponent>(player, glm::vec2(200, 200));
    m_Registry.emplace<Prune::KeyPressComponent>(player, glm::vec2(0, -75), glm::vec2(75, 0), glm::vec2(0, 75), glm::vec2(-75, 0));
}

void Game::AddSpritesToLibrary()
{
    m_SpriteLibrary.SetRenderer(m_Renderer);
    m_SpriteLibrary.AddSprite("plane-grey-right", "Assets\\Sprites\\plane-grey-right.png");
    m_SpriteLibrary.AddSprite("plane-green-left", "Assets\\Sprites\\plane-green-left.png");
    m_SpriteLibrary.AddSprite("player-idle", "Assets\\Sprites\\player-idle.png");
}

void Game::RunSystems(double delta)
{
    Prune::HealthSystem damageSystem = Prune::HealthSystem();
    damageSystem.SubscribeToEvents(m_EventBus);

    Prune::KeyPressSystem keyPressSystem = Prune::KeyPressSystem();
    keyPressSystem.SubscribeToEvents(m_EventBus);

    Prune::MovementSystem movementSystem = Prune::MovementSystem();
    movementSystem.Update(m_Registry, delta);

    Prune::AnimatedSpriteSystem animatedSpriteSystem = Prune::AnimatedSpriteSystem();
    animatedSpriteSystem.Update(m_Registry);

    Prune::CollisionSystem boxCollider2DCollisionSystem = Prune::CollisionSystem();
    boxCollider2DCollisionSystem.Update(m_Registry, m_EventBus);
}

void Game::RenderEntities()
{
    Prune::SpriteRenderSystem spriteRenderSystem = Prune::SpriteRenderSystem();
    spriteRenderSystem.Render(m_Registry, m_Renderer, m_SpriteLibrary);

    Prune::BoxColliderRenderSystem boxCollider2DRenderSystem = Prune::BoxColliderRenderSystem();
    boxCollider2DRenderSystem.Render(m_Registry, m_Renderer, m_ShowBoxColliders2D);
}

void Game::RenderBackground()
{
    SDL_SetRenderDrawColor(m_Renderer, 80, 50, 185, 255);
    SDL_RenderClear(m_Renderer);
}