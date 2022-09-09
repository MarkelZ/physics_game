#include "player.hpp"
#include "game.hpp"
#include "bomb.hpp"

namespace game
{

    Player::Player(Game *game, sf::Vector2f position) : Entity(game), rect(sf::Vector2f(64.f, 64.f))
    {
        dynobj = std::make_shared<physics::Vertex>(position);
        dynobj->elasticity = 0.25f;
        dynobj->airFriction = 0.95f;
        dynobj->collideFriction = 0.5f;
        rect.setPosition(position);
        rect.setFillColor(sf::Color::Green);
        game->addEntity(this);
        game->simulation.addVertex(dynobj);
    }

    void Player::update(float tdelta)
    {
        // Movement
        if (game->input.actionDown(Input::Action::Up))
        {
            dynobj->push(sf::Vector2f(0.f, -2.5f));
        }
        if (game->input.actionDown(Input::Action::Right))
        {
            dynobj->push(sf::Vector2f(1.5f, 0.f));
        }
        if (game->input.actionDown(Input::Action::Left))
        {
            dynobj->push(sf::Vector2f(-1.5f, 0.f));
        }

        // Shoot
        if (game->input.mouseButtonPressed(sf::Mouse::Button::Left))
        {
            auto mousepos = sf::Vector2f(game->input.getMouseCurrentPosition());
            auto velocity = 0.1f * (mousepos - dynobj->position);
            auto size = rect.getSize();
            auto position = sf::Vector2f(dynobj->position.x + size.x / 2.f,
                                         dynobj->position.y - size.y / 2.f);
            auto bomb = new Bomb(game, position, velocity);
            game->addEntity(bomb);
            game->simulation.addTrigger(bomb->trigger);
        }

        rect.setPosition(sf::Vector2f(dynobj->position.x, dynobj->position.y - rect.getSize().y));
    }

    void Player::draw(sf::RenderWindow &window) const
    {
        window.draw(rect);
    }
}