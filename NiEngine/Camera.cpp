#include "Camera.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

void ni::Camera::SetPosition(sf::Vector2f position)
{
	view_.setCenter({
			position.x - view_.getSize().x / 2,
			position.y - view_.getSize().y / 2
	});
}

void ni::Camera::ApplyTo(sf::RenderTarget& target)
{
	target.setView(view_);
}
