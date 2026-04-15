#pragma once

#include <collision.h>
#include <math_functions.h>
#include <id.h>

#include <cfloat>

#include "PhysicsComponent.h"
#include "TransformComponent.h"

namespace ni {

class PlatformerCharacterPhysicsComponent : public PhysicsComponent
{
public:
    PlatformerCharacterPhysicsComponent(b2Vec2 start_position, b2Capsule shape);

    void SolveMove(float throttle);
    void Jump();

private:
    void ApplyFriction();
    void Accelerate(b2Vec2 desired_velocity);

    static bool PlaneResultFcn(b2ShapeId shapeId, const b2PlaneResult* result, void* ctx)
    {
        PlatformerCharacterPhysicsComponent* self = static_cast<PlatformerCharacterPhysicsComponent*>(ctx);
        if (self->plane_count_< kMaxPlanes)
        {
            self->planes_[self->plane_count_++] = {
                result->plane,
                /*pushLimit=*/ FLT_MAX,
                /*push=*/      0.0f,
                /*clipVel=*/   true
            };
        }
        return true;
    }

    static constexpr int kMaxPlanes = 8;

    b2WorldId        world_id_;
    b2Transform      transform_;
    b2Vec2           velocity_;
    b2Capsule        capsule_;
    b2CollisionPlane planes_[kMaxPlanes] = {};
    int              plane_count_= 0;

    bool  on_ground_     = false;
    bool  jump_released_ = true;

    float delta = 1 / 60.0f;
    float jump_speed_ = 10.0f;
    float max_speed_  = 6.0f;
    float min_speed_  = 1.0f;
    float accelerate_ = 20.0f;
    float friction_   = 8.0f;
    float gravity_    = 9.8f;
    float air_steer_  = 0.2f;

    // Inherited via PhysicsComponent
    void PhysicsUpdate(TransformComponent& transform_component) override;
};

}