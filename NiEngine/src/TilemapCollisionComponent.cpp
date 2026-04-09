#include <NiEngine/TilemapCollisionComponent.h>

#include <box2d.h>
#include <types.h>
#include <math_functions.h>
#include <id.h>

#include <vector>

#include <SFML/System/Vector2.hpp>
#include <NiEngine/Converter.h>
#include <NiEngine/LayerBlueprint.h>

bool ni::TilemapCollisionComponent::IsTileExposed(const std::vector<int>& map, sf::Vector2i map_size, sf::Vector2i tile_grid_position)
{
	if (tile_grid_position.x < 0 || tile_grid_position.x >= map_size.x ||
		tile_grid_position.y < 0 || tile_grid_position.y >= map_size.y)
	{
		return true;
	}
	return IsTileExposed(map, tile_grid_position.x + tile_grid_position.y * map_size.x);
}

bool ni::TilemapCollisionComponent::IsTileExposed(const std::vector<int>& map, int tile_index)
{
	return tile_index < 0 || tile_index >= (int)map.size() || map[tile_index] == 0;
}

std::vector<ni::LoopInformation> ni::TilemapCollisionComponent::GetCollisionLoops(sf::Vector2i tile_size)
{
	std::vector<LoopInformation> loops;

	while (!exposed_edges_.empty())
	{
		sf::Vector2i starting_point = exposed_edges_.begin()->first;
		sf::Vector2i current_point  = starting_point;

		bool is_closed = true;
		std::vector<b2Vec2> loop;
		do
		{
			loop.push_back(Converter::PixelsToMeters(sf::Vector2i({ current_point.x * tile_size.x, current_point.y * tile_size.y })));

			auto it = exposed_edges_.find(current_point);
			if (it == exposed_edges_.end())
			{
				is_closed = false;
				break;
			}

			sf::Vector2i nextPoint = it->second;

			exposed_edges_.erase(current_point);
			current_point = nextPoint;

		} while (current_point != starting_point);

		loops.push_back({ is_closed, loop });
	}

	return loops;
}

ni::TilemapCollisionComponent::TilemapCollisionComponent(b2WorldId world_id)
{
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_staticBody;

	body_id_ = b2CreateBody(world_id, &body_def);
}

void ni::TilemapCollisionComponent::AddTile(const LayerBlueprint& layer, sf::Vector2i map_size, sf::Vector2i grid_position)
{
	int gx = grid_position.x;
	int gy = grid_position.y;

	sf::Vector2i top	= { gx,		gy - 1 };
	sf::Vector2i bottom = { gx,		gy + 1 };
	sf::Vector2i left   = { gx - 1, gy	   };
	sf::Vector2i right	= { gx + 1, gy	   };

	if (IsTileExposed(layer.data_, map_size, top))
	{
		exposed_edges_[{gx, gy}] = { gx + 1, gy };
	}
	if (IsTileExposed(layer.data_, map_size, bottom))
	{
		exposed_edges_[{gx + 1, gy + 1}] = { gx, gy + 1 };
	}
	if (IsTileExposed(layer.data_, map_size, left))
	{
		exposed_edges_[{gx, gy + 1}] = { gx, gy };
	}
	if (IsTileExposed(layer.data_, map_size, right))
	{
		exposed_edges_[{gx + 1, gy}] = { gx + 1, gy + 1 };
	}
}

void ni::TilemapCollisionComponent::CreateCollisionBody(sf::Vector2i tile_size)
{	
	std::vector<LoopInformation> loops = GetCollisionLoops(tile_size);

	for (const auto& loop : loops)
	{
		b2ChainDef shape = b2DefaultChainDef();

		shape.points = loop.data_.data();
		shape.count  = loop.data_.size();
		shape.isLoop = loop.is_closed_;

		b2CreateChain(body_id_, &shape);
	}
}
