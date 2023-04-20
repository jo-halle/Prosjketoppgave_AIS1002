#ifndef MAZEGAME_MAZE_HPP
#define MAZEGAME_MAZE_HPP

#include "threepp/threepp.hpp"
#include <vector>

using namespace threepp;

class Maze {
public:
    Maze() = default;
    Maze(unsigned int width, unsigned int height);
    void addToScene(Scene& scene);
    bool isWallAt(int x, int z) const;

private:
    std::vector<std::vector<bool>> grid;
    unsigned int width;
    unsigned int height;
};

#endif // MAZEGAME_MAZE_HPP
