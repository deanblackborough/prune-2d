#pragma once

#include <entt.hpp>
#include "../../../Event/EventBus.h"
#include "../../Event/KeyPressEvent.h"

namespace Prune
{
    class KeyPressSystem
    {
    public:
        KeyPressSystem() = default;
        ~KeyPressSystem() = default;

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus);

        void OnKeyPress(KeyPressEvent& event);

    private:
    };
}
