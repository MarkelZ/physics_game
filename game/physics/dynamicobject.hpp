#pragma once
#include <SFML/Graphics.hpp>

namespace physics
{
    struct DynamicObject
    {
        sf::Vector2f position;
        sf::Vector2f prevpos;
        // sf::Vector2f velocity;
        // sf::Vector3f force;

        float gravityMul;
        float airFriction;

        bool isFixed;

        DynamicObject(sf::Vector2f position, sf::Vector2f prevpos, float gravityMul = 1.0f,
                      float airFriction = 0.999f, bool isFixed = false)
            : position(position), prevpos(prevpos),
              gravityMul(gravityMul), airFriction(airFriction), isFixed(isFixed) {}

        void push(sf::Vector2f velocity);
        void moveTo(sf::Vector2f position);
        void moveBy(sf::Vector2f direction);
    };
}