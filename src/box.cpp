#include "../box.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

Box::Box(Scene& scene) {
    auto geometry = BoxGeometry::create();
    auto material = MeshBasicMaterial::create();
    material->color = Color::purple;
    mesh = Mesh::create(geometry, material);
    mesh->position.x = 0;
    mesh->position.y = 0.5;
    mesh->position.z = 0;
    startingPosition = Vector3(mesh->position.x, mesh->position.y, mesh->position.z);
    scene.add(mesh);
}

std::shared_ptr<Mesh> Box::getMesh() {
    return mesh;
}

Vector3 Box::getStartingPosition() {
    return startingPosition;
}
