#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "HUDComponent.h"
#include "BitmapStore.h"

namespace ni {

class Panel : public HUDComponent
{
public:
	Panel(sf::Vector2f gap, sf::Vector2f margin, bool vertical, int max_columns);

	void AddComponent(std::unique_ptr<HUDComponent> component);

	virtual void Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store) override;

private:
	std::vector<std::unique_ptr<HUDComponent>> hud_components_ = {};

	sf::Vector2f gap_    = {};
	sf::Vector2f margin_ = {};
	int max_columns_ = 0;
	bool vertical_ = false;
};

}