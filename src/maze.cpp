#include "../include/maze.hpp"
#include <random>
#include <stack>
#include <algorithm>
#include <threepp/threepp.hpp>
#include "texture_loader.hpp"

using namespace threepp;

Maze::Maze(unsigned int width, unsigned int height)
        : width(width), height(height) {
    grid.resize(height, std::vector<CellType>(width, WALL));
}

void Maze::generateMaze(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY) {
    std::vector<std::pair<int, int>> directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    auto rng = std::default_random_engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, directions.size() - 1);
    std::uniform_real_distribution<float> deadEndProbability(0.0, 1.0);

    float deadEndThreshold = 0.5f; // Increase this value to create more dead ends

    std::vector<std::pair<int, int>> frontier;
    frontier.emplace_back(startX, startY);

    while (!frontier.empty()) {
        auto current = frontier.back();
        frontier.pop_back();

        if (!isInside(current.first, current.second) || grid[current.second][current.first] == PATH) {
            continue;
        }

        grid[current.second][current.first] = PATH;
        lastPathUnitPosition = Vector2(current.first, current.second);

        std::vector<std::pair<int, int>> neighbors;
        for (const auto &[dx, dy] : directions) {
            int nx = current.first + dx * 2;
            int ny = current.second + dy * 2;

            if (isInside(nx, ny) && grid[ny][nx] == WALL) {
                int px = current.first + dx;
                int py = current.second + dy;
                if (grid[py][px] == PATH) {
                    continue;
                }
                neighbors.emplace_back(nx, ny);
            }
        }

        // Create dead ends
        if (!neighbors.empty()) {
            std::shuffle(neighbors.begin(), neighbors.end(), rng);
            for (size_t i = 0; i < neighbors.size(); i++) {
                if (deadEndProbability(rng) < deadEndThreshold) {
                    continue;
                }
                grid[current.second + (neighbors[i].second - current.second) / 2][current.first + (neighbors[i].first - current.first) / 2] = PATH;
                frontier.push_back(neighbors[i]);
            }
        }
    }
}

Vector2 Maze::getLastPathUnitPosition() const {
    return lastPathUnitPosition;
}


void Maze::addToScene(Scene &scene) {
    auto texture = CustomTextureLoader::load("C:/Users/Jo/project_template-master/textures/Hex.png");
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            if (isWallAt(x, y)) {
                Box box(scene, texture);
                auto cube = box.getMesh();
                cube->position.set(x, 0, y);
                scene.add(cube);
            }
        }
    }
}