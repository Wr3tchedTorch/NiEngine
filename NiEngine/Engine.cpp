#include "Engine.h"

#include <optional>

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>

ni::Engine::Engine()
{
	window_.create(sf::VideoMode::getDesktopMode(), "Ni Engine by Eric", sf::State::Fullscreen);
}

void ni::Engine::Run()
{
	while (window_.isOpen())
	{
		while (std::optional<sf::Event> event = window_.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window_.close();
			}
		}

		window_.clear(sf::Color::Blue);

		window_.display();
	}
}
