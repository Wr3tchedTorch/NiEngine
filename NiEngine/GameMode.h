#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>
#include <string>

#include "BitmapStore.h"
#include "ComponentStore.h"
#include "Id.h"
#include "GameObjectTag.h"
#include "Tilemap.h"

namespace ni {

class GameModeController;

class GameMode
{
private:
	ComponentStore store_;

	Id<GameObjectTag> current_game_object_id_;	

	std::vector<Tilemap> tilemaps_;

public:
	GameMode() = default;

	ComponentStore& GetComponentStore()
	{
		return store_;
	}

	Id<GameObjectTag> CreateGameObject()
	{
		return ++current_game_object_id_;
	}

	void RegisterTilemap(const std::string& filepath, bool enable_collision = true);

	virtual void Update(GameModeController& controller);
	virtual void Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store);
};

}