#include "Log.h"

std::shared_ptr<spdlog::logger> Prune::Log::s_PruneLogger;

void Prune::Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_PruneLogger = spdlog::stderr_color_mt("Prune2D");
    s_PruneLogger->set_level(spdlog::level::trace);
}
