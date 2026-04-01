#include "GameMode.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "BitmapStore.h"

void ni::GameMode::Update()
{
	store_.Update();

	store_.PhysicsUpdate();
}

void ni::GameMode::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{
	store_.Render(target, states, store);
}
