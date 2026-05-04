#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>

#include "BitmapStore.h"
#include "Engine.h"

namespace ni {

class ScreenTransition
{
public:
	ScreenTransition(float delay_in_seconds) { delay_in_seconds_ = delay_in_seconds;  };

	void Play() { playing_ = true ; time_since_start_ = Engine::time_elapsed; };
	void Stop() { playing_ = false; };
	
	virtual void Update() = 0;
	virtual void Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store) = 0;

protected:
	float    delay_in_seconds_ = 0;
	bool     playing_          = false;
	sf::Time time_since_start_ = {};
};

}