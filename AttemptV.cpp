#include <iostream>
#include <cmath>
#include <threepp/threepp.hpp>

using namespace threepp;

class MyKeyListener : public KeyListener
{
public:
    MyKeyListener(std::shared_ptr<Object3D>:: cube) : cube_(cube) {}

    void onKeyPressed(KeyEvent& args) //override
    {
        switch (args.key)
        {
            case 'w':
                cube_->position.y += 1;
                break;
            case 's':
                cube_->position.y -= 1;
                break;
            case 'a':
                cube_->position.x -= 1;
                break;
            case 'd':
                cube_->position.x += 1;
                break;
        }
    }

private:
    std::shared_ptr<Object3D> cube_;
};

int main()
{

    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::papayawhip);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 10;
    camera->position.y = 10;


    OrbitControls controls(camera, canvas);


    auto scene = Scene::create();
    auto grid = GridHelper::create(20, 10, Color::red);
    scene->add(grid);


    auto group = Group::create();
    scene->add(group);

    auto cube_geometry = BoxGeometry::create();
    auto cube_material = MeshBasicMaterial::create();
    cube_material->color = Color::purple;
    auto cube = Mesh::create(cube_geometry, cube_material);
    cube->position.z = 1;
    group->add(cube);


    MyKeyListener key_listener(cube);
    canvas.addEventListener(EventType::KEY, &key_listener);

    canvas.onWindowResize([&](WindowSize size){
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        renderer.render(scene, camera);
    });
}
