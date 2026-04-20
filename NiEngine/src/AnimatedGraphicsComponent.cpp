#include <NiEngine/AnimatedGraphicsComponent.h>

#include <string>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <NiEngine/StandardGraphicsComponent.h>
#include <NiEngine/BitmapStore.h>
#include <NiEngine/Engine.h>

ni::AnimatedGraphicsComponent::AnimatedGraphicsComponent(std::string texture_key, sf::Vector2i sprite_size, int frame_spacing) :
	ni::StandardGraphicsComponent(texture_key, { {0, 0}, sprite_size })
{
	frame_spacing_ = frame_spacing;

	initial_frame_rect_ = current_frame_rect_;
}

void ni::AnimatedGraphicsComponent::PlayAnimation(int animation_row, float delay_in_seconds, bool loop, int frame_count, int initial_animation_frame)
{
	if (playing_)
	{
		return;
	}
	playing_ = true;

	current_animation_ = animation_row;
	current_frame_	   = 0;
	delay_in_seconds_  = delay_in_seconds;
	loop_        = loop;
	frame_count_ = frame_count;
	initial_animation_frame_ = initial_animation_frame;

	NextFrame();
}

void ni::AnimatedGraphicsComponent::SetFrame(int row, int index)
{
	current_animation_ = row;
	current_frame_	   = index;
	playing_ = false;

	NextFrame();
}

bool ni::AnimatedGraphicsComponent::IsPlaying() const
{
	return playing_;
}

void ni::AnimatedGraphicsComponent::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{
	float time_elapsed_since_last_frame = (ni::Engine::time_elapsed - time_since_last_animation_frame_).asSeconds();

	if (playing_ && time_elapsed_since_last_frame >= delay_in_seconds_)
	{
		NextFrame();
	}	
	ni::StandardGraphicsComponent::Render(target, states, store);
}

void ni::AnimatedGraphicsComponent::NextFrame()
{
	current_frame_++;
	if (current_frame_ <= frame_count_)
	{
		current_frame_rect_ = initial_frame_rect_;
		current_frame_rect_.position.x = (current_frame_rect_.size.x + frame_spacing_) * current_frame_;
		current_frame_rect_.position.y = (current_frame_rect_.size.y + frame_spacing_) * current_animation_;
		
		time_since_last_animation_frame_ = ni::Engine::time_elapsed;
		return;
	}
	if (loop_)
	{
		current_frame_ = initial_animation_frame_ - 1;
		return;
	}
	playing_ = false;
}
