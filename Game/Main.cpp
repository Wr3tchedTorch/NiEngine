#include <utility>
#include <memory>

#include <SFML/Window/WindowEnums.hpp>
#include <Engine.h>
#include <GameMode.h>
#include <GameModeTag.h>
#include <Id.h>

int main()
{
    ni::Engine engine("Shooter by Eric", sf::State::Fullscreen);

    auto my_mode = std::make_unique<ni::GameMode>();
    my_mode->RegisterTilemap("maps/level_01/map.json");
    
    ni::Id<GameModeTag> mode_id = engine.GetGameModeController().Register(std::move(my_mode));
    engine.GetGameModeController().SwitchTo(mode_id);

    engine.Run();
}