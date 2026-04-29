#pragma once

#include <id.h>

#include <string>
#include <memory>
#include <vector>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "TilemapGraphicsComponent.h"
#include "LayerBlueprint.h"
#include "BitmapStore.h"
#include "TilemapCollisionComponent.h"
#include "TileBlueprint.h"
#include "TilesetBlueprint.h"

namespace ni {

class Tilemap
{
private:
	TilemapGraphicsComponent   graphics_;

	std::unique_ptr<TilemapCollisionComponent> collision_ = nullptr;

	bool has_loaded_collision = false;
	bool has_loaded_graphics  = false;

	bool is_collision_enabled = false;

	sf::Vector2i map_size_  = {};
	sf::Vector2i tile_size_ = {};

public:
	inline static const std::string kPrototypeLayerName = "prototype";
	inline static const std::string kTerrainLayerName   = "terrain";

	void Init(sf::Vector2i map_size, sf::Vector2i tile_size);
	void LoadTiles(const LayerBlueprint& layer, const std::vector<TilesetBlueprint>& tileset_blueprints);
	void EnableCollision(b2WorldId world_id);
	void Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store);

	sf::FloatRect GetBounds() const;

	sf::Vector2i GlobalToGridPosition(sf::Vector2f position) const;

	TileBlueprint GetTileInfo(sf::Vector2i tile_grid_position, const LayerBlueprint& layer, const std::vector<TilesetBlueprint>& tileset_blueprints) const;

	bool IsTileEmpty(sf::Vector2i tile_grid_position) const;
};

}