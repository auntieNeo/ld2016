/*
 * Copyright (c) 2016 Jonathan Glines, Galen Cochrane
 * Jonathan Glines <jonathan@glines.net>
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

#include <cstdlib>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "../../common/debug.h"
#include "../../common/game.h"
#include "../../common/meshObject.h"
#include "../../common/scene.h"
#include "../../common/wasdCamera.h"

using namespace ld2016;

class AnimationDemo : public Game {
  private:
    std::shared_ptr<WasdCamera> m_camera;
    std::shared_ptr<MeshObject> m_mesh;
  public:
    AnimationDemo(int argc, char **argv)
      : Game(argc, argv, "Animation Demo")
    {
      // Populate the graphics scene
      m_camera = std::shared_ptr<WasdCamera>(
          new WasdCamera(
            80.0f * ((float)M_PI / 180.0f),  // fovy
            0.1f,  // near
            100000.0f,  // far
            glm::vec3(0.0f, 0.0f, 15.0f),  // position
            glm::angleAxis(
              (float)M_PI / 4.0f,
              glm::vec3(1.0f, 0.0f, 0.0f))  // orientation
            ));
      this->scene()->addObject(m_camera);
      this->setCamera(m_camera);
      m_mesh = std::shared_ptr<MeshObject>(
          new MeshObject(
            "assets/models/sphere.dae",  // mesh
            "assets/textures/rt_bunny.png"  // texture
            ));
      this->scene()->addObject(m_mesh);
      float delta = 0.3f;
      for (int i = 0; i < 100; ++i) {
        Debug::drawLine(
            glm::vec3((float)i * delta, 0.0f, 0.0f),
            glm::vec3((float)i * delta, 1.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 1.0f));
        Debug::drawLine(
            glm::vec3(0.0f, (float)i * delta, 0.0f),
            glm::vec3(1.0f, (float)i * delta, 0.0f),
            glm::vec3(1.0f, 0.0f, 1.0f));
      }

      Debug::drawLine(
          glm::vec3(10 * delta, 0.f, 4.f),
          glm::vec3(11 * delta, 0.f, 2.f),
          glm::vec3(0.f, 1.f, 0.f));
      Debug::drawLine(
          glm::vec3(11 * delta, 0.f, 2.f),
          glm::vec3(12 * delta, 0.f, 4.f),
          glm::vec3(0.f, 1.f, 0.f));

      Debug::drawLine(
          glm::vec3(13 * delta, 0.f, 2.f),
          glm::vec3(13 * delta, 0.f, 4.f),
          glm::vec3(0.f, 1.f, 0.f));

      Debug::drawLine(
          glm::vec3(14 * delta, 0.f, 2.f),
          glm::vec3(14 * delta, 0.f, 4.f),
          glm::vec3(0.f, 1.f, 0.f));
      Debug::drawLine(
          glm::vec3(14 * delta, 0.f, 4.f),
          glm::vec3(15 * delta, 0.f, 3.5f),
          glm::vec3(0.f, 1.f, 0.f));
      Debug::drawLine(
          glm::vec3(15 * delta, 0.f, 3.5f),
          glm::vec3(14 * delta, 0.f, 3.f),
          glm::vec3(0.f, 1.f, 0.f));
      Debug::drawLine(
          glm::vec3(14 * delta, 0.f, 3.f),
          glm::vec3(15 * delta, 0.f, 2.f),
          glm::vec3(0.f, 1.f, 0.f));

      Debug::drawLine(
          glm::vec3(16 * delta, 0.f, 2.f),
          glm::vec3(16 * delta, 0.f, 4.f),
          glm::vec3(0.f, 1.f, 0.f));
      Debug::drawLine(
          glm::vec3(16 * delta, 0.f, 2.f),
          glm::vec3(17 * delta, 0.f, 2.f),
          glm::vec3(0.f, 1.f, 0.f));
      Debug::drawLine(
          glm::vec3(17 * delta, 0.f, 2.f),
          glm::vec3(17 * delta, 0.f, 4.f),
          glm::vec3(0.f, 1.f, 0.f));

      Debug::drawLine(
          glm::vec3(19 * delta, 0.f, 4.f),
          glm::vec3(18 * delta, 0.f, 3.3f),
          glm::vec3(0.f, 1.f, 0.f));
      Debug::drawLine(
          glm::vec3(18 * delta, 0.f, 3.3f),
          glm::vec3(19 * delta, 0.f, 2.6f),
          glm::vec3(0.f, 1.f, 0.f));
      Debug::drawLine(
          glm::vec3(19 * delta, 0.f, 2.6f),
          glm::vec3(18 * delta, 0.f, 2.f),
          glm::vec3(0.f, 1.f, 0.f));
    }
};

AnimationDemo *demo;

void main_loop() {
  demo->mainLoop();
}

int main(int argc, char **argv) {
  demo = new AnimationDemo(argc, argv);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (1) {
      main_loop();
      // TODO: Wait for VSync? Or should we poll input faster than that?
    }
#endif

  // FIXME: This can never be reached if the demo object calls exit()
  delete demo;

  return EXIT_SUCCESS;
}
