#pragma once

#include <string>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <NiEngine/BitmapStore.h>
#include <NiEngine/GraphicsComponent.h>

namespace ni {

class StandardGraphicsComponent : public GraphicsComponent
{
protected:
	std::string texture_key_;
	sf::IntRect current_frame_rect_;

	bool flip_h_  = false;
	bool centered = false;

public:
	StandardGraphicsComponent(std::string texture_key, sf::IntRect frame_rect = {});

	void FlipH(bool new_value);
	void CenterOrigin(bool center);
	
	sf::Vector2i GetSpriteSize() const;

	virtual void Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store) override;	
};

}