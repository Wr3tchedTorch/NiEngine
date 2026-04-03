#include "Tilemap.h"

#include <string>

#include "DataHandler.h"
#include "TilemapBlueprint.h"

ni::Tilemap::Tilemap(const std::string& filepath)
{
	LoadFromFile(filepath);
}

bool ni::Tilemap::LoadFromFile(const std::string& filepath)
{
	DataHandler<TilemapBlueprint> handler(filepath);

	blueprint_ = handler.GetBlueprint();

	return true;
}
