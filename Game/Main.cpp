

#include <SFML/Window/WindowEnums.hpp>
#include <Engine.h>
#include <Tilemap.h>

int main()
{
    ni::Engine engine("Shooter by Eric", sf::State::Fullscreen);

    ni::Tilemap my_map("./maps/level_01/map.json");
}