#include "MovingObstacleUpdateComponent.h"

#include "ObstacleUpdateComponent.h"

#include <SFML/System/Vector2.hpp>
#include <NiEngine/ComponentLocator.h>
#include <NiEngine/GameObjectTag.h>
#include <NiEngine/Id.h>

MovingObstacleUpdateComponent::MovingObstacleUpdateComponent(
	ni::ComponentLocator& component_locator, 
	ni::Id<ni::GameObjectTag> id, 
	ni::Id<ni::GameObjectTag> player_id, 
	sf::Vector2i position_offset, 
	float speed
) : ObstacleUpdateComponent(component_locator, id, player_id)
{
	position_offset_ = position_offset;
	speed_ = speed;
}

void MovingObstacleUpdateComponent::Update()
{
	// MOVEMENT IMPLEMENTATION
	
	ObstacleUpdateComponent::Update();
}
