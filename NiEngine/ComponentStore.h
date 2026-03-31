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
	void addPhysicsComponent(GameObjectId target, PhysicsComponent& component)
	{
		physics_component_[target] = std::make_unique<PhysicsComponent>(component);
	}

	void addUpdateComponent(GameObjectId target, UpdateComponent& component)
	{
		update_component_[target] = std::make_unique<UpdateComponent>(component);
	}

	void addGraphicsComponent(GameObjectId target, GraphicsComponent& component)
	{
		graphics_component_[target] = std::make_unique<GraphicsComponent>(component);
	}

	void addTransformComponent(GameObjectId target, TransformComponent& component)
	{
		transform_component_[target] = std::make_unique<TransformComponent>(component);
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

	void getTransformComponent(TransformComponent* component, GameObjectId id);

	void update();
	void physicsUpdate();
	void render(sf::RenderTarget& target, sf::RenderStates& states, BitmapStore& store);
};

}