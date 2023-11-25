#include "Prune/Prune.h"
#include "Log/Log.h"
#include "Game.h"

int main(int argc, char* argv[])
{
    Prune::Log::Init();

    Prune::Engine engine;
    Game game;

    engine.Up();

    game.SetRenderer(engine.GetRenderer());
    game.Run();

    engine.Down();

    return 0;
}
