#pragma once
#include "pointparticle.hpp"

namespace physics
{
    struct RigidLink
    {
    public:
        PointParticle &p1;
        PointParticle &p2;

        double length;
        double maxLength;
        bool canBreak;
        bool isBroken;

        RigidLink(PointParticle &p1, PointParticle &p2, bool canBreak);
        RigidLink(PointParticle &p1, PointParticle &p2, double length, bool canBreak);
        double getCurrentLength();

    private:
        static constexpr double MAXLENCOEF = 1.75;
    };
}