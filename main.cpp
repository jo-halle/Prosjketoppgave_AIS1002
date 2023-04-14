
#include "threepp/threepp.hpp"
#include "iostream"
#include <thread>

using namespace threepp;

enum class Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Game : public KeyListener {
public:
    Direction direction;
    Direction nextDirection;
    bool running;

    Game() : direction(Direction::LEFT), nextDirection(Direction::LEFT), running(true) {}

    void start() {
        direction = Direction::LEFT;
        nextDirection = Direction::LEFT;
        running = true;
    }

    void stop() {
        running = false;
    }

    bool isRunning() const {
        return running;
    }

    void reset() {
        direction = Direction::LEFT;
        nextDirection = Direction::LEFT;
        running = false;
    }

    void onKeyPressed(KeyEvent evt) override {
        std::cout << "Key pressed: " << evt.key << std::endl;
        if (evt.key == 87 /*W*/) {
            nextDirection = Direction::UP;
        }
        if (evt.key == 83 /*S*/) {
            nextDirection = Direction::DOWN;
        }
        if (evt.key == 65 /*A*/) {
            nextDirection = Direction::LEFT;
        }
        if (evt.key == 68 /*D*/) {
            nextDirection = Direction::RIGHT;
        }

    }

};

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

    auto group = Group::create();
    scene->add(group);

    auto geometry = BoxGeometry::create();
    auto material = MeshBasicMaterial::create();
    material->color = Color::purple;
    auto mesh = Mesh::create(geometry, material);
    mesh->position.x = 0;
    mesh->position.y = 0.5;
    mesh->position.z = 0;
    group->add(mesh);

    canvas.onWindowResize([&](WindowSize size){
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        if (game.isRunning()) {
            switch (game.nextDirection) {
                case Direction::LEFT:
                    if (game.direction != Direction::RIGHT) {
                        mesh->position.x -= 0.1;
                        game.direction = game.nextDirection;
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                    break;
                case Direction::RIGHT:
                    if (game.direction != Direction::LEFT) {
                        mesh->position.x += 0.1;
                        game.direction = game.nextDirection;
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                    break;
                case Direction::UP:
                    if (game.direction != Direction::DOWN) {
                        mesh->position.z -= 0.1;
                        game.direction = game.nextDirection;
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                    break;
                case Direction::DOWN:
                    if (game.direction != Direction::UP) {
                        mesh->position.z += 0.1;
                        game.direction = game.nextDirection;
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                    break;
                default:
                    break;
            }
        }
        renderer.render(scene, camera);
    });


    return 0;
}
