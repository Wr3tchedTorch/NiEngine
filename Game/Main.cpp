
#include <utility>
#include <memory>

#include <SFML/Window/WindowEnums.hpp>

#include <NiEngine/Id.h>
#include <NiEngine/Engine.h>
#include <NiEngine/GameModeTag.h>
#include <NiEngine/Converter.h>

#include "SimulationGameMode.h"

int main()
{
    ni::Converter::PIXELS_PER_METERS = 16.0f;

    ni::Engine engine("Ni Engine, by Eric", sf::State::Fullscreen);

    auto mode = std::make_unique<SimulationGameMode>();

    ni::Id<GameModeTag> mode_id = engine.GetGameModeController().Register(std::move(mode));
    engine.GetGameModeController().SwitchTo(mode_id);

    engine.Run();
}