#pragma once
#include "vertex.hpp"
// #include "vectormath.hpp"

namespace physics
{
    struct RigidLink
    {
    public:
        Vertex &p1;
        Vertex &p2;

        float length;
        float maxLength;
        bool canBreak;
        bool isBroken;

        RigidLink(Vertex &p1, Vertex &p2, bool canBreak);
        RigidLink(Vertex &p1, Vertex &p2, float length, bool canBreak);
        float getCurrentLength();
        float getCurrentLength2();

    private:
        static constexpr float MAXLENCOEF = 1.75f;
    };
}