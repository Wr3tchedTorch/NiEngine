#include <NiEngine/PlatformerCharacterPhysicsComponent.h>

#include <collision.h>
#include <math_functions.h>

#include <iostream>
#include <format>

#include <NiEngine/TransformComponent.h>

ni::PlatformerCharacterPhysicsComponent::PlatformerCharacterPhysicsComponent(b2Vec2 start_position, b2Capsule shape)
{
    transform_ = { start_position, b2Rot_identity };
    velocity_  = { 0.0f, 0.0f };

    capsule_ = shape;
}

void ni::PlatformerCharacterPhysicsComponent::SolveMove(float throttle)
{    
    if (throttle == 0.0f)
    {
        ApplyFriction();
        return;
    }    
    b2Vec2 desired_velocity = { max_speed_ * throttle, 0.0f };
    Accelerate(desired_velocity);
}

void ni::PlatformerCharacterPhysicsComponent::Jump()
{
    if (on_ground_)
    {
        velocity_.y = jump_speed_;
        on_ground_= false;
    }
}

void ni::PlatformerCharacterPhysicsComponent::ApplyFriction()
{
    float speed = b2Length(velocity_);
    {
        float drop = speed * friction_ * delta;
        float new_speed = b2MaxFloat(0.0f, speed - drop);
        velocity_ *= new_speed / speed;
    }
}

void ni::PlatformerCharacterPhysicsComponent::Accelerate(b2Vec2 desired_velocity)
{
    float  desired_speed = 0.0;
    b2Vec2 desired_direction = b2GetLengthAndNormalize(&desired_speed, desired_velocity);

    float current_speed = b2Dot(velocity_, desired_direction);
    float add_speed = desired_speed - current_speed;

    if (add_speed > 0.0f)
    {
        float steer = on_ground_ ? 1.0f : air_steer_;

        float accel_speed = steer * accelerate_ * max_speed_;
        if (accel_speed > add_speed)
        {
            accel_speed = add_speed;
        }

        velocity_ += accel_speed * desired_direction;
    }
}

void ni::PlatformerCharacterPhysicsComponent::PhysicsUpdate(TransformComponent& transform_component)
{
    if (on_ground_)
    {
        velocity_.y = 0.0f;
    }
    else
    {
        velocity_.y += gravity_ * delta;
    }

    transform_.p += velocity_ * delta;

    std::cout << std::format("\nvelocity: {}, {}", velocity_.x, velocity_.y);

    transform_component.SetPositionInMeters(transform_.p);
    transform_component.SetRotation(b2Rot_GetAngle(transform_.q));
}
