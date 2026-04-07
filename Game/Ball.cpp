#include "Ball.h"

#include <math_functions.h>

#include <memory>
#include <utility>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <collision.h>
#include <GameObjectTag.h>
#include <Id.h>
#include <box2d.h>
#include <types.h>
#include <Converter.h>
#include <TransformComponent.h>
#include <ShapeGraphicsComponent.h>
#include <ComponentStore.h>
#include <PhysicsComponent.h>
#include <iostream>

Ball::Ball(ni::Id<GameObjectTag> id, b2Vec2 starting_position, ni::ComponentStore& component_store, b2WorldId world_id, sf::Color color, float radius)
{
    id_ = id;

    // GRAPHICS
    ni::TransformComponent ball_transform;
    ball_transform.SetPositionInMeters(starting_position);

    component_store.AttachTransformComponent(id, ball_transform);

    sf::CircleShape shape(converter::MetersToPixels(radius));
    shape.setFillColor(color);
    shape.setOrigin({ converter::MetersToPixels(radius), converter::MetersToPixels(radius) });
    auto ball_graphics = std::make_unique<ni::ShapeGraphicsComponent<sf::CircleShape>>(shape);

    component_store.AttachGraphicsComponent(id, std::move(ball_graphics));

    // PHYSICS
    b2BodyDef ball_body_def = b2DefaultBodyDef();
    ball_body_def.type        = b2_dynamicBody;
    ball_body_def.position    = starting_position;
    ball_body_def.enableSleep = false;

    b2Circle circle_shape = { {0, 0}, radius };

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 1.0f;
    shape_def.material.friction = 0.3f;

    b2BodyId ball_body_id = b2CreateBody(world_id, &ball_body_def);
    b2CreateCircleShape(ball_body_id, &shape_def, &circle_shape);

    ni::PhysicsComponent ball_physics(ball_body_id);
    component_store.AttachPhysicsComponent(id, ball_physics);
}
