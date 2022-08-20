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

        // Triangle shape for testing physics
        // auto v1 = std::make_shared<physics::Vertex>(sf::Vector2f(100.f, 400.f), sf::Vector2f(10.f, -20.f));
        // auto v2 = std::make_shared<physics::Vertex>(sf::Vector2f(200.f, 400.f), sf::Vector2f(10.f, -20.f));
        // auto v3 = std::make_shared<physics::Vertex>(sf::Vector2f(150.f, 487.f), sf::Vector2f(0.f, -20.f));
        // auto l1 = std::make_shared<physics::RigidLink>(*v1, *v2);
        // auto l2 = std::make_shared<physics::RigidLink>(*v2, *v3);
        // auto l3 = std::make_shared<physics::RigidLink>(*v3, *v1);
        // simulation.vertices.push_back(v1);
        // simulation.vertices.push_back(v2);
        // simulation.vertices.push_back(v3);
        // simulation.links.push_back(l1);
        // simulation.links.push_back(l2);
        // simulation.links.push_back(l3);

        physics::Shape ragdoll("models/ragdoll.toml");
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

        simulation.update(TPS);

        // Game stuff here
        // ...
    }

    void Game::draw()
    {
        float updateTime = elapsedTime();

        window->clear();

        // Draw game stuff here
        sf::CircleShape circle(4.f, 16);
        circle.setFillColor(sf::Color::Green);
        for (auto p : simulation.vertices)
        {
            auto position = sf::Vector2f(p->position.x - 4.f, p->position.y - 4.f);
            circle.setPosition(position);
            window->draw(circle);
        }

        for (auto e : simulation.links)
        {
            sf::Vertex line[] = {sf::Vertex(e->v1.position),
                                 sf::Vertex(e->v2.position)};
            window->draw(line, 2, sf::Lines);
        }

        // Debug text
        float drawTime = elapsedTime() - updateTime;
        debugwriter.clear();
        debugwriter.stream << "update: " << std::fixed << std::setprecision(1) << updateTime << " ms\n";
        debugwriter.stream << "draw:   " << std::fixed << std::setprecision(1) << drawTime << " ms\n";
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
