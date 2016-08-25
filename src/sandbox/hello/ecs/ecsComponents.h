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
#ifndef LD2016_ECS_H
#define LD2016_ECS_H

#include "ecsAutoGen.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ld2016 {

  typedef uint32_t compMask;

  template <typename Derived>
  struct Component {
    static compMask requiredComps;
    static compMask dependentComps;
    static compMask flag;
  };

  /*
   * The following are component type declarations.
   * TODO: Declare new components here and be sure to define 'SIG_[component_type]' as the constructor parameter types.
   * NOTE: Just follow the examples of the others.
   */
  #define SIG_Existence
  struct Existence : public Component<Existence> {
    compMask componentsPresent = 0;
    bool flagIsOn(int compType);
    bool passesPrerequisitesForAddition(compMask mask);
    bool passesDependenciesForRemoval(compMask mask);
    void turnOnFlags(compMask mask);
    void turnOffFlags(compMask mask);
  };
  #define SIG_Position glm::vec3
  struct Position : public Component<Position> {
    glm::vec3 vec;
    Position(glm::vec3 vec);
  };
  #define SIG_LinearVel glm::vec3
  struct LinearVel : public Component<LinearVel> {
    glm::vec3 vec;
    LinearVel(glm::vec3 vec);
  };
  #define SIG_Orientation glm::quat
  struct Orientation : public Component<Orientation> {
    glm::quat quat;
    Orientation(glm::quat quat);
  };
  #define SIG_AngularVel glm::quat
  struct AngularVel : public Component<AngularVel> {
    glm::quat quat;
    AngularVel(glm::quat quat);
  };
  #define SIG_CameraView float, float, float, float
  struct CameraView : public Component<CameraView> {
    float fovy, near, far, aspect;
    CameraView(float fovy, float near, float far, float aspect);
  };
  #define SIG_WasdControls
  struct WasdControls : public Component<WasdControls> {
    glm::vec3 accel;
  };

  /*
   * TODO: Add an entry to the end of each of the three directives below for any new component types you create.
   * (follow examples of others)
   */
  #define ALL_COMPS \
    Existence,      \
    Position,       \
    LinearVel,      \
    Orientation,    \
    AngularVel,     \
    CameraView,     \
    WasdControls

  #define GEN_COLL_DECLS \
    GEN_COMP_COLL_DECL(Existence)   \
    GEN_COMP_COLL_DECL(Position)    \
    GEN_COMP_COLL_DECL(LinearVel)   \
    GEN_COMP_COLL_DECL(Orientation) \
    GEN_COMP_COLL_DECL(AngularVel)  \
    GEN_COMP_COLL_DECL(CameraView)  \
    GEN_COMP_COLL_DECL(WasdControls)

  #define GEN_COLL_DEFNS \
    GEN_COMP_COLL_DEFN(Existence)   \
    GEN_COMP_COLL_DEFN(Position)    \
    GEN_COMP_COLL_DEFN(LinearVel)   \
    GEN_COMP_COLL_DEFN(Orientation) \
    GEN_COMP_COLL_DEFN(AngularVel)  \
    GEN_COMP_COLL_DEFN(CameraView)  \
    GEN_COMP_COLL_DEFN(WasdControls)

  /*
   * This macro does the following:
   * generates bit flag enumerations for all component types
   * declares and defines uint8_t numCompTypes as the number of component types total
   * declares these functions:
   */
  GEN_COMP_DECLS(ALL_COMPS)

  compMask getRequiredComps(const int compType);
  compMask getDependentComps(const int compType);

}

#endif //LD2016_ECS_H
