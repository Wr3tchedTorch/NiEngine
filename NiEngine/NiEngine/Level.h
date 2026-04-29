#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

#include "TilesetBlueprint.h"
#include "Tilemap.h"
#include "ObjectMap.h"
#include "LevelBlueprint.h"
#include "LayerBlueprint.h"
#include "TileBlueprint.h"
#include "TilesetReference.h"

namespace ni {

class Level
{
public:
	Level(int num_of_levels);

	void ReloadLevel();
	void LoadNextLevel();

	const LayerBlueprint* GetLayerByName(const std::string& layer_name) const;

	TileBlueprint GetTileAt(sf::Vector2i tile_grid_position) const;

private:
	inline static const std::string kDefaultLevelsDirectory      = "maps";
	inline static const std::string kTransparentTilesTilesetName = "transparent_tiles";
	
	inline static const std::string kPrototypeLayerName = "prototype";
	inline static const std::string kTerrainLayerName   = "terrain";
	inline static const std::string kObjectsLayerType   = "objectgroup";

	int current_level_ = 0;
	int num_of_levels_ = 0;

	LevelBlueprint current_level_blueprint_;
	std::vector<TilesetBlueprint> tileset_blueprints_ = {};

	std::string last_loaded_file_ = "";

	Tilemap   tilemap_;
	ObjectMap object_map_;

	void LoadLevel(int index);
	void LoadTilesetBlueprints(const std::vector<TilesetReference>& tileset_references);
};

}