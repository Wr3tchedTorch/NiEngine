#pragma once

#include <vector>
#include <unordered_map>
#include <utility>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <NiEngine/BitmapStore.h>
#include <NiEngine/GameMode.h>
#include <NiEngine/GameModeController.h>
#include <NiEngine/Camera.h>

#include "Ball.h"
#include "BallFactory.h"

class SimulationGameMode : public ni::GameMode
{
private:
	BallFactory ball_factory_;
	ni::Camera  main_camera_;

	std::vector<Ball> balls_ = {};

	bool was_mouse_pressed_ = false;

	std::unordered_map<sf::Mouse::Button, bool> mouse_pressed_history_;

	sf::Vector2f current_mouse_position_;

public:
	SimulationGameMode();

	bool IsMouseButtonJustPressed(sf::Mouse::Button button);	

	virtual void Update(ni::GameModeController& controller) override;
	virtual void Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store) override;

	void SpawnPlayer();
	std::pair<sf::CircleShape, sf::CircleShape> GetPlayerShape(float radius);
};

