#include "GameMode.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "BitmapStore.h"
#include "GameModeController.h"
#include "Engine.h"

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
}
