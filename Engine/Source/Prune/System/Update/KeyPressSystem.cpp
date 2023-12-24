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
        RigidBodyComponent& rigidBodyComponent = view.get<RigidBodyComponent>(entity);

        switch (event.symbol)
        {
            case SDLK_UP:
                PRUNE_LOG_INFO("Set the up velocity");
                rigidBodyComponent.velocity = keyPressComponent.upVelocity;
                break;
            case SDLK_RIGHT:
                PRUNE_LOG_INFO("Set the right velocity");
                if (event.held) {
                    rigidBodyComponent.velocity = keyPressComponent.rightVelocity;
                } else {
                    rigidBodyComponent.velocity = glm::vec2(0, 0);
                }
                break;
            case SDLK_DOWN:
                PRUNE_LOG_INFO("Set the down velocity");
                rigidBodyComponent.velocity = keyPressComponent.downVelocity;
                break;
            case SDLK_LEFT:
                PRUNE_LOG_INFO("Set the left velocity");
                if (event.held) {
                    rigidBodyComponent.velocity = keyPressComponent.leftVelocity;
                }
                else {
                    rigidBodyComponent.velocity = glm::vec2(0, 0);
                }
                break;
        }
    }
}
