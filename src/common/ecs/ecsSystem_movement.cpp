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
#include <SDL_timer.h>
#include "ecsSystem_movement.h"

namespace ecs {

  MovementSystem::MovementSystem(State *state) : System(state) {

  }
  bool MovementSystem::onInit() {
    return true;
  }
  void MovementSystem::onTick(float dt) {
    for (auto id : registeredIDs[0]) {
      Position* posComp;
      state->getPosition(id, &posComp);
      LinearVel* velComp;
      state->getLinearVel(id, &velComp);
      posComp->vec += dt * velComp->vec;
    }
    for (auto id : registeredIDs[1]) {
      Orientation* oriComp;
      state->getOrientation(id, &oriComp);
      AngularVel* velComp;
      state->getAngularVel(id, &velComp);
      glm::quat noRotation = glm::angleAxis(0.f, glm::vec3(0.f, 0.f, 1.f));
      /*float partOfRotation = 1000 / dt;
      if (partOfRotation == 0.f) { continue; }
      oriComp->quat *= glm::slerp(noRotation, velComp->quat, partOfRotation);*/
      oriComp->quat *= velComp->quat;
      // FIXME: This may be causing things to occasionally disappear??? Or is it something else?
    }
    for (auto id : registeredIDs[2]) {
      Scale* scale;
      state->getScale(id, &scale);
      ScalarMultFunc* scalarMultFunc;
      state->getScalarMultFunc(id, &scalarMultFunc);
      scale->vec = scalarMultFunc->multByFuncOfTime(scale->lastVec, SDL_GetTicks());
    }
  }
}