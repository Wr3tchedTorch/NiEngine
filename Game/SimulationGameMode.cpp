#include "SimulationGameMode.h"

#include <iostream>

#include <types.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Color.hpp>
#include <math_functions.h>
#include <GameMode.h>
#include <Converter.h>
#include <GameModeController.h>
#include "Ball.h"

SimulationGameMode::SimulationGameMode()
{
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = { 0.0f, 9.8f };

    GetPhysicsEngine().CreateWorld(world_def);

    RegisterTilemap("maps/level_01/map.json");    
}

void SimulationGameMode::Update(ni::GameModeController& controller)
{
    GameMode::Update(controller);

    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (is_pressed && !was_mouse_pressed_)
    {
        SpawnBall();
    }

    was_mouse_pressed_ = is_pressed;
}

void SimulationGameMode::SpawnBall()
{
    Ball ball(CreateGameObject(), b2Vec2({ 4, 4 }), GetComponentStore(), GetPhysicsEngine().GetWorldId(), sf::Color::Red, 1.0f);
}
