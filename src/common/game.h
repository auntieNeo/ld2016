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

#ifndef LD2016_COMMON_GAME_H_
#define LD2016_COMMON_GAME_H_
#include <GL/glew.h>
#include <SDL.h>
#include <memory>
#include "ecs/ecsState.h"
#include "ecs/ecsSystem.h"

namespace ld2016 {
  class Camera;
  class Scene;
  class Game {
    private:
      const char *m_windowTitle;
      SDL_Window *m_window;
      SDL_GLContext m_glContext;
      int m_width, m_height;
      Scene *m_scene;
      std::shared_ptr<Camera> m_camera;
      float m_lastTime;

      void m_initSdl();
      void m_initGl();
      void m_initScene();
    protected:
      ecs::State state;

    public:
      Game(int argc, char **argv, const char *windowTitle);
      virtual ~Game();

      int width() const { return m_width; }
      int height() const { return m_height; }
      float aspect() const { return (float)m_width / (float)m_height; }
      Scene *scene() { return m_scene; }

      void setCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

      virtual bool handleEvent(const SDL_Event &event) {
        return false;
      }

      float mainLoop(ecs::Delegate<bool(SDL_Event&)>& systemsHandler);
  };
}

#endif
