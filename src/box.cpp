#include "../include/box.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

Box::Box(Scene& scene, const Color &color) { // Add color parameter
    auto geometry = BoxGeometry::create();
    auto material = MeshBasicMaterial::create();
    material->color = color; // Use the provided color
    mesh = Mesh::create(geometry, material);
    mesh->position.x = 1;
    mesh->position.y = 0;
    mesh->position.z = 1;
    startingPosition = Vector3(mesh->position.x, mesh->position.y, mesh->position.z);
    scene.add(mesh);
}

std::shared_ptr<Mesh> Box::getMesh() {
    return mesh;
}

Vector3 Box::getStartingPosition() {
    return startingPosition;
}
