#pragma once
#include "triggerarea.hpp"
#include "dynamicobject.hpp"
#include <functional>

namespace physics
{
    struct Trigger : DynamicObject
    {
        // TriggerArea *area;
        bool enabled;
        std::function<void()> onCollision = []() {};
    };
}