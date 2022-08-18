#pragma once
#include <SFML/Graphics.hpp>

namespace vecm
{
    using Vector = sf::Vector2f;

    float dot(Vector v1, Vector v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    Vector scale(Vector v, float alpha)
    {
        return Vector(alpha * v.x, alpha * v.y);
    }
}