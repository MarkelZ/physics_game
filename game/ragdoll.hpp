#pragma once
#include "physics/shape.hpp"
#include "entity.hpp"
#include <memory>
#include <functional>

namespace game
{
    class Game;

    class Ragdoll : Entity
    {
    public:
        std::shared_ptr<physics::Shape> shape; // make private

        Ragdoll(Game *game, sf::Vector2f position);

        void update(float tdelta) override;
        void draw(sf::RenderWindow &window) const override;

    private:
        // std::function<void(physics::RigidLink)> onLinkBroken; // this should go on link
        void onLinkBroken(physics::RigidLink link);
    };
}