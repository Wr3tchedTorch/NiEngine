

#include <SFML/Window/WindowEnums.hpp>
#include <Engine.h>
#include <GameMode.h>
#include <utility>
#include <memory>

int main()
{
    ni::Engine engine("Shooter by Eric", sf::State::Fullscreen);

    auto my_mode = std::make_unique<ni::GameMode>();
    my_mode->RegisterTilemap("maps/level_01/map.json");
    engine.GetGameModeController().Register(std::move(my_mode));

    engine.Run();
}