#include "threepp/threepp.hpp"
#include "game.hpp"
#include "box.hpp"
#include "game_imgui.hpp"
#include "texture_loader.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

using namespace threepp;

void set_new_end_point(Game &game) {
    unsigned int startX = 1;
    unsigned int startY = 1;

    game.maze.generateNewEndPoint(startX, startY);
}

int main() {
    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::darkviolet);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 10;
    camera->position.y = 20;

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();
    auto game = Game{};
    canvas.addKeyListener(&game);

    set_new_end_point(game);

    GameImGui gameImGui(static_cast<GLFWwindow *>(canvas.window_ptr()), &game);

    game.maze.addToScene(*scene);
    auto texture = CustomTextureLoader::load("../textures/steve.png");
    auto box = Box(*scene, texture);
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
                    camera->position.z = newPosition.z + 10;
                }

                game.shouldMove = false;

                if (game.isWinning(box.getMesh()->position)) {
                    game.endTime = std::chrono::steady_clock::now();
                    game.duration = game.endTime - game.startTime;
                    std::cout << "You won! Time taken: " << game.duration.count() << " seconds" << std::endl;
                    game.stop();
                    game.showWinOverlay();
                }
            }
        }
        renderer.render(scene, camera);

        gameImGui.render();
    });

    return 0;
}