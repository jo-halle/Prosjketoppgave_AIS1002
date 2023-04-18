#include "threepp/threepp.hpp"

using namespace threepp;

enum class Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    REST
};

class Game : public KeyListener {
public:
    Direction nextDirection;
    bool running;
    bool shouldMove;

    Game() : nextDirection(Direction::LEFT), running(false), shouldMove(false) {}

    void start() {

        nextDirection = Direction::LEFT;
        running = true;
        shouldMove = false;
    }


    bool isRunning() const {
        return running;
    }

    void reset() {
        nextDirection = Direction::LEFT;
        running = false;
        shouldMove = false;
    }

    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == 87 /*W*/) {
            nextDirection = Direction::UP;
            shouldMove = true;
        }
        if (evt.key == 83 /*S*/) {
            nextDirection = Direction::DOWN;
            shouldMove = true;
        }
        if (evt.key == 65 /*A*/) {
            nextDirection = Direction::LEFT;
            shouldMove = true;
        }
        if (evt.key == 68 /*D*/) {
            nextDirection = Direction::RIGHT;
            shouldMove = true;
        }
        if (evt.key == 82 /*R*/) {
            reset();
            start();
        }
//        if (evt.key == 32 /*SPACE*/) {
//            nextDirection = Direction::REST;
//        }
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
    auto startingPosition = Vector3(mesh->position.x, mesh->position.y, mesh->position.z);
    group->add(mesh);

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
                        mesh->position.x -= 2.0;
                        break;
                    case Direction::RIGHT:
                        mesh->position.x += 2.0;
                        break;
                    case Direction::UP:
                        mesh->position.z -= 2.0;
                        break;
                    case Direction::DOWN:
                        mesh->position.z += 2.0;
                        break;
                    case Direction::REST:
                        break;
                    default:
                        break;
                }

                // Check if the box has moved one unit
                if (abs(mesh->position.x - startingPosition.x) >= 2.0 ||
                    abs(mesh->position.z - startingPosition.z) >= 2.0) {
                    game.shouldMove = false;
                }
            }
        }
        renderer.render(scene, camera);
    });

    return 0;
}