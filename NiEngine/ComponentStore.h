#pragma once

#include <unordered_map>
#include <memory>
#include <utility>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "GameObjectId.h"
#include "GraphicsComponent.h"
#include "UpdateComponent.h"
#include "PhysicsComponent.h"
#include "BitmapStore.h"
#include "TransformComponent.h"

namespace ni {

class ComponentStore
{
private:
	std::unordered_map<GameObjectId, std::unique_ptr<TransformComponent>> transform_component_;
	std::unordered_map<GameObjectId, std::unique_ptr<PhysicsComponent>>   physics_component_;
	std::unordered_map<GameObjectId, std::unique_ptr<UpdateComponent>>	  update_component_;
	std::unordered_map<GameObjectId, std::unique_ptr<GraphicsComponent>>  graphics_component_;

public:

	void addPhysicsComponent(GameObjectId target, std::unique_ptr<PhysicsComponent> component)
	{
		physics_component_[target] = std::move(component);
	}

	void addUpdateComponent(GameObjectId target, std::unique_ptr<UpdateComponent> component)
	{
		update_component_[target] = std::move(component);
	}

	void addGraphicsComponent(GameObjectId target, std::unique_ptr<GraphicsComponent> component)
	{
		graphics_component_[target] = std::move(component);
	}

	void addTransformComponent(GameObjectId target, std::unique_ptr<TransformComponent> component)
	{
		transform_component_[target] = std::move(component);
	}

	void removePhysicsComponent(GameObjectId target)
	{
		physics_component_.erase(target);
	}

	void removeUpdateComponent(GameObjectId target)
	{
		update_component_.erase(target);
	}

	void removeGraphicsComponent(GameObjectId target)
	{
		graphics_component_.erase(target);
	}

	void removeTransformComponent(GameObjectId target)
	{
		transform_component_.erase(target);
	}



	TransformComponent* getTransformComponent(GameObjectId id);

	void update();
	void physicsUpdate();
	void render(sf::RenderTarget& target, sf::RenderStates& states, BitmapStore& store);
};

}