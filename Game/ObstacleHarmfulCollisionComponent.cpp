#include "ObstacleHarmfulCollisionComponent.h"

#include <SFML/Graphics/Rect.hpp>
#include <NiEngine/ComponentLocator.h>
#include <NiEngine/GameObjectTag.h>
#include <NiEngine/Id.h>
#include <NiEngine/TransformComponent.h>

void ObstacleHarmfulCollisionComponent::SolveTopCollision(sf::FloatRect collision_box, ni::ComponentLocator& locator, ni::Id<ni::GameObjectTag> id)
{
	KillCharacter(locator, id);
}

void ObstacleHarmfulCollisionComponent::SolveBottomCollision(sf::FloatRect collision_box, ni::ComponentLocator& locator, ni::Id<ni::GameObjectTag> id)
{
	KillCharacter(locator, id);
}

void ObstacleHarmfulCollisionComponent::SolveFrontCollision(sf::FloatRect collision_box, ni::ComponentLocator& locator, ni::Id<ni::GameObjectTag> id)
{
	KillCharacter(locator, id);
}

void ObstacleHarmfulCollisionComponent::KillCharacter(ni::ComponentLocator& locator, ni::Id<ni::GameObjectTag> id)
{
	ni::TransformComponent* transform = locator.GetTransformComponent(id);

	transform->GetTransformable().setPosition({ 100, 100 });
}
