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
#ifndef LD2016_ENTITIES_H
#define LD2016_ENTITIES_H

#include "metaEcs.h"
#include "KvMap.h"
#include "components.h"

namespace ld2016 {

  #define COMP_COLL_DECL_NOARGS(comp) \
          KvMap<entityId, comp> comps_##comp;\
          CompOpReturn add##comp(const entityId id);\
          CompOpReturn rem##comp(const entityId id);\
          CompOpReturn get##comp(const entityId id, comp** out);
  #define COMP_COLL_DECL(comp, ...) \
          KvMap<entityId, comp> comps_##comp;\
          CompOpReturn add##comp(const entityId id, __VA_ARGS__);\
          CompOpReturn rem##comp(const entityId id);\
          CompOpReturn get##comp(const entityId id, comp** out);

  class GameState {

      COMP_COLL_DECL_NOARGS(Existence)
      COMP_COLL_DECL(Position, glm::vec3 vec)
      COMP_COLL_DECL(LinearVel, glm::vec3 vec)
      COMP_COLL_DECL(Orientation, glm::quat quat)
      COMP_COLL_DECL(AngularVel, glm::quat quat)
      COMP_COLL_DECL(CameraView, float fovy, float near, float far, float aspect)
      COMP_COLL_DECL_NOARGS(WasdControls)

      template<typename compType, typename ... types>
      CompOpReturn addComp(KvMap<entityId, compType>& coll, const entityId id, const types &... args);

      template<typename compType>
      CompOpReturn remComp(KvMap<entityId, compType>& coll, const entityId id, ComponentTypes flag);

      template<typename compType>
      CompOpReturn getComp(KvMap<entityId, compType>& coll, const entityId id, compType** out);
  };

  #undef COMP_COLL_DECL_NOARGS
  #undef COMP_COLL_DECL
}

#endif //LD2016_ENTITIES_H
