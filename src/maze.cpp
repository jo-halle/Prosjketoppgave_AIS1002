
#include "../maze.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

Maze::Maze(unsigned int width, unsigned int height) {
    grid.resize(width, std::vector<bool>(height, false));

    // Initialize the maze grid
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            grid[i][j] = false;
        }
    }
}

    // TODO: Generate a maze using an algorithm, e.g., Prim's, Kruskal's, or recursive backtracking


void Maze::addToScene(Scene& scene) {
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            if (grid[i][j]) {
                auto geometry = BoxGeometry::create();
                auto material = MeshBasicMaterial::create();
                material->color = Color::blue;
                auto wall = Mesh::create(geometry, material);
                wall->position.x = static_cast<float>(i) * 2.0f;
                wall->position.y = 0.5f;
                wall->position.z = static_cast<float>(j) * 2.0f;
                scene.add(wall);
            }
        }
    }
}

bool Maze::isWallAt(int x, int z) const {
    int i = x / 2;
    int j = z / 2;
    return (i >= 0 && i < width) && (j >= 0 && j < height) && grid[i][j];
}
