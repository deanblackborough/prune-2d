#include "KeyPressSystem.h"
#include "../../Component/KeyPressComponent.h"
#include "../../Component/RigidBodyComponent.h"
#include "../../../Log/Log.h"

void Prune::KeyPressSystem::SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
{
    eventBus->SubscribeToEvent<KeyPressEvent>(this, &KeyPressSystem::OnKeyPress);
}

void Prune::KeyPressSystem::OnKeyPress(KeyPressEvent& event)
{
    auto view = event.registry.view<KeyPressComponent, RigidBodyComponent>();

    for (auto entity : view) {
        const KeyPressComponent& keyPressComponent = view.get<KeyPressComponent>(entity);
        RigidBodyComponent& velocityComponent = view.get<RigidBodyComponent>(entity);

        switch (event.symbol)
        {
            case SDLK_UP:
                PRUNE_LOG_INFO("Set the up velocity");
                velocityComponent.velocity = keyPressComponent.upVelocity;
                break;
            case SDLK_RIGHT:
                PRUNE_LOG_INFO("Set the right velocity");
                velocityComponent.velocity = keyPressComponent.rightVelocity;
                break;
            case SDLK_DOWN:
                PRUNE_LOG_INFO("Set the down velocity");
                velocityComponent.velocity = keyPressComponent.downVelocity;
                break;
            case SDLK_LEFT:
                PRUNE_LOG_INFO("Set the left velocity");
                velocityComponent.velocity = keyPressComponent.leftVelocity;
                break;
        }
    }
}
