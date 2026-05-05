#include <NiEngine/Panel.h>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <NiEngine/BitmapStore.h>
#include <NiEngine/Container.h>

ni::Panel::Panel(sf::Color background_color, sf::FloatRect rect, sf::Vector2f gap, sf::Vector2f margin, bool vertical, int max_columns) : Container(gap, margin, vertical, max_columns)
{
	background_.setFillColor(background_color);
	
	bounds_ = rect;

	background_.setPosition(rect.position);
	background_.setSize    (rect.size);	
}

void ni::Panel::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{
	target.draw(background_, states);
	Container::Render(target, states, store);
}
