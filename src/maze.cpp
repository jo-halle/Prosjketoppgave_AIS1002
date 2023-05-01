#include "maze.hpp"
#include "texture_loader.hpp"

#include <random>
#include <stack>
#include <algorithm>
#include <queue>
#include <threepp/threepp.hpp>
#include <ctime>
#include <cstdlib>

using namespace threepp;

Maze::Maze(unsigned int width, unsigned int height)
        : width(width), height(height) {
    srand(time(0));
    grid.resize(height, std::vector<CellType>(width, WALL));
}

Vector2 Maze::getEndPoint() const {
    return endPoint;
}

void Maze::generateMaze(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY) {
    int minLength = 20; // Set your desired minimum path length here

    std::vector<std::pair<int, int>> directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    auto rng = std::default_random_engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, directions.size() - 1);
    std::uniform_real_distribution<float> deadEndProbability(0.0, 1.0);

    float deadEndThreshold = 0.5f; // Increase this value to create more dead ends

    do {
        // Clear the grid
        for (auto &row : grid) {
            std::fill(row.begin(), row.end(), WALL);
        }

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
    } while (shortestPathLength(startX, startY, endX, endY) < minLength);
}

Vector2 Maze::getLastPathUnitPosition() const {
    return lastPathUnitPosition;
}

void Maze::addToScene(Scene &scene) {
    auto texture = CustomTextureLoader::load("../textures/Hex.png");
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

int Maze::shortestPathLength(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY) const {
    std::vector<std::pair<int, int>> directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::queue<std::tuple<int, int, int>> q;
    q.push({startX, startY, 0});
    visited[startY][startX] = true;

    while (!q.empty()) {
        auto [x, y, distance] = q.front();
        q.pop();

        if (x == endX && y == endY) {
            return distance;
        }

        for (const auto &[dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (isInside(nx, ny) && grid[ny][nx] == PATH && !visited[ny][nx]) {
                visited[ny][nx] = true;
                q.push({nx, ny, distance + 1});
            }
        }
    }

    return -1;
}

void Maze::generateNewEndPoint(unsigned int startX, unsigned int startY) {
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<int> distX(1, width - 2);
    std::uniform_int_distribution<int> distY(1, height - 2);

    int newEndX, newEndY;
    do {
        newEndX = distX(rng);
        newEndY = distY(rng);
    } while ((newEndX == startX && newEndY == startY) || isWallAt(newEndX, newEndY));

    endPoint.x = newEndX;
    endPoint.y = newEndY;
}


