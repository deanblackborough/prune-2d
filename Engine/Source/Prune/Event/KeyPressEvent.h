#pragma once

#include <entt.hpp>
#include <SDL.h>
#include "../../Event/Event.h"

namespace Prune
{
    class KeyPressEvent : public Event
    {
    public:
        entt::registry& registry;
        SDL_Keycode symbol;
        bool held;

        KeyPressEvent(
            entt::registry& registry, 
            SDL_Keycode symbol, 
            bool held = false
        ) : registry(registry), symbol(symbol), held(held)
        {
        }

    private:

    };
}