//
// Created by volundr on 8/20/16.
//

#ifndef LD2016_CAMERAORBIT_H
#define LD2016_CAMERAORBIT_H

#include "../../common/camera.h"

namespace ld2016 {

    class orbitCamera : public Camera {
        glm::vec3 position;
        glm::quat orientation;
    public:
        orbitCamera(const glm::vec3 &position, const glm::quat &orientation);
        ~orbitCamera();
        glm::mat4 projection(float aspect, float alpha = 1.0f) const;
    };

}

#endif //LD2016_CAMERAORBIT_H
