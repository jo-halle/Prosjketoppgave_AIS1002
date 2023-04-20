#include "../include/maze.hpp"
#include <random>
#include <stack>
#include <algorithm>
#include <threepp/threepp.hpp>

using namespace threepp;

Maze::Maze(unsigned int width, unsigned int height)
        : width(width), height(height) {
    grid.resize(height, std::vector<CellType>(width, WALL));
}

void Maze::generateMaze(unsigned int startX, unsigned int startY) {
    std::stack<std::pair<unsigned int, unsigned int>> stack;
    stack.push({startX, startY});

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        stack.pop();

        if (!isInside(x, y) || grid[y][x] == PATH) {
            continue;
        }

        grid[y][x] = PATH;

        std::vector<std::pair<int, int>> directions = {
                {0, 2}, {2, 0}, {0, -2}, {-2, 0}};

        std::shuffle(directions.begin(), directions.end(), std::default_random_engine(std::random_device{}()));

        for (const auto &[dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (isInside(nx, ny) && grid[ny][nx] == WALL) {
                grid[y + dy / 2][x + dx / 2] = PATH;
                stack.push({nx, ny});
            }
        }
    }
}

void Maze::addToScene(Scene &scene) {
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            if (isWallAt(x, y)) {
                Box box(scene, Color::purple); // Set the box color
                auto cube = box.getMesh();
                cube->position.set(x, 0, y);
                scene.add(cube);
            }
        }
    }
}
