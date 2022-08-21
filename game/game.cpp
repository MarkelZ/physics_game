#include "game.hpp"

namespace game
{
    Game::Game(int width, int height)
        : width(width), height(height),
          debugwriter("content/freemono.ttf", 32, sf::Color::White),
          input(), simulation(width, height)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(width, height), "Physics Demo",
            sf::Style::Titlebar | sf::Style::Close, settings);
        window->setFramerateLimit(TPS);

        // Code for testing the physics
        physics::Shape ragdoll("models/ragdoll.toml");
        ragdoll.push(sf::Vector2f(5.f, -32.f));
        ragdoll.vertices[0]->prevpos.x = 0.f; // give some spin to ragdoll
        ragdoll.moveTo(sf::Vector2f(400.f, 500.f));
        simulation.addShape(ragdoll);
    }

    void Game::run()
    {
        while (window->isOpen())
        {
            update();
            draw();
        }
    }

    void Game::update()
    {
        restartTimer();
        input.update();

        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::LostFocus:
                std::cout << "Lost focus.\n";
                break;
            default:
                break;
            }
        }

        simulation.update(SPT);

        // Game stuff here
        if (input.actionPressed(utils::Input::Action::Up))
        {
            for (int i = 0; i < 20; i++)
            {
                auto p = std::make_shared<SparkParticle>(
                    this, sf::Vector2f(300.f, 300.f + i * 10), sf::Vector2f(1.f, 0.f));
                particles.push_back(p);
                simulation.addDynamicObject(p->dynObject);
            }
        }

        for (auto p : particles)
        {
            p->update(SPT);
        }
    }

    void Game::draw()
    {
        float updateTime = elapsedTime();

        window->clear();

        // Draw game stuff here
        sf::CircleShape circle(4.f, 16);
        circle.setFillColor(sf::Color::Green);
        for (auto v : simulation.vertices)
        {
            auto position = sf::Vector2f(v->position.x - 4.f, v->position.y - 4.f);
            circle.setPosition(position);
            window->draw(circle);
        }

        for (auto l : simulation.links)
        {
            if (l->isBroken)
                continue;

            sf::Vertex line[] = {sf::Vertex(l->v1.position),
                                 sf::Vertex(l->v2.position)};
            window->draw(line, 2, sf::Lines);
        }

        for (auto p : particles)
        {
            p->draw(*window);
        }

        // Debug text
        float drawTime = elapsedTime() - updateTime;
        debugwriter.clear();
        debugwriter.stream << "Update: " << std::fixed << std::setprecision(1) << updateTime << " ms\n";
        debugwriter.stream << "Draw:   " << std::fixed << std::setprecision(1) << drawTime << " ms\n";
        debugwriter.stream << "Entities:   " << particles.size() << "\n";
        debugwriter.draw(*window);

        // This displays window on screen (not part of debug)
        window->display();
    }

    void Game::restartTimer()
    {
        startTime = sc::high_resolution_clock::now();
    }

    float Game::elapsedTime()
    {
        auto elapsed = std::chrono::high_resolution_clock::now() - startTime;
        long long microseconds = sc::duration_cast<std::chrono::microseconds>(elapsed).count();
        float milliseconds = microseconds / 1000.0f;
        return milliseconds;
    }
}
