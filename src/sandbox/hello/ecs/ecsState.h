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

#include "ecsCoreAutoGen.h"
#include "KvMap.h"
#include "components.h"

namespace ld2016 {

  class EcsState {

      /*
       * The following macros DECLARE collections of each type of component and methods to access and modify them.
       * TODO: Add an entry below for any new component types you create.
       * Other files you will need to modify: ecsState.cpp, components.h, components.cpp
       */
      COMP_COLL_DECL(Existence)
      COMP_COLL_DECL(Position)
      COMP_COLL_DECL(LinearVel)
      COMP_COLL_DECL(Orientation)
      COMP_COLL_DECL(AngularVel)
      COMP_COLL_DECL(CameraView)
      COMP_COLL_DECL(WasdControls)

    private:
      template<typename compType, typename ... types>
      CompOpReturn addComp(KvMap<entityId, compType>& coll, const entityId id, const types &... args);
      template<typename compType>
      CompOpReturn remComp(KvMap<entityId, compType>& coll, const entityId id, ComponentTypes flag);
      template<typename compType>
      CompOpReturn getComp(KvMap<entityId, compType>& coll, const entityId id, compType** out);
  };

//  #undef COMP_COLL_DECL_NOARGS
  #undef COMP_COLL_DECL
}

#endif //LD2016_ENTITIES_H
