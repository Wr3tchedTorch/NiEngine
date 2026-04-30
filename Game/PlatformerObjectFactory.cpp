#include "PlatformerObjectFactory.h"

#include <vector>
#include <string>
#include <utility>
#include <memory>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <NiEngine/TilesetBlueprint.h>
#include <NiEngine/GameMode.h>
#include <NiEngine/ObjectTemplateBlueprint.h>
#include <NiEngine/ObjectBlueprint.h>
#include <NiEngine/TiledUtility.h>
#include <NiEngine/GameObjectTag.h>
#include <NiEngine/Id.h>
#include <NiEngine/StandardGraphicsComponent.h>
#include <NiEngine/TransformComponent.h>

#include "ObstacleHarmfulCollisionComponent.h"
#include "MovingObstacleUpdateComponent.h"

void PlatformerObjectFactory::SpawnObject(ni::ObjectBlueprint object, ni::ObjectTemplateBlueprint& object_template, const std::vector<ni::TilesetBlueprint>& tileset_blueprints, ni::GameMode& mode, int type)
{
	ni::TilesetBlueprint tileset = ni::TiledUtility::GetTilesetByGid(tileset_blueprints, object_template.tile_gid_);
	std::string  texture_key = tileset.texture_key_;
	
	int gid  = object_template.tile_gid_ - tileset.first_gid_;

	int uv_x = gid % tileset.columns_;
	int uv_y = gid / tileset.columns_;
	
	sf::IntRect texture_coords;
	texture_coords.position.x = uv_x * tileset.tile_size_.x;
	texture_coords.position.y = uv_y * tileset.tile_size_.y;
	texture_coords.size = tileset.tile_size_;

	switch (type)
	{
	case ObjectTypes::Spike:
		SpawnSpike(object, object_template, texture_key, texture_coords, mode);
		break;
	}
}

void PlatformerObjectFactory::SpawnSpike(ni::ObjectBlueprint object, ni::ObjectTemplateBlueprint& object_template, std::string texture_key, sf::IntRect texture_coordinates, ni::GameMode& mode)
{
	ni::Id<ni::GameObjectTag> id = mode.CreateGameObject();

	sf::Vector2i repeat_amount = { 1, 0 };

	auto graphics = std::make_unique<ni::StandardGraphicsComponent>(texture_key, texture_coordinates);
	graphics->SetRepeating(repeat_amount);

	ni::TransformComponent transform;
	transform.GetTransformable().setPosition(object.position_);

	auto update = std::make_unique<MovingObstacleUpdateComponent>(
		mode.GetComponentStore(), transform, id,
		sf::Vector2i({ 0, -32 }), 20,
		sf::Vector2f({ static_cast<float>((repeat_amount.x + 1) * 16), 16 }),
		0.2f
	);
	update->RegisterCollisionComponent(std::make_unique<ObstacleHarmfulCollisionComponent>());

	mode.GetComponentStore().AttachUpdateComponent   (id, std::move(update));
	mode.GetComponentStore().AttachGraphicsComponent (id, std::move(graphics));
	mode.GetComponentStore().AttachTransformComponent(id, transform);
}
