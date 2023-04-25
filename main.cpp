#include "threepp/threepp.hpp"
#include "game.hpp"
#include "box.hpp"
#include <iostream>

using namespace threepp;

int main() {
    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::papayawhip);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 10;
    camera->position.y = 20;

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();
    auto game = Game{};
    canvas.addKeyListener(&game);

    game.maze.addToScene(*scene);
    auto box = Box(*scene, Color::orange);
    scene->add(box.getMesh());
    game.box = &box;

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        if (game.isRunning()) {
            if (game.shouldMove) {
                Vector3 newPosition = box.getMesh()->position;

                switch (game.nextDirection) {
                    case Direction::LEFT:
                        newPosition.x -= 1.0;
                        break;
                    case Direction::RIGHT:
                        newPosition.x += 1.0;
                        break;
                    case Direction::UP:
                        newPosition.z -= 1.0;
                        break;
                    case Direction::DOWN:
                        newPosition.z += 1.0;
                        break;
                    case Direction::REST:
                        break;
                    default:
                        break;
                }

                if (!game.maze.isWallAt(newPosition.x, newPosition.z)) {
                    box.getMesh()->position = newPosition;

                    camera->position.x = newPosition.x;
                    camera->position.z = newPosition.z +10;
                }

                game.shouldMove = false;

                // Check for winning condition
                if (game.isWinning(box.getMesh()->position)) {
                    auto endTime = std::chrono::steady_clock::now();
                    game.duration = endTime - game.startTime;
                    std::cout << "You won! Time taken: " << game.duration.count() << " seconds" << std::endl;
                    game.stop();
                }
            }
        }
        renderer.render(scene, camera);
    });

    return 0;
}
