#pragma once

#include <vector>

#include "TilesetBlueprint.h"

namespace ni {

struct TiledUtility
{
	static inline const ni::TilesetBlueprint& GetTilesetByGid(const std::vector<TilesetBlueprint>& tileset_blueprints, int gid)
	{
		const TilesetBlueprint* result = nullptr;
		for (auto& tileset : tileset_blueprints)
		{
			if (gid >= tileset.first_gid_)
			{
				result = &tileset;
			}
		}
		assert(result != nullptr);
		return *result;
	}
};

}