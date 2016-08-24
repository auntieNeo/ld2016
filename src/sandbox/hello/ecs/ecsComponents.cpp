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
#include "ecsComponents.h"

namespace ld2016 {

  /*
   * The following macros describe the dependency relationships between components.The first block enumerates for
   * a given component what other components are required for it to exist. For example, it makes no sense for an
   * entity to posses linear velocity without first having a position. This relationship is important when you're
   * adding new components to the world. Notice that all components list the existence component as a requirement.
   *
   * The second set of macros describe the inverse relationships, or for a given component, which other components
   * list it as a required component. This relationship is examined upon the deletion of a component. Notice that
   * the existence component is a lists 'ALL' as its dependents.
   *
   * TODO: Add entries to both sections below for any new component types you create.
   * The generated format for any component enumerator is 'ENUM_[component_type].' As seen below, the ALL and NONE
   * enumerators also exist. Since these are bit flags, you can probably guess that NONE is zero and ALL is
   * unsigned -1, or in other words, ALL has all the bits turned on.
   *
   * Other files you will need to modify: ecsState.h, ecsState.cpp, components.h
   */
  COMP_DEFN_REQD(Existence, NONE);
  COMP_DEFN_REQD(Position, ENUM_Existence);
  COMP_DEFN_REQD(LinearVel, ENUM_Existence | ENUM_Position);
  COMP_DEFN_REQD(Orientation, ENUM_Existence);
  COMP_DEFN_REQD(AngularVel, ENUM_Existence | ENUM_Orientation);
  COMP_DEFN_REQD(CameraView, ENUM_Existence | ENUM_Position | ENUM_Orientation);
  COMP_DEFN_REQD(WasdControls, ENUM_Existence | ENUM_Position | ENUM_LinearVel | ENUM_Orientation | ENUM_AngularVel);

  COMP_DEFN_DEPN(Existence, ALL);
  COMP_DEFN_DEPN(Position, ENUM_LinearVel | ENUM_CameraView | ENUM_WasdControls);
  COMP_DEFN_DEPN(LinearVel, ENUM_WasdControls);
  COMP_DEFN_DEPN(Orientation, ENUM_AngularVel | ENUM_CameraView | ENUM_WasdControls);
  COMP_DEFN_DEPN(AngularVel, ENUM_WasdControls);
  COMP_DEFN_DEPN(CameraView, NONE);
  COMP_DEFN_DEPN(WasdControls, NONE);

  /*
   * The following area is for the definitions of any component methods you create. Make sure that constructor
   * parameters match the 'SIG_[component_type]' define you provided with the declaration of the component.
   * TODO: Add any and all component member method definitions here.
   * NOTE: Generally there shouldn't be methods except the constructor. Game logic ought to go in the systems instead.
   * Sometimes its convenient to put helper methods in some components, however (like matrix calculators in a camera
   * component or something). It's up to coder discretion.
   */
  bool Existence::isPresent(ComponentTypes compType) {
    return compType & componentsPresent;
  }
  bool Existence::passesPrerequisitesForAddition(compMask mask) {
    return (mask & componentsPresent) == mask;
  }
  bool Existence::passesDependenciesForRemoval(compMask mask) {
    return (mask & componentsPresent) == 0;
  }
  void Existence::turnOnFlags(compMask mask) {
    componentsPresent |= mask;
  }
  void Existence::turnOffFlags(compMask mask) {
    componentsPresent &= ~mask;
  }
  Position::Position(glm::vec3 vec) : vec(vec) {}
  LinearVel::LinearVel(glm::vec3 vec) : vec(vec) {}
  Orientation::Orientation(glm::quat quat) : quat(quat) {}
  AngularVel::AngularVel(glm::quat quat) : quat(quat) {}
  CameraView::CameraView(float fovy, float near, float far, float aspect)
      : fovy(fovy), near(near), far(far), aspect(aspect) {}
}