#pragma once

#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct TilesetReference
{
    int first_gid_ = 0;
    std::string file_source_ = "";
};

inline void to_json(json& j, const TilesetReference& tb)
{
}

inline void from_json(const json& j, TilesetReference& tb)
{
}