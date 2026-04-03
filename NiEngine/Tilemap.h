#pragma once

#include <string>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "TilemapBlueprint.h"
#include "TilemapGraphicsComponent.h"

namespace ni {

class Tilemap
{
private:
	TilemapBlueprint blueprint_;

	TilemapGraphicsComponent graphics_;

public:
	Tilemap(const std::string& filepath);

	bool LoadFromFile(const std::string& filepath);
	void EnableCollisions();

	void Render(sf::RenderTarget& target, sf::RenderStates states);
};

}