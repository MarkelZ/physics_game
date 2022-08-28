#include <chrono>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils/input.hpp"
#include "utils/debugwriter.hpp"
#include "entity.hpp"
#include "particleeffect.hpp"
#include "physics/simulation.hpp"
#include "ragdoll.hpp"

namespace game
{

    namespace sc = std::chrono;

    class Game
    {
    private:
        int width;
        int height;

        const int TPS = 60;
        const float SPT = 1.0f / TPS;

        std::unique_ptr<sf::RenderWindow> window;
        utils::Input input;

        void update();
        void draw();

        sc::_V2::system_clock::time_point startTime;
        void restartTimer();
        float elapsedTime();

    public:
        std::vector<Entity *> entities;

        physics::Simulation simulation;
        utils::Debugwriter debugwriter;

        Game(int width, int height);
        void run();

        void addDynamicObject(std::shared_ptr<physics::DynamicObject> dynObj);
        void addShape(physics::Shape &shape);
        void addEntity(Entity *entity);
    };
}