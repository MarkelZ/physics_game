#include <chrono>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils/input.hpp"
#include "utils/debugwriter.hpp"
#include "entity.hpp"
#include "physics/simulation.hpp"
// #include "physics/rigidbody.hpp"

namespace game
{

    namespace sc = std::chrono;

    class Game
    {
        int width;
        int height;

        const int TPS = 60;
        const float SPT = 1.0f / TPS;

        // std::vector<Ragdoll> ragdolls;
        // std::vector<Particle> particles;
        std::vector<Entity> entities;

        physics::Simluation simulation;
        utils::Debugwriter debugwriter;
        std::unique_ptr<sf::RenderWindow> window;
        utils::Input input;

        void update();
        void draw();

        sc::_V2::system_clock::time_point startTime;
        void restartTimer();
        float elapsedTime();

    public:
        Game(int width, int height);
        void run();
    };
}