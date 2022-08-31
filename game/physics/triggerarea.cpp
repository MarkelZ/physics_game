#include "triggerarea.hpp"
#include "vectormath.hpp"
#include <cmath>

namespace physics
{
    bool CircleArea::IsTouching(std::shared_ptr<Vertex> vertex) const
    {
        sf::Vector2f diff = position - vertex->position;
        return vecm::dot(diff, diff) <= radius2;
    }

    float TriangleArea(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C)
    {
        auto AB = B - A;
        auto AC = C - A;
        float cross = AB.x * AC.y - AB.y * AC.x;
        return std::abs(cross) / 2.f;
    }

    bool CircleArea::IsTouching(std::shared_ptr<RigidLink> link) const
    {
        // https://www.baeldung.com/cs/circle-line-segment-collision-detection
        auto P = link->v1.position;
        auto Q = link->v2.position;
        auto O = position;

        auto OP = P - O;
        auto OQ = Q - O;
        auto QP = Q - P;
        auto PQ = P - Q;

        float min_dist = -1.f;
        float max_dist = std::max(vecm::len(OP), vecm::len(OQ));

        if (vecm::dot(OP, QP) > 0.f && vecm::dot(OQ, PQ) > 0.f)
        {
            min_dist = 2.f * TriangleArea(O, P, Q) / vecm::len(PQ);
        }
        else
        {
            min_dist = std::min(vecm::len(OP), vecm::len(OQ));
        }

        return min_dist <= radius && max_dist >= radius;
    }

    // bool CircleArea::IsTouching(std::shared_ptr<RigidLink> link) const override
    // {
    //     // https://mathworld.wolfram.com/Circle-LineIntersection.html
    //
    //     auto p1 = link->v1.position - position;
    //     auto p2 = link->v2.position - position;
    //
    //     auto d = p2 - p1;
    //     float dr2 = vecm::dot(d, d);
    //     float D = p1.x * p2.y - p2.x * p1.y;
    //     return (radius2 * dr2 - D * D) >= 0;
    // }

    sf::Vector2f CircleArea::getPosition()
    {
        return position;
    }

    void CircleArea::setPosition(sf::Vector2f position)
    {
        this->position = position;
    }

    float CircleArea::getRadius()
    {
        return radius;
    }

    void CircleArea::setRadius(float radius)
    {
        this->radius = radius;
        radius2 = radius * radius;
    }

    float CircleArea::getRadius2()
    {
        return radius2;
    }
}