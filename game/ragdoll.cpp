#include "ragdoll.hpp"

namespace game
{

    void Ragdoll::onLinkBroken(std::shared_ptr<physics::RigidLink> link)
    {
        // spawn blood
        std::cout << "Link broken in ragdoll with x position ";
        std::cout << shape->vertices[0]->position.x << "\n";
    }

    Ragdoll::Ragdoll(Game *game, sf::Vector2f position)
        : Entity(game), shape(std::make_shared<physics::Shape>("models/ragdoll.toml"))
    {
        shape->moveTo(position);
        for (auto l : shape->links)
        {
            l->onLinkBroken = std::bind(&Ragdoll::onLinkBroken, this, std::placeholders::_1);
        }
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
}