#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace ni {

struct TilemapUtility 
{
	static sf::IntRect GetTextureBounds(sf::Vector2i coordinates, int tile_size = 0, int spacing = 0)
	{
		sf::IntRect result;
		result.size = { tile_size, tile_size };
		result.position.x = coordinates.x * (tile_size + spacing);
		result.position.y = coordinates.y * (tile_size + spacing);
		return result;
	}
};

}
