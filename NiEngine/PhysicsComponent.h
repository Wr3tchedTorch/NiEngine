#pragma once

#include "Component.h"
#include "TransformComponent.h"

namespace ni {

class PhysicsComponent : public Component
{
public:
	virtual void physicsUpdate(TransformComponent& transform_component) = 0;
};

}