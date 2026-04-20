#include <NiEngine/StandardGraphicsComponent.h>

#include <string>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <NiEngine/BitmapStore.h>

ni::StandardGraphicsComponent::StandardGraphicsComponent(std::string texture_key, sf::IntRect frame_rect) : texture_key_(texture_key), current_frame_rect_(frame_rect)
{
}

void ni::StandardGraphicsComponent::FlipH(bool new_value)
{
	flip_h_ = new_value;
}

void ni::StandardGraphicsComponent::CenterOrigin(bool center)
{
	centered = true;
}

sf::Vector2i ni::StandardGraphicsComponent::GetSpriteSize() const
{
	return current_frame_rect_.size;
}

void ni::StandardGraphicsComponent::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{
	sf::Sprite sprite(store.GetTexture(texture_key_));

	sprite.scale({ flip_h_ ? -1.0f : 1.0f, 1.0f });

	if (centered)
	{
		sprite.setOrigin(
		{
			current_frame_rect_.size.x / 2.0f,
			current_frame_rect_.size.y / 2.0f
		});
	}

	bool isFrameRectValid = current_frame_rect_.size.x > 0 && current_frame_rect_.size.y > 0;
	if (isFrameRectValid)
	{
		sprite.setTextureRect(current_frame_rect_);
	}

	target.draw(sprite, states);
}
