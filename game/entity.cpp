#include "entity.hpp"
#include "game.hpp"

namespace game
{
    Entity::Entity(Game *game, sf::Vector2f position) : game(game), position(position) {}
}