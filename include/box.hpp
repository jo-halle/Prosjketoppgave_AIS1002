#ifndef MAZEGAME_BOX_HPP
#define MAZEGAME_BOX_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Box {
public:
    Box(Scene& scene, const std::shared_ptr<Texture> &texture);
    std::shared_ptr<Mesh> getMesh();
    Vector3 getStartingPosition();

private:
    std::shared_ptr<Mesh> mesh;
    Vector3 startingPosition;
};

#endif //MAZEGAME_BOX_HPP