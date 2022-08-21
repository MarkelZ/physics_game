#include <chrono>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils/input.hpp"
#include "utils/debugwriter.hpp"
#include "entity.hpp"
#include "particleeffect.hpp"
#include "physics/simulation.hpp"

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

        // std::vector<std::shared_ptr<Entity>> entities;
        std::vector<std::shared_ptr<ParticleEffect>> particles;

        physics::Simulation simulation;
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