#pragma once
#include "dynamicobject.hpp"

namespace physics
{
    struct Vertex : DynamicObject
    {
        float elasticity;
        float collideFriction;

        Vertex(sf::Vector2f position, bool isFixed, float elasticity = 1.0f, float collideFriction = 1.0f)
            : DynamicObject(sf::Vector2f(position.x, position.y),
                            sf::Vector2f(position.x, position.y),
                            1.0f, 0.95f, isFixed),
              elasticity(elasticity), collideFriction(collideFriction) {}

        Vertex(sf::Vector2f position, sf::Vector2f velocity, bool isFixed)
            : DynamicObject(sf::Vector2f(position.x, position.y),
                            sf::Vector2f(position.x - velocity.x, position.y - velocity.y),
                            1.0f, 0.95f, isFixed),
              elasticity(elasticity), collideFriction(collideFriction) {}
    };
}