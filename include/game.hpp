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
    Box *box;

    bool winOverlay = false;

    void showWinOverlay() {
        winOverlay = true;
    }

    Maze maze;
    Vector3 startPoint;
    Vector3 endPoint;

    std::chrono::duration<float> duration;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point endTime;

    Game();
    void start();
    void stop();
    bool isRunning() const;
    void reset();
    void onKeyPressed(KeyEvent evt) override;
    bool isWinning(const Vector3 &currentPosition) const;

    void set_new_end_point();
};

#endif //MAZEGAME_GAME_HPP
