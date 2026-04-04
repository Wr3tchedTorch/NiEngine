#include "TilemapGraphicsComponent.h"

#include <vector>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "TilemapBlueprint.h"
#include "LayerBlueprint.h"
#include "TilesetBlueprint.h"

void ni::TilemapGraphicsComponent::UpdateVertices(int index, TilemapBlueprint& blueprint, std::vector<TilesetBlueprint>& tileset_blueprints)
{
	LayerBlueprint & layer_blueprint = blueprint.layers_.at(index);	
	sf::VertexArray& layer_vertices  = layers_vertices_.at(index);

	layers_vertices_.resize(blueprint.map_size_.x * blueprint.map_size_.y * kVerticesPerTile);
	for (int y = 0; y < blueprint.map_size_.y; ++y)
	{
		for (int x = 0; x < blueprint.map_size_.x; ++x)
		{
			int index = x + y * blueprint.map_size_.x;

			int tile_id = layer_blueprint.data_.at(index);

			float top  = y * blueprint.tile_size_.y;
			float left = x * blueprint.tile_size_.x;
			float bottom = top  + blueprint.tile_size_.y;
			float right  = left + blueprint.tile_size_.x;
		}
	}
}

void ni::TilemapGraphicsComponent::LoadBlueprint(TilemapBlueprint& blueprint, std::vector<TilesetBlueprint>& tileset_blueprints)
{
	layers_vertices_.clear();

	layers_vertices_.resize(blueprint.layers_.size());
	for (int i = 0; i < blueprint.layers_.size(); ++i)
	{
		LayerBlueprint& layer = blueprint.layers_[i];
		if (layer.name_ == kPrototypeLayerName)
		{
			continue;
		}
		UpdateVertices(i, blueprint, tileset_blueprints);
	}
}

void ni::TilemapGraphicsComponent::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{
}
