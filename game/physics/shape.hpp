#pragma once
#include "rigidlink.hpp"
#include "vertex.hpp"
#include <memory>

namespace physics
{
    struct Shape
    {
        std::vector<std::shared_ptr<Vertex>> points;
        std::vector<std::shared_ptr<RigidLink>> links;
    };
}