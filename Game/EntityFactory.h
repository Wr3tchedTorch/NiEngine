#pragma once

#include <NiEngine/GameMode.h>
#include <SFML/System/Vector2.hpp>

class EntityFactory
{
public:
	ni::Id<ni::GameObjectTag> CreatePlatformerCharacter(ni::GameMode& game_mode, sf::Vector2i character_size, int animation_row);

private:
};

