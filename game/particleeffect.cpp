#include <cstdlib>
#include "particleeffect.hpp"
#include "game.hpp"

namespace game
{
    // Multiply the rgba channels of a color col by a scalar x
    sf::Color colmul(float x, sf::Color col, bool mulalpha = true)
    {
        if (mulalpha)
            return sf::Color(x * col.r, x * col.g, x * col.b, x * col.a);
        else
            return sf::Color(x * col.r, x * col.g, x * col.b, col.a);
    }

    void ParticleEffect::update(float tdelta)
    {
        // Set circle's origin to dynmaic object's position
        // circle.setOrigin(dynObject->position); // doesn't work
        float radius = circle.getRadius();
        circle.setPosition(dynObject->position.x + radius, dynObject->position.y + radius);

        // Linearly interpolate circle's color based on age
        float agemul = age / maxAge;
        circle.setFillColor(colmul(1.0f - agemul, color1) + colmul(agemul, color2));

        // Age particle and pop from simulation if too old
        age += tdelta;

        if (age >= maxAge)
        {
            // TODO: pop from simulation and free memory
            return;
        }
    }

    void ParticleEffect::draw(sf::RenderWindow &window) const
    {
        if (age >= maxAge)
            return; // we do this for now cuz we dont pop yet

        window.draw(circle);
    }

    sf::Vector2f ParticleEffect::getPosition()
    {
        return dynObject->position;
    }
    void ParticleEffect::setPosition(sf::Vector2f position)
    {
        dynObject->moveTo(position);
    }
    void ParticleEffect::push(sf::Vector2f velocity)
    {
        dynObject->push(velocity);
    }

    // Return a random float between a and b
    float rfloat(float a = 0.f, float b = 1.f)
    {
        return a + (b - a) * (rand() / (static_cast<float>(RAND_MAX)));
    }

    sf::Vector2f addBias(sf::Vector2f direction, float angle)
    {
        // ...
        return direction;
    }

    SparkParticle::SparkParticle(Game *game, sf::Vector2f position, sf::Vector2f direction)
        : ParticleEffect(game, NULL, sf::Color::Black, sf::Color(0, 0, 0, 255), 1.f, rfloat(4.f, 8.f))
    {
        auto speed = rfloat(15.f, 20.f);
        auto velocity = speed * addBias(direction, 0.1f);
        dynObject = std::make_shared<physics::DynamicObject>(position, velocity);

        float saturation = rfloat(0.5f, 1.f);
        color1 = colmul(saturation, sf::Color(160, 0, 255, 255), false);
    }
}