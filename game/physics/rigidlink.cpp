#include "rigidlink.hpp"
#include <cmath>

namespace physics
{
    RigidLink::RigidLink(PointParticle &p1, PointParticle &p2, bool canBreak)
        : p1(p1), p2(p2), length(length), canBreak(canBreak)
    {
        maxLength = length * MAXLENCOEF;
        isBroken = false;
    }

    RigidLink::RigidLink(PointParticle &p1, PointParticle &p2, double length, bool canBreak)
        : p1(p1), p2(p2), canBreak(canBreak)
    {
        length = getCurrentLength();
        maxLength = length * MAXLENCOEF;
        isBroken = false;
    }

    double RigidLink::getCurrentLength()
    {
        sf::Vector2f diff = p1.position - p2.position;
        return std::sqrt(diff.x * diff.x + diff.y * diff.y);
    }
}