#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ni {

struct TileBlueprint
{
	int id_ = 0;

	bool full_collision_	  = false;
	bool one_sided_collision_ = false;
};

inline void to_json(json& j, const TileBlueprint& tb)
{
	j =
	{
		{"id", tb.id_}
	};

	j["properties"] += 
	{ 
		{"name", "oneSidedCollision"},
		{"value"}, tb.one_sided_collision_
	};

	j["properties"] +=
	{
		{"name", "fullCollision"},
		{ "value" }, tb.full_collision_
	};
}

inline void from_json(const json& j, TileBlueprint& tb)
{
	j.at("id").get_to(tb.id_);

	if (!j.contains("properties"))
	{
		return;
	}

	for (auto& property : j.at("properties"))
	{
		if (property.at("name") == "oneSidedCollision")
		{
			property.at("value").get_to(tb.one_sided_collision_);
		}
		else if (property.at("name") == "fullCollision")
		{
			property.at("value").get_to(tb.full_collision_);
		}
	}
}

}