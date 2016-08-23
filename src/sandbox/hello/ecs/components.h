/*
 * Copyright (c) 2016 Galen Cochrane
 * Galen Cochrane <galencochrane@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef LD2016_ECS_H
#define LD2016_ECS_H

#include "metaEcs.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ld2016 {
  void initializeInterComponentRequirements();
  template <typename Derived>
  struct Component {
    static compMask requiredComps;
    static compMask dependentComps;
  };
  #define COMP_DECL(name) struct name : public Component<name>

  COMP_DECL(Existence) {
    compMask componentsPresent = NONE;
  };
  #define ARGS_Position vec
  COMP_DECL(Position) {
    glm::vec3 vec;
    Position(glm::vec3 vec) : vec(vec) {}
  };
  #define ARGS_LinearVel vec
  COMP_DECL(LinearVel) {
    glm::vec3 vec;
    LinearVel(glm::vec3 vec) : vec(vec) {}
  };
  #define ARGS_Orientation quat
  COMP_DECL(Orientation) {
    glm::quat quat;
    Orientation(glm::quat quat) : quat(quat) {}
  };
  #define ARGS_AngularVel quat
  COMP_DECL(AngularVel) {
    glm::quat quat;
    AngularVel(glm::quat quat) : quat(quat) {}
  };
  #define ARGS_CameraView fovy, near, far, aspect
  COMP_DECL(CameraView) {
    float fovy, near, far, aspect;
    CameraView(float fovy, float near, float far, float aspect) : fovy(fovy), near(near), far(far), aspect(aspect) {}
  };
  COMP_DECL(WasdControls) {
    glm::vec3 accel;
  };

  /*struct Existence : public Component<Existence> {
    componentMask componentsPresent = NONE;
  };
  struct Position : public Component<Position> {
    glm::vec3 vec;
  };
  struct LinearVel : public Component<LinearVel> {
    glm::vec3 vec;
  };
  struct Orientation : public Component<Orientation> {
    glm::quat quat;
  };
  struct AngularVel : public Component<AngularVel> {
    glm::quat quat;
  };
  struct CameraView : public Component<CameraView> {
    float fovy, near, far, aspect;
  };
  struct WasdControls : public Component<WasdControls> {
    glm::vec3 accel;
  };*/
  #undef COMP_DECL
}

#endif //LD2016_ECS_H
