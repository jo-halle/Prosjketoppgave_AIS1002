#ifndef MAZEGAME_MAZE_HPP
#define MAZEGAME_MAZE_HPP

#include <vector>
#include <memory>
#include "threepp/threepp.hpp"
#include "box.hpp"

using namespace threepp;

class Maze {
public:
    Maze(unsigned int width, unsigned int height);

    void generateMaze(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY);

    void addToScene(Scene &scene);

    bool isWallAt(unsigned int x, unsigned int y) const;

    Vector2 getLastPathUnitPosition() const;

private:
    enum CellType { WALL, PATH };

    bool isInside(unsigned int x, unsigned int y) const;

    Vector2 lastPathUnitPosition;

    unsigned int width, height;
    std::vector<std::vector<CellType>> grid;
};

inline bool Maze::isInside(unsigned int x, unsigned int y) const {
    return x < width && y < height;
}

inline bool Maze::isWallAt(unsigned int x, unsigned int y) const {
    if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
        return true; // Check if (x, y) is a boundary cell
    }
    if (isInside(x, y)) {
        return grid[y][x] == WALL;
    }
    return false;
}

#endif // MAZEGAME_MAZE_HPP