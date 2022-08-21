#pragma once
#include "physics/shape.hpp"
#include "entity.hpp"
#include <memory>

namespace game
{
    class Game;

    class Ragdoll : Entity
    {
    public:
        Ragdoll(const char path[]);

    private:
        std::shared_ptr<physics::Shape> shape;
    };
}