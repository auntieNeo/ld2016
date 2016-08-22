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

#include <cstdlib>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "../../common/game.h"
#include "../../common/meshObject.h"
#include "orbitCamera.h"

using namespace ld2016;

class HelloDemo : public Game {
    std::shared_ptr<orbitCamera> camera;
  public:
    HelloDemo(int argc, char **argv, glm::vec3 &&position, glm::quat &&orientation)
        : Game(argc, argv, "Animation Demo"),
          camera(std::make_shared<orbitCamera>(position, orientation)) {
      setCamera(camera);
    }
};

void main_loop(void *instance) {
  HelloDemo *demo = (HelloDemo *) instance;
  demo->mainLoop();
}

int main(int argc, char **argv) {
  HelloDemo demo(argc, argv, glm::vec3(), glm::quat());

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(main_loop, (void*)&demo, 0, 1);
#else
  while (1) {
    main_loop(&demo);
    // TODO: Wait for VSync? Or should we poll input faster than that?
  }
#endif

  return EXIT_SUCCESS;
}
