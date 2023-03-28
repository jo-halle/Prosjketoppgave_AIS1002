#include "threepp/threepp.hpp"

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

    auto grid = GridHelper::create(20, 10, Color::red);
    scene->add(grid);

    auto group = Group::create();
    scene->add(group);

    auto geometry = BoxGeometry::create();
    auto material = MeshBasicMaterial::create();
    material->color = Color::purple;
    auto mesh = Mesh::create(geometry, material);
    mesh->position.x = 1;
    mesh->position.y = 0.5;
    mesh->position.z = 1;
    group->add(mesh);

    canvas.onWindowResize([&](WindowSize size){
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&] {
        renderer.render(scene, camera);
    });

}
