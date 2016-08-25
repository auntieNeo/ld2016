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
#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include <string>
#include <vector>
#include <algorithm>
#include "ecsState.h"

namespace ecs {

  template<typename Derived_System>
  class System
  {
    private:
      bool paused = false;
      Derived_System& sys();

    protected:
      State* game;
      std::vector<std::vector<entityId>> registeredIDs;
      std::vector<compMask> requiredComponents;

    public:
      System(State* game);
      bool init(std::stringstream& output, std::vector<compMask> entityTypesToWatch);
      void tick();
      void pause();
      void resume();
      void clean();
      bool isPaused();
  };

  template<typename Derived_System>
  System<Derived_System>::System(State* game)
      : game(game) { }
  template<typename Derived_System>
  Derived_System& System<Derived_System>::sys() {
    return *static_cast<Derived_System*>(this);
  }
  template<typename Derived_System>
  bool System<Derived_System>::init(std::stringstream& output, std::vector<compMask> entityTypesToWatch) {
    for (int i = 0; i < entityTypesToWatch.size(); i++) {
      registeredIDs.push_back(std::vector<entityId>());
      requiredComponents.push_back(entityTypesToWatch[i]);
      game->listenForLikeEntities(entityTypesToWatch[i],
        [&](const entityId &id) {
          registeredIDs[i].push_back(id);
        },
        [&](const entityId &id) {
          std::vector<entityId>::iterator position = std::find(registeredIDs[i].begin(),
                                                               registeredIDs[i].end(), id);
          if (position != registeredIDs[i].end()) {
            registeredIDs[i].erase(position);
          }
        }
      );
    }
    return sys().onInit(output);
  }
  template<typename Derived_System>
  void System<Derived_System>::tick() {
    sys().onTick();
  }
  template<typename Derived_System>
  void System<Derived_System>::pause(){
    if (!paused){
      paused = true;
    }
  }
  template<typename Derived_System>
  void System<Derived_System>::resume(){
    if (paused){
      paused = false;
    }
  }
  template<typename Derived_System>
  void System<Derived_System>::clean(){
    sys().onClean();
    for (auto registry : registeredIDs) {
      registry.clear();
    }
  }
  template<typename Derived_System>
  bool System<Derived_System>::isPaused(){
    return paused;
  }
}

#endif //ECS_SYSTEM_H
