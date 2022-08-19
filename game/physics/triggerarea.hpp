#pragma once
#include "vertex.hpp"
#include "rigidlink.hpp"
// #include "vectormath.hpp"

namespace physics
{
    struct TriggerArea
    {
        virtual bool IsTouching(Vertex vertex) const = 0;
        virtual bool IsTouching(RigidLink link) const = 0;
    };

    struct CircleArea : TriggerArea
    {
    public:
        CircleArea(sf::Vector2f position, float radius)
            : position(position), radius(radius), radius2(radius * radius) {}

        bool IsTouching(Vertex vertex) const override
        {
            sf::Vector2f diff = position - vertex.position;
            // return vecm::dot(diff, diff) <= radius2;
            return diff.x * diff.x + diff.y * diff.y <= radius2;
        }

        bool IsTouching(RigidLink link) const override
        {
            // https://mathworld.wolfram.com/Circle-LineIntersection.html
            auto p1 = link.v1.position;
            auto p2 = link.v2.position;
            auto diff = p2 - p1;
            // float dr2 = vecm::dot(diff, diff);
            float dr2 = diff.x * diff.x + diff.y * diff.y;
            float D = p1.x * p2.y - p2.x * p1.y;
            return radius2 * dr2 - D * D >= 0;
        }

        sf::Vector2f getPosition()
        {
            return position;
        }
        void setPosition(sf::Vector2f position)
        {
            this->position = position;
        }
        float getRadius()
        {
            return radius;
        }
        void setRadius(float radius)
        {
            this->radius = radius;
            radius2 = radius * radius;
        }
        float getRadius2()
        {
            return radius2;
        }

    private:
        sf::Vector2f position;
        float radius;
        float radius2;
    };
}