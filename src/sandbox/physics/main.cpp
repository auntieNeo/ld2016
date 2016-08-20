/*
 * Copyright (c) 2016 Jonathan Glines
 * Jonathan Glines <jonathan@glines.net>
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

#include <btBulletDynamicsCommon.h>

#include <cstdio>
#include <cstdlib>

#include "../../common/scene.h"
// #include "../../common/wasdCamera.h"

/* Global physics data structures */
btDispatcher *dispatcher;
btBroadphaseInterface *broadphase;
btConstraintSolver *constraintSolver;
btCollisionConfiguration *collisionConfiguration;
btDynamicsWorld *dynamicsWorld;

void init_bullet() {
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  broadphase = new btDbvtBroadphase();
  constraintSolver = new btSequentialImpulseConstraintSolver();
  dynamicsWorld = new btDiscreteDynamicsWorld(
      dispatcher,
      broadphase,
      constraintSolver,
      collisionConfiguration);
  dynamicsWorld->setGravity(btVector3(0.0f, 0.0f, -9.81f));
}

void destroy_bullet() {
  delete dynamicsWorld;
  delete constraintSolver;
  delete broadphase;
  delete dispatcher;
  delete collisionConfiguration;
}

void main_loop() {
  dynamicsWorld->stepSimulation(1.0f / 60.0f);
}

int main(int argc, char **argv) {
  init_bullet();

  /* TODO: Actually run the simulation here */

  destroy_bullet();

  return EXIT_SUCCESS;
}
