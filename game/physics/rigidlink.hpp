#pragma once
#include "vertex.hpp"
// #include "vectormath.hpp"

namespace physics
{
    struct RigidLink
    {
    public:
        Vertex &v1;
        Vertex &v2;

        float length;
        float maxLength;
        bool canBreak;
        bool isBroken;

        RigidLink(Vertex &v1, Vertex &v2, bool canBreak = true);
        RigidLink(Vertex &v1, Vertex &v2, float length, bool canBreak = true);
        float getCurrentLength();
        float getCurrentLength2();

    private:
        static constexpr float MAXLENCOEF = 1.75f;
    };
}