#include "CharacterPhysicsComponent.h"

#include <id.h>

#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <NiEngine/TransformComponent.h>
#include <NiEngine/Tilemap.h>
#include <SFML/Graphics/Rect.hpp>

CharacterPhysicsComponent::CharacterPhysicsComponent(sf::Vector2i character_size) : size_(character_size)
{
	bottom_rect_.size = sf::Vector2f(character_size);

	bottom_rect_.size.x = character_size.x - 1;
	bottom_rect_.size.y = character_size.x / 4.0f + 1;
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
	bottom_rect_.position = transform_component.GetTransformable().getPosition();
	bottom_rect_.position.x -= size_.x / 2.0f - 1;
	bottom_rect_.position.y += size_.y / 4.0f;

	sf::FloatRect collision_area;
	collision_area.position.x = transform_component.GetTransformable().getPosition().x - size_.x / 2.0f;
	collision_area.position.y = transform_component.GetTransformable().getPosition().y - size_.y / 2.0f;
	collision_area.size = sf::Vector2f(size_);

	sf::FloatRect collision_block;
	collision_block.size = sf::Vector2f(size_);

	int start_x = collision_area.position.x / size_.x - 1;
	int start_y = collision_area.position.y / size_.y - 1;
	int end_x = collision_area.position.x / size_.x + 1;
	int end_y = collision_area.position.y / size_.y + 1;

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

			if (is_falling_ && collision_block.findIntersection(bottom_rect_))
			{
				velocity_.y = 0;

				sf::Vector2f snap_position = transform_component.GetTransformable().getPosition();
				snap_position.y = collision_block.position.y - size_.y / 2.0f;

				transform_component.GetTransformable().setPosition(snap_position);

				is_falling_ = false;
			}
		}
	}
}
