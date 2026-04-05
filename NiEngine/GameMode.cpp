#include "GameMode.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "BitmapStore.h"
#include "GameModeController.h"
#include "Engine.h"
#include "Tilemap.h"

void ni::GameMode::RegisterTilemap(const std::string& filepath, bool enable_collision)
{
	Tilemap map;

	map.LoadFromFile(filepath, enable_collision);

	tilemaps_.push_back(map);
}

void ni::GameMode::Update(GameModeController& controller)
{	
	if (Engine::time_elapsed.asSeconds() > 2)
	{
		controller.SwitchTo({ 2 });
	}

	store_.Update();

	store_.PhysicsUpdate();
}

void ni::GameMode::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{
	store_.Render(target, states, store);

	for (auto& map : tilemaps_)
	{
		map.Render(target, states, store);
	}
}
