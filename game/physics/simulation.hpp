#pragma once
#include "vertex.hpp"
#include "rigidlink.hpp"
#include "trigger.hpp"
#include "shape.hpp"
#include <memory>

namespace physics
{
    class Simulation
    {
    public: // should be private
        std::vector<std::shared_ptr<DynamicObject>> dynobjects;
        std::vector<std::shared_ptr<Vertex>> points;
        std::vector<std::shared_ptr<RigidLink>> links;
        std::vector<std::shared_ptr<Trigger>> triggers;

        float width;
        float height;
        float gravity;

        Simulation(float width, float height, float gravity = 1.0f)
            : width(width), height(height), gravity(gravity) {}

        void update(float tdelta);
        void addShape(Shape shape);
        void addVertex(Vertex vertex);
        void addLink(RigidLink link);
        void addDynamicObject(DynamicObject dynobj);

    private:
        int upd_iters = 4;

        void updateDynamicObjects(float tdelta);
        void updateDynamicObject(DynamicObject &dobj);
        void updateVertices(float tdelta);
        void updateLinks(float tdelta);
        void constrainVertices(float tdelta);
        void checkTriggers(float tdelta);
    };
}