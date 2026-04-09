#pragma once

#include <random>

#include <math_functions.h>
#include <NiEngine/GameMode.h>

class BallFactory
{
private:
	std::mt19937 rng_;

public:
	BallFactory();
	void SpawnRandomizedBall(ni::GameMode& mode, b2Vec2 starting_position, b2Vec2 starting_velocity);
};

