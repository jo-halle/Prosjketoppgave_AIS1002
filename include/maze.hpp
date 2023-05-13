#ifndef MAZEGAME_MAZE_HPP
#define MAZEGAME_MAZE_HPP

#include <vector>
#include <memory>
#include "threepp/threepp.hpp"
#include "box.hpp"

using namespace threepp;

using Vector2 = Vector2;

class Maze {
public:
    Maze(unsigned int width, unsigned int height);

    void generateMaze(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY);

    void generateNewEndPoint(unsigned int startX, unsigned int startY);

    void addToScene(Scene &scene);

    bool isWallAt(unsigned int x, unsigned int y) const;

    Vector2 getLastPathUnitPosition() const;

    Vector2 getEndPoint() const;


    unsigned int getWidth() const;
    unsigned int getHeight() const;

private:
    enum CellType { WALL, PATH };

    bool isInside(unsigned int x, unsigned int y) const;

    int shortestPathLength(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY) const;

    Vector2 lastPathUnitPosition;
    Vector2 endPoint;

    unsigned int width, height;
    std::vector<std::vector<CellType>> grid;
};

inline bool Maze::isInside(unsigned int x, unsigned int y) const {
    return x < width && y < height;
}

inline bool Maze::isWallAt(unsigned int x, unsigned int y) const {
    if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
        return true;
    }
    if (isInside(x, y)) {
        return grid[y][x] == WALL;
    }
    return false;
}

#endif // MAZEGAME_MAZE_HPP
