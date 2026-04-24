#pragma once

#include <string>
#include <queue>
#include <vector>

#include <SFML/Audio/Sound.hpp>

#include "SoundBufferStore.h"

namespace ni {

class SoundEngine
{

friend class Engine;

public:
	void PlaySound(std::string key);

	void FlushSoundQueue(SoundBufferStore& store);

private:
	std::queue<std::string> sound_queue_;
	std::vector<sf::Sound>  active_sounds_;
};

}