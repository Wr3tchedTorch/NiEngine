#include "CharacterPhysicsComponent.h"

#include <id.h>

#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <NiEngine/TransformComponent.h>
#include <NiEngine/Tilemap.h>
#include <SFML/Graphics/Rect.hpp>

CharacterPhysicsComponent::CharacterPhysicsComponent(sf::Vector2i character_size) : size_(character_size)
{
}

void CharacterPhysicsComponent::PhysicsUpdate(ni::TransformComponent& transform_component, b2WorldId world_id, const ni::Tilemap* current_tilemap)
{
	if (!current_tilemap)
	{
		std::cout << "ERROR! Tilemap not provided!";
		return;
	}	

	HandleCollisions(transform_component, current_tilemap);
	
	if (is_falling_)
	{
		velocity_.y += GRAVITY / 10.0f;
	}
	transform_component.GetTransformable().move(velocity_);
}

void CharacterPhysicsComponent::HandleCollisions(ni::TransformComponent& transform_component, const ni::Tilemap* current_tilemap)
{
	sf::Vector2f character_position = transform_component.GetTransformable().getPosition();

	sf::FloatRect collision_area;
	collision_area.position.x = character_position.x - size_.x / 2.0f;
	collision_area.position.y = character_position.y - size_.y / 2.0f;
	collision_area.size = sf::Vector2f(size_);

	sf::FloatRect collision_block;
	collision_block.size = sf::Vector2f(size_);

	int start_x = collision_area.position.x / size_.x - 1;
	int start_y = collision_area.position.y / size_.y - 1;
	int end_x   = collision_area.position.x / size_.x + 1;
	int end_y   = collision_area.position.y / size_.y + 1;

	for (int x = start_x; x <= end_x; ++x)
	{
		for (int y = start_y; y <= end_y; ++y)
		{
			if (current_tilemap->IsTileEmpty({ x, y }))
			{
				continue;
			}

			collision_block.position.x = x * size_.x;
			collision_block.position.y = y * size_.y;

			if (is_falling_ && collision_block.findIntersection(GetFeetBounds(character_position)))
			{
				velocity_.y = 0;

				sf::Vector2f snap_position = character_position;
				snap_position.y = collision_block.position.y - size_.y / 2.0f;

				transform_component.GetTransformable().setPosition(snap_position);

				is_falling_ = false;
			}
		}
	}
}

sf::FloatRect CharacterPhysicsComponent::GetFeetBounds(sf::Vector2f position) const
{
	sf::FloatRect feet_bounds;
	feet_bounds.size.x = size_.x - 1;
	feet_bounds.size.y = size_.x / 4.0f + 1;
	
	feet_bounds.position = position;
	feet_bounds.position.x -= size_.x / 2.0f - 1;
	feet_bounds.position.y += size_.y / 4.0f;

	return feet_bounds;
}
