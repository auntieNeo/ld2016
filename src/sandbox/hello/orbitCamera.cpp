//
// Created by volundr on 8/20/16.
//

#include "orbitCamera.h"

namespace ld2016 {
    orbitCamera::orbitCamera(const glm::vec3 &position, const glm::quat &orientation)
            : Camera(position, orientation),
              position(position), orientation(orientation) { }
    orbitCamera::~orbitCamera() {

    }
    glm::mat4 orbitCamera::projection(float aspect, float alpha) const {
        return glm::mat4();
    }
}