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
#ifndef LD2016_TYPES_H
#define LD2016_TYPES_H

#include <stdint.h>
#include "ecsCoreAutoGenForEach.h"

namespace ld2016 {

  typedef uint32_t entityId;
  typedef uint32_t compMask;

  enum CompOpReturn {
    SUCCESS,
    NONEXISTANT,
    REDUNDANT,
    PREREQ_FAIL,
    INVALID_STATE,
  };

  #define _GEN_COMP_ENUM(comp, i) ENUM_##comp = 1 << i,
  #define GEN_COMP_ENUMS(...) enum ComponentTypes { NONE = 0, ALL = -1, DO_FOR_EACH(_GEN_COMP_ENUM, __VA_ARGS__) };

  #define _GEN_ARG_NAME_NUMERIC(placeholder, i) , arg##i
  #define GEN_ARG_NAMES(...) DO_FOR_EACH(_GEN_ARG_NAME_NUMERIC, ##__VA_ARGS__)

  #define _GEN_ARG_NAME_TYPED(type, i) , type arg##i
  #define GEN_ARG_NAMES_TYPED(...) DO_FOR_EACH(_GEN_ARG_NAME_TYPED, ##__VA_ARGS__)

  /*#define COMP_COLL_DECL_NOARGS(comp) \
          KvMap<entityId, comp> comps_##comp;\
          CompOpReturn add##comp(const entityId id);\
          CompOpReturn rem##comp(const entityId id);\
          CompOpReturn get##comp(const entityId id, comp** out);*/
  #define _COMP_COLL_DECL(comp, ...) \
          private: KvMap<entityId, comp> comps_##comp; public: \
          CompOpReturn add##comp(const entityId id GEN_ARG_NAMES_TYPED(__VA_ARGS__));\
          CompOpReturn rem##comp(const entityId id);\
          CompOpReturn get##comp(const entityId id, comp** out);
  #define COMP_COLL_DECL(comp) _COMP_COLL_DECL(comp, SIG_##comp)

  /*#define _COMP_COLL_DEFN_NOARGS(comp) \
          CompOpReturn EcsState::add##comp(const entityId id) { addComp(comps_##comp, id); }\
          CompOpReturn EcsState::rem##comp(const entityId id) { remComp(comps_##comp, id, ENUM_##comp); }\
          CompOpReturn EcsState::get##comp(const entityId id, comp** out) { getComp(comps_##comp, id, out); }*/
  #define _COMP_COLL_DEFN(comp, ...) \
    CompOpReturn EcsState::add##comp(const entityId id GEN_ARG_NAMES_TYPED(__VA_ARGS__)) \
                                { addComp(comps_##comp, id GEN_ARG_NAMES(__VA_ARGS__)); }\
    CompOpReturn EcsState::rem##comp(const entityId id) { remComp(comps_##comp, id, ENUM_##comp); }\
    CompOpReturn EcsState::get##comp(const entityId id, comp** out) { getComp(comps_##comp, id, out); }
  #define COMP_COLL_DEFN(comp) _COMP_COLL_DEFN(comp, SIG_##comp)

  #define COMP_DEFN_REQD(comp, flags) template<> compMask Component<comp>::requiredComps = flags
  #define COMP_DEFN_DEPN(comp, flags) template<> compMask Component<comp>::dependentComps = flags
}

#endif //LD2016_TYPES_H
