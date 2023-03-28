#ifndef THREEPP_KjorDa_HPP
#define THREEPP_KjorDa_HPP

#include "threepp/loaders/AssimpLoader.hpp"
#include "threepp/objects/Group.hpp"
#include "threepp/input/KeyListener.hpp"

using namespace threepp;

struct wasd {
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
};

struct KjorDa: Object3D, KeyListener {
    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == 87) {
            wasd_.up = true;
        } else if (evt.key == 83) {
            wasd_.down = true;
        } else if (evt.key == 68) {
            wasd_.right = true;
        } else if (evt.key == 65) {
            wasd_.left = true;
        }
    }

    void onKeyReleased(KeyEvent evt) override {
        if (evt.key == 87) {
            wasd_.up = false;
        } else if (evt.key == 83) {
            wasd_.down = false;
        } else if (evt.key == 68) {
            wasd_.right = false;
        } else if (evt.key == 65) {
            wasd_.left = false;
        }
    }

    void driveForwards(float dt) {
        translateX(translationSpeed * dt);
    }

    void driveBackwards(float dt) {
        translateX(-translationSpeed * dt);
    }

    void driveRight(float dt) {
        rotateY(-rotationSpeed * dt);
    }

    void driveLeft(float dt) {
        rotateY(rotationSpeed * dt);
    }

    void update(float dt) {

        if (wasd_.up) {
            driveForwards(dt);
        }
        if (wasd_.down) {
            driveBackwards(dt);
        }
        if (wasd_.right) {
            driveRight(dt);
        }
        if (wasd_.left) {
            driveLeft(dt);
        }
    }

private:
    wasd wasd_;
    float rotationSpeed = 2;
    float translationSpeed = 5;

};

#endif // THREEPP_KjorDa_HPP