#include "MovementSystem.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/RigidBodyComponent.h"
#include "../../Component/SpriteComponent.h"
#include "../../../Log/Log.h"

void Prune::MovementSystem::Update(entt::registry& registry, double delta)
{
    auto view = registry.view<TransformComponent, RigidBodyComponent, SpriteComponent>();

    for (auto entity : view) {
        TransformComponent& transformComponent = view.get<TransformComponent>(entity);
        RigidBodyComponent& velocityComponent = view.get<RigidBodyComponent>(entity);
        SpriteComponent& spriteComponent = view.get<SpriteComponent>(entity);

        transformComponent.translation.x += static_cast<int>(velocityComponent.velocity.x * delta);
        if (velocityComponent.velocity.x < 0)
        {
            spriteComponent.flipHorizontal = true;
        }
        else {
            spriteComponent.flipHorizontal = false;
        }

        transformComponent.translation.y += static_cast<int>(velocityComponent.velocity.y * delta);
    }
};
