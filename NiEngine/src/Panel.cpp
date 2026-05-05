#include <NiEngine/Panel.h>

#include <memory>
#include <utility>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <NiEngine/BitmapStore.h>
#include <NiEngine/HUDComponent.h>

void ni::Panel::AddComponent(std::unique_ptr<HUDComponent> component)
{
	hud_components_.push_back(std::move(component));
}

void ni::Panel::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{}
