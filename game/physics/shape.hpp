#pragma once
#include "rigidlink.hpp"
#include "vertex.hpp"
#include <memory>

namespace physics
{
    struct Shape
    {
        std::vector<std::shared_ptr<Vertex>> vertices;
        std::vector<std::shared_ptr<RigidLink>> links;

        Shape(std::vector<std::shared_ptr<Vertex>> vertices,
              std::vector<std::shared_ptr<RigidLink>> links)
            : vertices(vertices), links(links) {}

        Shape(const char path[]);
    };
}