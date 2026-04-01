#include "PhysicsComponent.h"

#include <box2d.h>
#include <math_functions.h>

#include "TransformComponent.h"

void ni::PhysicsComponent::PhysicsUpdate(TransformComponent& transform_component)
{
	b2Vec2 position = b2Body_GetPosition(body_);
	float  radians  = b2Rot_GetAngle(b2Body_GetRotation(body_));

	transform_component.SetPositionInMeters(position);
	transform_component.SetRotation(radians);
}
