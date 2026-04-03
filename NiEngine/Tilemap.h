#pragma once

#include <string>

#include "TilemapBlueprint.h"

namespace ni {

class Tilemap
{
private:
	TilemapBlueprint blueprint_;

public:
	Tilemap();

	bool LoadFromFile(const std::string& filepath);
};

}