#pragma once
#include "entity.hpp"

namespace game
{
    class Player : public Entity
    {
        Player(Game *game, sf::Vector2f position);
    };
}