#ifndef MAZEGAME_GAME_HPP
#define MAZEGAME_GAME_HPP

#include "threepp/threepp.hpp"
#include "maze.hpp"
#include <chrono>

using namespace threepp;

enum class Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    REST
};

class Game : public KeyListener {
public:
    Direction nextDirection;
    bool running;
    bool shouldMove;

    Maze maze;
    Vector3 startPoint;
    Vector3 endPoint;

    std::chrono::duration<float> duration; // Add a duration variable
    std::chrono::steady_clock::time_point startTime;

    Game();
    void start();
    void stop();
    bool isRunning() const;
    void reset();
    void onKeyPressed(KeyEvent evt) override;
    bool isWinning(const Vector3 &currentPosition) const;
};

#endif //MAZEGAME_GAME_HPP
