#pragma once

#include "ObstacleUpdateComponent.h"

#include <SFML/System/Vector2.hpp>
#include <NiEngine/ComponentLocator.h>
#include <NiEngine/GameObjectTag.h>
#include <NiEngine/Id.h>

class MovingObstacleUpdateComponent : public ObstacleUpdateComponent
{
public:
	MovingObstacleUpdateComponent(ni::ComponentLocator& component_locator, ni::Id<ni::GameObjectTag> id, ni::Id<ni::GameObjectTag> player_id, sf::Vector2i position_offset, float speed);
	void Update() override;

private:
	sf::Vector2i position_offset_;
	float speed_;
};

