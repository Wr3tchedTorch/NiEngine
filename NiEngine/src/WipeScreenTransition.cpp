#include <NiEngine/WipeScreenTransition.h>

#include <cmath>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <NiEngine/ScreenTransition.h>
#include <NiEngine/Engine.h>
#include <NiEngine/BitmapStore.h>


ni::WipeScreenTransition::WipeScreenTransition(float delay_in_seconds, bool vertical, sf::Color color) : ScreenTransition(delay_in_seconds),
	upper_rect_(sf::Vector2f(Engine::window_resolution)),
	lower_rect_(sf::Vector2f(Engine::window_resolution))
{
	vertical_ = vertical;
	upper_rect_.setFillColor(color);
	lower_rect_.setFillColor(color);

	upper_rect_.setPosition(-upper_rect_.getSize());
	lower_rect_.setPosition(upper_rect_.getSize());
}

void ni::WipeScreenTransition::Update()
{
	if (!playing_)
	{
		return;
	}

	float time_elapsed = (time_since_start_ - Engine::time_elapsed).asSeconds();

	sf::Vector2f upper_rect_pos = {};
	sf::Vector2f lower_rect_pos = {};
	if (vertical_)
	{
		upper_rect_pos.x = 0;
		lower_rect_pos.x = 0;

		float upper_rect_start_y_pos = -upper_rect_.getSize().y;
		float upper_rect_end_y_pos   = -upper_rect_.getSize().y / 2.0f;

		upper_rect_pos.y = std::lerp(upper_rect_start_y_pos, upper_rect_end_y_pos, time_elapsed / delay_in_seconds_);

		float lower_rect_start_y_pos = lower_rect_.getSize().y;
		float lower_rect_end_y_pos   = lower_rect_.getSize().y / 2.0f;

		lower_rect_pos.y = std::lerp(lower_rect_start_y_pos, lower_rect_end_y_pos, time_elapsed / delay_in_seconds_);
	}
	else
	{
		upper_rect_pos.y = 0;
		lower_rect_pos.y = 0;

		float upper_rect_start_x_pos = -upper_rect_.getSize().x;
		float upper_rect_end_x_pos   = -upper_rect_.getSize().x / 2.0f;

		upper_rect_pos.x = std::lerp(upper_rect_start_x_pos, upper_rect_end_x_pos, time_elapsed / delay_in_seconds_);

		float lower_rect_start_x_pos = lower_rect_.getSize().x;
		float lower_rect_end_x_pos   = lower_rect_.getSize().x / 2.0f;

		lower_rect_pos.x = std::lerp(lower_rect_start_x_pos, lower_rect_end_x_pos, time_elapsed / delay_in_seconds_);
	}
	upper_rect_.setPosition(upper_rect_pos);
	lower_rect_.setPosition(lower_rect_pos);
}

void ni::WipeScreenTransition::Render(sf::RenderTarget & target, sf::RenderStates states, BitmapStore & store)
{
	target.draw(upper_rect_, states);
	target.draw(lower_rect_, states);
}

