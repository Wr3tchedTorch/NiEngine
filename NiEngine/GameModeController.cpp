#include "GameModeController.h"

#include <memory>
#include <utility>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "BitmapStore.h"
#include "GameMode.h"
#include "GameModeTag.h"
#include "Id.h"

Id<GameModeTag> ni::GameModeController::Register(std::unique_ptr<GameMode> mode)
{
	game_modes_.emplace(++current_id, std::move(mode));
	return current_id;
}

void ni::GameModeController::SwitchTo(Id<GameModeTag> id)
{
	current_id = id;
}

void ni::GameModeController::Remove(Id<GameModeTag> id)
{
	game_modes_.erase(id);
}

ni::GameMode& ni::GameModeController::Get(Id<GameModeTag> id)
{
	return *game_modes_.at(id).get();
}

ni::GameMode& ni::GameModeController::GetCurrent()
{
	return *game_modes_.at(current_id).get();
}

void ni::GameModeController::Update()
{
	game_modes_.at(current_id)->Update();
}

void ni::GameModeController::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{
	game_modes_.at(current_id)->Render(target, states, store);
}
