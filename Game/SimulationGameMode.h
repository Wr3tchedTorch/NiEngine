#pragma once

#include <vector>

#include <id.h>
#include <GameMode.h>
#include <GameModeController.h>

#include "Ball.h"

class SimulationGameMode : public ni::GameMode
{
private:
	std::vector<Ball> balls_ = {};

	bool was_mouse_pressed_ = false;

public:
	SimulationGameMode();

	virtual void Update(ni::GameModeController& controller) override;

	void SpawnBall();
};

