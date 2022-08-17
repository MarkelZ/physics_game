#include "collider.hpp"
#include "dynamicobject.hpp"

namespace physics
{
    struct Trigger : DynamicObject
    {
        bool enabled;
        std::function<void(float)> onCollision;
        Collider collider;
    };
}