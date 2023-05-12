#include <iostream>
#include <cassert>
#include "../include/maze.hpp"

void test_maze_generation() {
    unsigned int width = 31;
    unsigned int height = 31;
    unsigned int startX = 1;
    unsigned int startY = 1;
    unsigned int endX = 29;
    unsigned int endY = 29;

    Maze maze(width, height);
    maze.generateMaze(startX, startY, endX, endY);

    assert(!maze.isWallAt(startX, startY));
    assert(!maze.isWallAt(endX, endY));

    for (unsigned int x = 0; x < width; ++x) {
        assert(maze.isWallAt(x, 0));
        assert(maze.isWallAt(x, height - 1));
    }
    for (unsigned int y = 0; y < height; ++y) {
        assert(maze.isWallAt(0, y));
        assert(maze.isWallAt(width - 1, y));
    }

    std::cout << "Maze generation test passed!" << std::endl;
}

int main() {
    test_maze_generation();
    // Call other test functions here

    std::cout << "All tests passed!" << std::endl;
    return 0;
}