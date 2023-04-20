#include "threepp/threepp.hpp"
#include "game.hpp"
#include "box.hpp"


using namespace threepp;

int main() {
    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::papayawhip);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 10;
    camera->position.y = 10;

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();
    auto game = Game{};
    canvas.addKeyListener(&game);

    auto grid = GridHelper::create(20, 10, Color::red);
    scene->add(grid);

    auto box = Box(*scene);


    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        if (game.isRunning()) {
            if (game.shouldMove) {
                switch (game.nextDirection) {
                    case Direction::LEFT:
                        box.getMesh()->position.x -= 2.0;
                        break;
                    case Direction::RIGHT:
                        box.getMesh()->position.x += 2.0;
                        break;
                    case Direction::UP:
                        box.getMesh()->position.z -= 2.0;
                        break;
                    case Direction::DOWN:
                        box.getMesh()->position.z += 2.0;
                        break;
                    case Direction::REST:
                        break;
                    default:
                        break;
                }

                if (abs(box.getMesh()->position.x - box.getStartingPosition().x) >= 2.0 ||
                    abs(box.getMesh()->position.z - box.getStartingPosition().z) >= 2.0) {
                    game.shouldMove = false;
                }
            }
        }
        renderer.render(scene, camera);
    });

    return 0;
}