//
// Created by volundr on 8/20/16.
//

#include "cameraOrbit.h"

namespace ld2016 {
    CameraOrbit::CameraOrbit(const glm::vec3 &position, const glm::quat &orientation)
            : Camera(position, orientation),
              position(position), orientation(orientation) { }
    CameraOrbit::~CameraOrbit() {

    }
    glm::mat4 CameraOrbit::projection(float aspect, float alpha) const {
        return glm::mat4();
    }
}