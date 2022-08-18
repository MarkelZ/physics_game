#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace game
{
    class Game;

    class Entity
    {
    public:
        Entity(Game *game, sf::Vector2f position);

        sf::Vector2f position; // should be dynobject

        virtual void update(float tdelta) const = 0;
        virtual void draw(sf::RenderWindow &window) const = 0;

    private:
        Game *game;
    };
}