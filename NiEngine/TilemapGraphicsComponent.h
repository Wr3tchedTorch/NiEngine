#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "TilemapBlueprint.h"

namespace ni {

class TilemapGraphicsComponent
{
private:
	sf::VertexArray vertices_;

public:
	void Render(sf::RenderTarget& target, sf::RenderStates states, TilemapBlueprint& blueprint);
};

}