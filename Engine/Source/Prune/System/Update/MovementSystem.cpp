#include "MovementSystem.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/RigidBodyComponent.h"
#include "../../../Log/Log.h"

void Prune::MovementSystem::Update(entt::registry& registry, double delta)
{
    auto view = registry.view<TransformComponent, RigidBodyComponent>();

    for (auto entity : view) {
        TransformComponent& transformComponent = view.get<TransformComponent>(entity);
        RigidBodyComponent& velocityComponent = view.get<RigidBodyComponent>(entity);

        transformComponent.translation.x += static_cast<int>(velocityComponent.velocity.x * delta);
        transformComponent.translation.y += static_cast<int>(velocityComponent.velocity.y * delta);
    }
};
