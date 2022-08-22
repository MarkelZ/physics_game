#include "game.hpp"
#include <cstdlib>

namespace game
{
    Game::Game(int width, int height)
        : width(width), height(height),
          debugwriter("content/freemono.ttf", 24, sf::Color::White),
          input(), simulation(width, height)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(width, height), "Physics Demo",
            sf::Style::Titlebar | sf::Style::Close, settings);
        window->setFramerateLimit(TPS);
    }

    void Game::run()
    {
        while (window->isOpen())
        {
            update();
            draw();
        }
    }

    void Game::addDynamicObject(std::shared_ptr<physics::DynamicObject> dynObj)
    {
        simulation.addDynamicObject(dynObj);
    }

    void Game::addShape(physics::Shape &shape)
    {
        simulation.addShape(shape);
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

        if (input.actionPressed(utils::Input::Action::Right))
        {
            auto r = std::make_shared<Ragdoll>(this, sf::Vector2f(0.f, 400.f));
            float speed = 1.f + 2.f * (rand() / (static_cast<float>(RAND_MAX)));
            float spin = 5.f + 10.f * (rand() / (static_cast<float>(RAND_MAX)));
            r->shape->push(speed * sf::Vector2f(5.f, -10.f));
            r->shape->vertices[0]->prevpos.x -= spin; // give some spin to ragdoll
            ragdolls.push_back(r);
            simulation.addShape(*r->shape);
        }

        for (auto p : particles)
        {
            p->update(SPT);
        }

        for (auto r : ragdolls)
        {
            r->update(SPT);
        }
    }

    void Game::draw()
    {
        float updateTime = elapsedTime();

        window->clear();

        for (auto p : particles)
        {
            p->draw(*window);
        }

        for (auto r : ragdolls)
        {
            r->draw(*window);
        }

        // Debug text
        float drawTime = elapsedTime() - updateTime;
        debugwriter.clear();
        debugwriter.stream << "Press D or Right to spawn ragdoll.\n";
        debugwriter.stream << "Press W or Up to spawn particles.\n";

        debugwriter.stream << "RigidLinks:   " << simulation.links.size() << ". ";
        debugwriter.stream << "Vertices:   " << simulation.vertices.size() << ". ";
        debugwriter.stream << "Particles:   " << particles.size() << "\n";

        debugwriter.stream << "Update: " << std::fixed << std::setprecision(1) << updateTime << " ms. ";
        debugwriter.stream << "Draw:   " << std::fixed << std::setprecision(1) << drawTime << " ms\n";

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
