#include <NiEngine/SoundEngine.h>

#include <string>
#include <unordered_set>
#include <vector>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include <NiEngine/SoundBufferStore.h>

void ni::SoundEngine::PlaySound(std::string key)
{
	sound_queue_.push(key);
}

void ni::SoundEngine::FlushSoundQueue(SoundBufferStore& store)
{
	std::erase_if(active_sounds_, [](const sf::Sound& s) 
	{
		return s.getStatus() == sf::Sound::Status::Stopped;
	});

	std::unordered_set<std::string> played_keys;
	while (!sound_queue_.empty())
	{
		std::string key = sound_queue_.front();
		sound_queue_.pop();
		if (played_keys.contains(key))
		{
			continue;
		}
		played_keys.insert(key);

		active_sounds_.emplace_back(store.GetSoundBuffer(key));
		active_sounds_.back().play();
	}
}
