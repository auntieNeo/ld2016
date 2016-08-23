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
#include "ecsState.h"

namespace ld2016 {

  /*
   * The following macros DEFINE collections of each type of component and methods to access and modify them.
   * TODO: Add an entry below for any new component types you create.
   * Other files you will need to modify: ecsState.h, components.h, components.cpp
   */
  COMP_COLL_DEFN(Existence)
  COMP_COLL_DEFN(Position)
  COMP_COLL_DEFN(LinearVel)
  COMP_COLL_DEFN(Orientation)
  COMP_COLL_DEFN(AngularVel)
  COMP_COLL_DEFN(CameraView)
  COMP_COLL_DEFN(WasdControls)

  template<typename compType, typename ... types>
  CompOpReturn EcsState::addComp(KvMap<entityId, compType>& coll, const entityId id, const types &... args) {
    if ( ! (coll.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(args...)))) {
      return REDUNDANT;
    }
    return SUCCESS;
  }
  template<typename compType>
  CompOpReturn EcsState::remComp(KvMap<entityId, compType>& coll, const entityId id, ComponentTypes flag) {
    if (coll.count(id)) {
      if (comps_Existence.count(id)) {
        coll.erase(id);
        comps_Existence.at(id).componentsPresent &= ~flag;
        return SUCCESS;
      }
      return INVALID_STATE;
    }
    return NONEXISTANT;
  }
  template<typename compType>
  CompOpReturn EcsState::getComp(KvMap<entityId, compType> &coll, const entityId id, compType** out) {
    if (coll.count(id)) {
      *out = &coll.at(id);
      return SUCCESS;
    }
    return NONEXISTANT;
  }

}