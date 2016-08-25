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
#include <limits>
#include "ecsState.h"

namespace ld2016 {

  CompOpReturn EcsState::createEntity(entityId *newId) {
    entityId id;
    if (freedIds.empty()) {
      if (nextId == std::numeric_limits<entityId>::max() || ++nextId == std::numeric_limits<entityId>::max()) {
        *newId = 0;
        return MAX_ID_REACHED;
      }
      id = nextId;
    } else {
      id = freedIds.top();
      freedIds.pop();
    }
    Existence *existence = &comps_Existence[id];
    existence->turnOnFlags(Existence::flag);
    *newId = id;
    return SUCCESS;
  }

  CompOpReturn EcsState::clearEntity(const entityId& id) {
    Existence* existence;
    CompOpReturn status = getExistence(id, &existence);
    if (status != SUCCESS) {
      return status;
    }
    GEN_CLEAR_ENT_LOOP_DEFN(ALL_COMPS)
    return SUCCESS;
  }

  CompOpReturn EcsState::deleteEntity(const entityId& id) {
    CompOpReturn status = clearEntity(id);
    if (status != SUCCESS) {
      return status;
    }
    status = remExistence(id);
    if (status != SUCCESS) {
      return status;
    }
    freedIds.push(id);
    return SUCCESS;
  }

  void EcsState::listenForLikeEntities(const compMask &likeness,
                                       CompOpCallback callback_add, CompOpCallback callback_rem) {
    CompOpCallback checkForCompleteness = [&](const entityId& id){
      if ((comps_Existence.at(id).componentsPresent & likeness) == likeness) {
        callback_add(id);
      }
    };
    CompOpCallback checkForInadequacy = [&](const entityId& id){
      if ((comps_Existence.at(id).componentsPresent & likeness) != likeness) {
        callback_rem(id);
      }
    };
    GEN_LISTEN_FOR_LIKE_ENTITIES_INTERNALS(ALL_COMPS)
  }

  template<typename compType, typename ... types>
  CompOpReturn EcsState::addComp(KvMap<entityId, compType>& coll, const entityId id,
                                 const CompOpCallback& callbacks, const types &... args) {
    if (comps_Existence.count(id)) {
      Existence* existence = &comps_Existence.at(id);
      if (existence->passesPrerequisitesForAddition(compType::requiredComps)) {
        if (coll.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(args...))) {
          existence->turnOnFlags(compType::flag);
          callbacks(id);
          return SUCCESS;
        }
        return REDUNDANT;
      }
      return PREREQ_FAIL;
    }
    return NONEXISTENT_ENT;
  }

  template<typename compType>
  CompOpReturn EcsState::remComp(KvMap<entityId, compType>& coll, const entityId id, const CompOpCallback& callbacks) {
    if (coll.count(id)) {
      if (comps_Existence.count(id)) {
        Existence* existence = &comps_Existence.at(id);
        if (existence->passesDependenciesForRemoval(compType::dependentComps)) {
          callbacks(id);
          coll.erase(id);
          if ((void*)&coll != (void*)&comps_Existence) {
            comps_Existence.at(id).turnOffFlags(compType::flag);
          }
          return SUCCESS;
        }
        return DEPEND_FAIL;
      }
      return NONEXISTENT_ENT;
    }
    return NONEXISTENT_COMP;
  }

  template<typename compType>
  CompOpReturn EcsState::getComp(KvMap<entityId, compType> &coll, const entityId id, compType** out) {
    if (coll.count(id)) {
      *out = &coll.at(id);
      return SUCCESS;
    }
    return NONEXISTENT_COMP;
  }

  /*
   * GEN_COLL_DEFNS wraps calls to the GEN_COMP_COLL_DEFN macro as defined in ecsComponents.h.
   * The GEN_COMP_COLL_DEFN macros DEFINE collections of each type of component and methods to access and modify them.
   */
  GEN_COLL_DEFNS
}