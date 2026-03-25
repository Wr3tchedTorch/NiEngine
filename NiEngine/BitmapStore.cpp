#include "BitmapStore.h"

#include <string>
#include <iostream>
#include <format>

#include <SFML/Graphics/Texture.hpp>

sf::Texture& BitmapStore::getTexture(const std::string& key)
{
    auto result = map_.find(key);

    if (result != map_.end())
    {
        return result->second;
    }

    bool success = map_[key].loadFromFile(key);

    if (!success)
    {
#ifdef _DEBUG
        std::cout << std::format("[Engine/Bitmap]: Texture not found for key `{}`", key);
#endif // _DEBUG
    }

    return map_[key];
}
