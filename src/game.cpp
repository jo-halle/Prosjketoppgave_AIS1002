#include "../include/game.hpp"
#include "threepp/threepp.hpp"
#include <chrono>

using namespace threepp;

Game::Game() : nextDirection(Direction::LEFT), running(false), shouldMove(false), maze(31, 31) {
    startPoint = Vector3(1.0f, 0.5f, 1.0f);
    endPoint = Vector3(29.0f, 0.5f, 29.0f);
    maze.generateMaze(startPoint.x, startPoint.z, endPoint.x, endPoint.z);
}

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

    // Move the box back to its starting position
    if (box) {
        box->getMesh()->position = box->getStartingPosition();
    }

    startTime = std::chrono::steady_clock::now();
}

bool Game::isWinning(const Vector3 &currentPosition) const {
    Vector2 lastPathUnitPosition = maze.getLastPathUnitPosition();
    Vector3 lastPathUnitPosition3D(lastPathUnitPosition.x, 0.5f, lastPathUnitPosition.y);

    return currentPosition.distanceTo(lastPathUnitPosition3D) < 1.0f;
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
        startTime = std::chrono::steady_clock::now();
    }
}
