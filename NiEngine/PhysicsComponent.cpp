#include "PhysicsComponent.h"

#include <box2d.h>
#include <math_functions.h>
#include <id.h>

#include "TransformComponent.h"
#include <iostream>

ni::PhysicsComponent::PhysicsComponent(b2BodyId body) : body_(body)
{
}

void ni::PhysicsComponent::PhysicsUpdate(TransformComponent& transform_component) {
    b2Vec2 position = b2Body_GetPosition(body_);
    float  radians = b2Rot_GetAngle(b2Body_GetRotation(body_));

    //// Informative Logging
    //std::cout << "[PhysicsUpdate] Body ID: " << body_.index1
    //    << " | Pos: (" << position.x << ", " << position.y << ")"
    //    << " | Rot: " << radians << " rad" << std::endl;

    transform_component.SetPositionInMeters(position);
    transform_component.SetRotation(radians);
}
