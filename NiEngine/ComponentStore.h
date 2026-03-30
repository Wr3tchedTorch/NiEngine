#pragma once

#include <unordered_map>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "GameObjectId.h"
#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "BitmapStore.h"

namespace ni {

class ComponentStore
{
private:
	std::unordered_map<GameObjectId, PhysicsComponent>  physics_component_;
	std::unordered_map<GameObjectId, InputComponent>	input_component_;
	std::unordered_map<GameObjectId, GraphicsComponent> graphics_component_;

public:

	void addPhysicsComponent(GameObjectId target, PhysicsComponent component)
	{
		physics_component_[target] = component;
	}

	void addInputComponent(GameObjectId target, InputComponent component)
	{
		input_component_[target] = component;
	}

	void addGraphicsComponent(GameObjectId target, GraphicsComponent component)
	{
		graphics_component_[target] = component;
	}

	void addPhysicsComponent(GameObjectId target)
	{
		physics_component_.erase(target);
	}

	void addInputComponent(GameObjectId target)
	{
		input_component_.erase(target);
	}

	void addGraphicsComponent(GameObjectId target)
	{
		graphics_component_.erase(target);
	}
	 
	void render(sf::RenderTarget& target, sf::RenderStates& states, BitmapStore& store);
};

}