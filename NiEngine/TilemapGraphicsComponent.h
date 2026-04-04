#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "TilemapBlueprint.h"
#include "TilesetBlueprint.h"
#include "BitmapStore.h"

namespace ni {

class TilemapGraphicsComponent
{

private:
	inline static const std::string kPrototypeLayerName = "prototype";
	inline static const float kVerticesPerTile = 6;

	std::vector<sf::VertexArray> layers_vertices_;

	void UpdateVertices(int layer_index, TilemapBlueprint& blueprint, std::vector<TilesetBlueprint>& tileset_blueprints);

public:
	void LoadBlueprint(TilemapBlueprint& blueprint, std::vector<TilesetBlueprint>& tileset_blueprints);
	void Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store);
};

}