#include <NiEngine/Container.h>

#include <memory>
#include <utility>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <NiEngine/BitmapStore.h>
#include <NiEngine/HUDComponent.h>

ni::Container::Container(sf::Vector2f gap, sf::Vector2f margin, bool vertical, int max_columns)
{
	gap_         = gap;
	margin_      = margin;
	vertical_    = vertical;
	max_columns_ = max_columns;
}

void ni::Container::AddComponent(std::unique_ptr<HUDComponent> component)
{
	hud_components_.push_back(std::move(component));
}

void ni::Container::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{
	sf::Vector2f previous_sizes_count = {};
	for (int i = 0; i < hud_components_.size(); ++i)
	{
		auto& component = hud_components_.at(i);

		int grid_x = i % max_columns_;
		int grid_y = i / max_columns_;

		previous_sizes_count += component->GetBounds().size;

		sf::Vector2f position = GetBounds().position;

		position.x += previous_sizes_count.x + grid_x * gap_.x + margin_.x;
		position.y += previous_sizes_count.y + grid_y * gap_.y + margin_.y;

		component->GetBounds().position = position;

		component->Render(target, states, store);
	}
}