#include <memory>
#include <utility>

#include <SFML/Window/WindowEnums.hpp>
#include <NiEngine/Engine.h>

#include "GameMode.h"

int main()
{
    ni::Engine engine("Cat Mario clone, by Eric", sf::State::Windowed);

    auto mode = std::make_unique<GameMode>();
    engine.GetGameModeController().Register(std::move(mode));

    engine.Run();
}