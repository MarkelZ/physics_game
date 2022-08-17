#include <iostream>
#include "game/game.hpp"

int main()
{
    game::Game myGame(1280, 720);
    myGame.run();

    return 0;
}