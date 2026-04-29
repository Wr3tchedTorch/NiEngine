#include <NiEngine/Level.h>

#include <filesystem>
#include <string>
#include <vector>
#include <format>
#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <NiEngine/TilesetBlueprint.h>
#include <NiEngine/TilesetReference.h>
#include <NiEngine/FileUtility.h>
#include <NiEngine/DataHandler.h>
#include <NiEngine/LevelBlueprint.h>
#include <NiEngine/TileBlueprint.h>
#include <NiEngine/LayerBlueprint.h>

ni::Level::Level(int num_of_levels)
{
}

void ni::Level::ReloadLevel()
{
	LoadLevel(current_level_);
}

void ni::Level::LoadNextLevel()
{
	current_level_++;

	LoadLevel(current_level_);
}

const ni::LayerBlueprint* ni::Level::GetLayerByName(const std::string& layer_name) const
{
	for (auto& layer : current_level_blueprint_.layers_)
	{
		if (layer.name_ == layer_name)
		{
			return &layer;
		}
	}
	return nullptr;
}

ni::TileBlueprint ni::Level::GetTileAt(sf::Vector2i tile_grid_position) const
{
	TileBlueprint tile;
	for (auto& layer : current_level_blueprint_.layers_)
	{
		if (layer.type_ == kObjectsLayerType || layer.name_ == kPrototypeLayerName)
		{
			continue;
		}
		tile = tilemap_.GetTileInfo(tile_grid_position, layer, tileset_blueprints_);

		if (tile.id_ != 0)
		{
			return tile;
		}
	}
#ifdef _DEBUG
	std::cout << std::format("Tile not found at: {}, {}", tile_grid_position.x, tile_grid_position.y);
#endif // _DEBUG
	return tile;
}

void ni::Level::LoadLevel(int index)
{
	DataHandler<LevelBlueprint> handler(std::format("{}/level{}.json", kDefaultLevelsDirectory, index));

	current_level_blueprint_ = handler.GetBlueprint();

	LoadTilesetBlueprints(current_level_blueprint_.tileset_references_);

	for (int i = 0; i < current_level_blueprint_.layers_.size(); ++i)
	{
		LayerBlueprint& layer_blueprint = current_level_blueprint_.layers_[i];
		if (layer_blueprint.name_ == kPrototypeLayerName || layer_blueprint.type_ == kObjectsLayerType)
		{
			continue;
		}
		tilemap_.LoadTiles(layer_blueprint, tileset_blueprints_);
	}
}

void ni::Level::LoadTilesetBlueprints(const std::vector<TilesetReference>&tileset_references)
{
	for (auto& tileset_reference : tileset_references)
	{
		std::string tileset_filepath = std::filesystem::path(tileset_reference.file_source_).replace_extension(".json").string();
		tileset_filepath = FileUtility::RemoveRelativePaths(tileset_filepath);

		DataHandler<TilesetBlueprint> tileset_handler(tileset_filepath);
		TilesetBlueprint tileset_blueprint = tileset_handler.GetBlueprint();

		tileset_blueprint.texture_key_ = FileUtility::RemoveRelativePaths(tileset_blueprint.texture_key_);
		tileset_blueprint.first_gid_ = tileset_reference.first_gid_;

		tileset_blueprints_.emplace_back(tileset_blueprint);
	}
}
