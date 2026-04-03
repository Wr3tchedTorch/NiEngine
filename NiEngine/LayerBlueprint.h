#pragma once

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct LayerBlueprint
{
	std::string name_ = "";
	sf::Vector2f position_ = {};

	std::vector<int> data_ = {};
	bool visible_ = false;
};

inline void to_json(json& j, const LayerBlueprint& tb)
{
}

inline void from_json(const json& j, LayerBlueprint& tb)
{
}