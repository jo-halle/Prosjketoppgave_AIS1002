#include "../game.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

void Game::start() {
    nextDirection = Direction::LEFT;
    running = true;
    shouldMove = false;
}

void Game::stop() {
    running = false;
}

bool Game::isRunning() const {
    return running;
}

void Game::reset() {
    nextDirection = Direction::LEFT;
    running = false;
    shouldMove = false;
}

void Game::onKeyPressed(KeyEvent evt) {
    if (evt.key == 87 /*W*/) {
        nextDirection = Direction::UP;
        shouldMove = true;
    }
    if (evt.key == 83 /*S*/) {
        nextDirection = Direction::DOWN;
        shouldMove = true;
    }
    if (evt.key == 65 /*A*/) {
        nextDirection = Direction::LEFT;
        shouldMove = true;
    }
    if (evt.key == 68 /*D*/) {
        nextDirection = Direction::RIGHT;
        shouldMove = true;
    }
    if (evt.key == 82 /*R*/) {
        reset();
        start();
    }
}
