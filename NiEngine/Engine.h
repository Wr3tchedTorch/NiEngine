#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace ni {
	class Engine
	{
	private:
		sf::RenderWindow window_;

	public:
		Engine();
		void Run();
	};
}