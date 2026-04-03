#include "Tilemap.h"

#include <string>

#include "DataHandler.h"
#include "TilemapBlueprint.h"
#include "TilesetBlueprint.h"
#include "FileUtility.h"

ni::Tilemap::Tilemap(const std::string& filepath)
{
	LoadFromFile(filepath);
}

bool ni::Tilemap::LoadFromFile(const std::string& filepath)
{
	DataHandler<TilemapBlueprint> handler(filepath);

	blueprint_ = handler.GetBlueprint();

	for (auto& tileset_reference : blueprint_.tileset_references_)
	{
		std::string tileset_filepath = std::filesystem::path(tileset_reference.file_source_).replace_extension(".json").string();
		tileset_filepath = FileUtility::RemoveRelativePaths(tileset_filepath);

		DataHandler<TilesetBlueprint> tileset_handler(tileset_filepath);
		TilesetBlueprint tileset_blueprint = tileset_handler.GetBlueprint();

		tileset_blueprint.texture_key_ = FileUtility::RemoveRelativePaths(tileset_blueprint.texture_key_);
		tileset_blueprint.first_gid_   = tileset_reference.first_gid_;

		tileset_blueprints_.emplace_back(tileset_blueprint);
	}

	return true;
}
