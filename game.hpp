
#ifndef MAZEGAME_GAME_HPP
#define MAZEGAME_GAME_HPP

#include "threepp/threepp.hpp"

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

    Game() : nextDirection(Direction::LEFT), running(false), shouldMove(false) {}

    void start();
    void stop();
    bool isRunning() const;
    void reset();
    void onKeyPressed(KeyEvent evt) override;
};
#endif //MAZEGAME_GAME_HPP
