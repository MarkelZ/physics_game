#pragma once
#include "pointparticle.hpp"
#include "rigidlink.hpp"
#include <memory>

namespace physics
{
    class Simulation
    {
    public: // should be private
        std::vector<std::shared_ptr<DynamicObject>> dynobjects;
        std::vector<std::shared_ptr<PointParticle>> points;
        std::vector<std::shared_ptr<RigidLink>> links;

        float width;
        float height;
        float gravity;

        void update(float tdelta);
    };
}