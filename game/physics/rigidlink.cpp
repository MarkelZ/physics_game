#include "rigidlink.hpp"
#include <cmath>

namespace physics
{
    RigidLink::RigidLink(Vertex &p1, Vertex &p2, bool canBreak)
        : p1(p1), p2(p2), length(length), canBreak(canBreak)
    {
        maxLength = length * MAXLENCOEF;
        isBroken = false;
    }

    RigidLink::RigidLink(Vertex &p1, Vertex &p2, float length, bool canBreak)
        : p1(p1), p2(p2), canBreak(canBreak)
    {
        length = getCurrentLength();
        maxLength = length * MAXLENCOEF;
        isBroken = false;
    }

    float RigidLink::getCurrentLength2()
    {
        auto diff = p1.position - p2.position;
        return diff.x * diff.x + diff.y * diff.y;
        // return vecm::dot(diff, diff);
    }

    float RigidLink::getCurrentLength()
    {
        return std::sqrt(getCurrentLength2());
    }
}