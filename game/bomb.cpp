#include <iostream>
#include "bomb.hpp"
#include "game.hpp"

namespace game
{
    Bomb::Bomb(Game *game, sf::Vector2f position, sf::Vector2f velocity)
        : Entity(game), circle(RADIUS, 16)
    {
        trigger = std::make_shared<physics::Trigger>(position, velocity);
        trigger->onCollision = std::bind(&Bomb::explode, this);

        circle.setFillColor(sf::Color(255, 128, 255, 255));
    }

    void Bomb::update(float tdelta)
    {
        // THIS IS DEBUG!!!
        // trigger->position = game->input.getMouseCurrentPosition();

        circle.setPosition(trigger->position);
    }

    void Bomb::draw(sf::RenderWindow &window) const
    {
        window.draw(circle);
    }

    void Bomb::explode()
    {
        circle.setFillColor(sf::Color::Cyan);
    }
}