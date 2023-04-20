#ifndef MAZEGAME_MAZE_HPP
#define MAZEGAME_MAZE_HPP

#include <vector>
#include <memory>
#include <threepp/threepp.hpp>
#include "box.hpp"

using namespace threepp;

class Maze {
public:
    Maze(unsigned int width, unsigned int height);

    void generateMaze(unsigned int startX, unsigned int startY);

    void addToScene(Scene &scene);

    bool isWallAt(unsigned int x, unsigned int y) const;

private:
    enum CellType { WALL, PATH };

    bool isInside(unsigned int x, unsigned int y) const;

    unsigned int width, height;
    std::vector<std::vector<CellType>> grid;
};

#endif // MAZEGAME_MAZE_HPP
