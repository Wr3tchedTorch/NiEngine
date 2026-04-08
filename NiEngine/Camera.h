#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace ni {

class Camera
{
private:
	sf::View view_;

public:

	sf::View& GetView()
	{
		return view_;
	}

	void SetPosition(sf::Vector2f position);
	void ApplyTo(sf::RenderTarget& target);	
};

}