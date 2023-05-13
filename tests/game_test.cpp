#include <iostream>
#include <cassert>
#include "../include/game.hpp"

void test_game() {
    Game game;

    assert(!game.isRunning());

    game.start();

    assert(game.isRunning());

    game.stop();

    assert(!game.isRunning());

    game.reset();

    assert(!game.isRunning());

    assert(!game.winOverlay);

    game.showWinOverlay();

    assert(game.winOverlay);

    std::cout << "Game test passed!" << std::endl;
}
