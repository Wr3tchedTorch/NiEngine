#pragma once

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowEnums.hpp>

#include "GameMode.h"
#include "BitmapStore.h"

namespace ni {

class Engine
{

private:
	sf::RenderWindow window_;

	GameMode current_game_mode_;
	BitmapStore store_;

public:
	Engine(std::string window_name, sf::State start_state);

	void registerGameMode(GameMode& mode);

	void Run();
};

}