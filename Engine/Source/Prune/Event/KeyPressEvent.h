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

        KeyPressEvent(entt::registry& registry, SDL_Keycode symbol) : registry(registry), symbol(symbol)
        {
        }

    private:

    };
}