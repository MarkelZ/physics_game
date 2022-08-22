#include "bomb.hpp"

namespace game
{
    Bomb::Bomb(Game *game, sf::Vector2f position, sf::Vector2f velocity)
        : Entity(game)
    {
        // trigger = std::make_shared<physics::Trigger>();
        // trigger->onCollision = std::bind(&explode, this);
    }

    void Bomb::update(float tdelta)
    {
    }

    void Bomb::draw(sf::RenderWindow &window) const
    {
    }

    void Bomb::explode()
    {
        // boom
    }
}