#pragma once

#include <id.h>

#include <NiEngine/TransformComponent.h>
#include <NiEngine/PhysicsComponent.h>
#include <NiEngine/Tilemap.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class CharacterPhysicsComponent : public ni::PhysicsComponent
{
public:
	inline static const float GRAVITY = 9.8f;

	CharacterPhysicsComponent(sf::Vector2i character_size);
	void PhysicsUpdate(ni::TransformComponent& transform_component, b2WorldId world_id, const ni::Tilemap* current_tilemap) override;
	void Move(float dir_x);

private:
	sf::Vector2f velocity_;
	sf::Vector2i size_;

	float speed_ = 16;

	bool is_falling_ = true;

	void HandleCollisions(ni::TransformComponent& transform_component, const ni::Tilemap* current_tilemap);

	sf::FloatRect GetFeetBounds(sf::Vector2f position) const;
};

