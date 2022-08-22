#include "ragdoll.hpp"

namespace game
{
    Ragdoll::Ragdoll(Game *game, sf::Vector2f position)
        : Entity(game), shape(std::make_shared<physics::Shape>("models/ragdoll.toml"))
    {
        shape->moveTo(position);
    }

    void Ragdoll::update(float tdelta)
    {
        // despawn if too much damage / time
    }

    void Ragdoll::draw(sf::RenderWindow &window) const
    {
        for (auto l : shape->links)
        {
            if (l->isBroken)
                continue;

            sf::Vertex line[] = {sf::Vertex(l->v1.position),
                                 sf::Vertex(l->v2.position)};
            window.draw(line, 2, sf::Lines);
        }
    }

    void onLinkBroken(physics::RigidLink link)
    {
        // spawn blood
    }
}